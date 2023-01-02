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
#include "../TouchPanel/TouchPanel.h"
#include "../tamagotchi/pet.h"
#include "../tamagotchi/tamagotchi.h"


// User defined variables *****************************************************
	
	//char updatedTime[8] = {'0', '0', ':', '0', '0', ':', '0', '0'};
	

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Handles idle pet animation
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
			DrawPet_idle_stance1(200, 105);
		case 2:
			DrawPet_idle_stance2(200, 105);
		case 3:
			DrawPet_idle_stance1(200, 105);
		case 4:
			DrawPet_idle_stance2(200, 105);
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
	
	static char updatedTime[8] = {'0', '0', ':', '0', '0', ':', '0', '0'};
	
	seconds++; 
	
	if (seconds % 59 == 0 && seconds >= 1){
		seconds = 0;
		minutes++;
	}
	
	if (minutes % 59 == 0 && minutes >= 1){
		minutes = 0;
		hours++;
	}
	
	sprintf(updatedTime, "Age: %02d:%02d:%02d", hours, minutes, seconds);
	
	if(seconds % 5 == 0 && seconds > 1){
		pet_decreaseSatiety();
		pet_decreaseHappiness();
	}
	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
