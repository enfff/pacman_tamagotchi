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

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void RIT_IRQHandler (void)
{					
	static int8_t last_key_pressed = 0;			// 0-> select, 1-> left, 2-> right
	
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){ // SELECT
		
		if(last_key_pressed == 1){
			disable_RIT();
			pet_play();
			enable_RIT();
		}
		
		if(last_key_pressed == 2){
			disable_RIT();
			pet_snack();
			enable_RIT();
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
	
	reset_RIT();
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
