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
			DrawPet_idle_stance1(PET_STARTING_X, PET_STARTING_Y);
		case 2:
			DrawPet_idle_stance2(PET_STARTING_X, PET_STARTING_Y);
		case 3:
			DrawPet_idle_stance1(PET_STARTING_X, PET_STARTING_Y);
		case 4:
			DrawPet_idle_stance2(PET_STARTING_X, PET_STARTING_Y);
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
	
	static int8_t statsCountdown = 5;
	
	seconds++;
	statsCountdown--;			// decreases every second
	
	if (seconds % 60 == 0 && seconds >= 1){
		seconds = 0;
		minutes++;
	}
	
	if (minutes % 60 == 0 && minutes >= 1){
		minutes = 0;
		hours++;
	}
	
	DrawAgeBar(hours, minutes, seconds);
	
	if(statsCountdown % 5 == 0){
		pet_decreaseSatiety();
		pet_decreaseHappiness();
		statsCountdown = 5;
	}
	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
