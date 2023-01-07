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


/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Handles idle pet animation, 25ms, 25MHz
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

static int HoChiamatoGameOver = 0;
static uint8_t animation_type = 'I';				// 0 -> idle, 1 -> pet play, 2 -> pet snack

void TIMER0_IRQHandler (void)
{
	static int8_t software_count = 0;
	static int8_t frame_number = 0;
	software_count++;
	
	animation_type = get_animation_type();
	
	if(HoChiamatoGameOver == 0){
		switch(animation_type){
			case 'I':	// idle
				if(software_count % 2 == 0)	{ pet_animation_idle1(); } // pacman bocca chiusa			
				else 												{ pet_animation_idle2(); } // pacman bocca aperta
				break;
			case 'P':	// play (disegna fantasmino spaventato)
				if(frame_number == 0){
					frame_number++;
					draw_pet_play();
				} else if(frame_number == 1) {
					frame_number++;
					pet_animation_pursuit2(frame_number - 1);
				} else if(frame_number == 2) {
					frame_number++;
					pet_animation_pursuit1(frame_number - 1);
				} else if(frame_number == 3) {
					frame_number++;
					pet_animation_pursuit2(frame_number - 1);
					set_animation_type('I');
					frame_number=0;
					pet_clear_animation_pursuit();
				}
			break;
			case 'S': // snack (disegna fragola)
				if(frame_number == 0){
					frame_number++;
					draw_pet_snack();
				} else if(frame_number == 1) {
					frame_number++;
					pet_animation_pursuit2(frame_number - 1);
				} else if(frame_number == 2) {
					frame_number++;
					pet_animation_pursuit1(frame_number - 1);
				} else if(frame_number == 3) {
					frame_number++;
					pet_animation_pursuit2(frame_number - 1);
					set_animation_type('I');
					frame_number=0;
					pet_clear_animation_pursuit();
				}
				break;
			default:
				break;
		}
	}
	
	// reset_timer(0); // ricomincia a contare da 0;
	
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
