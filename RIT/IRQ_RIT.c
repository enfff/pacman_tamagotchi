/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../tamagotchi/tamagotchi.h"
#include "../timer/timer.h"
#include "../TouchPanel/TouchPanel.h"
#include "../music/music.h"
#include "../adc/adc.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

extern uint8_t HoChiamatoGameOver;

void RIT_IRQHandler (void)
{					
	static int8_t last_key_pressed = 0;			// 0-> select, 1-> left, 2-> right
	ADC_start_conversion();
	
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){ // SELECT
			
			if(last_key_pressed == 1){						//Play
				play_click_sound();
				disable_RIT();
				pet_play();
				DrawPlayButton('N');
				enable_RIT();
				
			}
			
			if(last_key_pressed == 2){						//Snack
				play_click_sound();
				disable_RIT();
				pet_snack();
				DrawSnackButton('N');
				enable_RIT();
		}
		
		last_key_pressed = 0;
		
		if(gameCanRestart(0)){				// questa funzione controlla che la flag gameCanRestart_flag
			
			disable_RIT();							// contenuta in tamagotchi.c sia messa ad 1; l'argomento 0
			
			reset_RIT();
			reset_timer(0);
			reset_timer(1);
			
			DrawResetButton('N');				// cancella il tasto reset precedentemente disegnato dal GameOver()
			Tamagotchi_Init();
			
			enable_RIT();
			enable_timer(0);
			enable_timer(1);
		}
		
	
	
		reset_RIT();
  }

	
	// <----------------------------------------------------->
	
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){ // LEFT (PLAY)
		DrawPlayButton('S');
		DrawSnackButton('N');
		last_key_pressed = 1;
		reset_RIT();
  }
	
	// <----------------------------------------------------->
	
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){ // RIGHT (SNACK)
		DrawSnackButton('S');
		DrawPlayButton('N');
		last_key_pressed = 2;
		reset_RIT();
  }
	
	// <----------------------------------------------------->
	
	// Controllo se può partire l'animazione di petting
	if(HoChiamatoGameOver == 0 && getDisplayPoint(&display, Read_Ads7846(), &matrix )){
		
		if(display.y > 135 && display.y < 235 && display.x > 55 && display.x < 155) {
			set_animation_type('T'); // Petting
		}
		
	}
	
	disable_RIT();
	reset_RIT();
	enable_RIT();
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
  return;
}


/******************************************************************************
**                            End Of File
******************************************************************************/
