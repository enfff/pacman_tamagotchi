/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include <stdio.h>

#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../tamagotchi/pet.h"
#include "../tamagotchi/tamagotchi.h"


// User defined variables *****************************************************

# define PET_STARTING_X 185
# define PET_STARTING_Y 105

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Handles idle pet animation, 25ms, 25MHz
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER0_IRQHandler (void)
{
	uint8_t software_count = 0;
	software_count++;
	
	switch(software_count){
		case 1:
			pet_animation_idle1(PET_STARTING_X, PET_STARTING_Y);
		case 2:
			pet_animation_idle2(PET_STARTING_X, PET_STARTING_Y);
			software_count = 0;
		default:
			break;
	}
	
  LPC_TIM0->IR |= 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Handles pet age; 1s, 25MHz
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER1_IRQHandler (void)
{
	static int8_t seconds=0;
	static int8_t minutes=0;
	static int8_t hours=0;
	
	static int HoChiamatoGameOver = 0;
	seconds++;
	
	if (seconds % 60 == 0 && seconds >= 1){
		seconds = 0;
		minutes++;
	}
	
	if (minutes % 60 == 0 && minutes >= 1){
		minutes = 0;
		hours++;
	}
	
	DrawAgeBar(hours, minutes, seconds);
	
	if(decrease_countdown() % 5 == 0){
		HoChiamatoGameOver = pet_decreaseSatiety();
		
		if(HoChiamatoGameOver == 0){
			pet_decreaseHappiness();
		} else {
			seconds = 0;		// è stata chiamata la GameOver quindi resetto il conteggio
			minutes = 0;
			hours = 0;
		}
	
		reset_countdown();
		
		HoChiamatoGameOver = 0; // Dovrei modificare questo valore dentro la GameOver(), ma è più semplice chiamarla qui;
	}
	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}



// <-------------------------------------------------------------------------->

/******************************************************************************
**                            End Of File
******************************************************************************/
