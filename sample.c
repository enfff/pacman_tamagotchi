/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "timer/timer.h"
#include "tamagotchi/tamagotchi.h"
#include "tamagotchi/pet.h" // RIMUOVI
#include "joystick/joystick.h"
#include "RIT/RIT.h"
#include "TouchPanel/TouchPanel.h"
#include "adc/adc.h"

#define SIMULATOR 1

# define PET_STARTING_X 185
# define PET_STARTING_Y 105

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	
	LPC_PINCON->PINSEL1 |= (1<<21);
	LPC_PINCON->PINSEL1 &= ~(1<<20);
	LPC_GPIO0->FIODIR |= (1<<26);
	
	NVIC_SetPriority(RIT_IRQn, 1);				// handles joystick
	NVIC_SetPriority(TIMER0_IRQn, 3);			// handles all animations
	NVIC_SetPriority(TIMER1_IRQn, 2);			// handles age and stats
	NVIC_SetPriority(TIMER2_IRQn, 0);			//
	NVIC_SetPriority(TIMER3_IRQn, 0);			// handles adc converter
	
	LCD_Initialization();
	TP_Init();
	TouchPanel_Calibrate();
	
	init_timer(0, 0x5F5E10);							// 250ms, 25MHz, handles animations
	init_timer(1, 0x17D7840);							// 1s,   	25MHz, handles age and stats
	
	joystick_init();
	init_RIT(0x4C4B40);										// 50ms, 	100MHz
	
	ADC_init();					
	Tamagotchi_Init();
	
	enable_RIT();
	enable_timer(0);											
	enable_timer(1);	
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
	
  while (1)	
  {
		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
