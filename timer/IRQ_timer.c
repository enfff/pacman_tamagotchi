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
#include "../RIT/RIT.h"
#include "../adc/adc.h"

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

uint16_t SinTable[45] =                                       /* ?????                       */
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};


uint8_t HoChiamatoGameOver = 0;

static uint8_t animation_type = 'I';

void TIMER0_IRQHandler (void){
	static int8_t software_count = 0;
	static int8_t frame_number = 0;
	software_count++;
	
	animation_type = get_animation_type();
	
	if(HoChiamatoGameOver == 0){
		switch(animation_type){
			case 'I':	// idle
				if(HoChiamatoGameOver == 1){
					break;
				}
				if(software_count % 2 == 0 && HoChiamatoGameOver == 0){
					pet_animation_idle1();
				} // pacman bocca chiusa			
				else if (software_count % 2 != 0 && HoChiamatoGameOver == 0){
					pet_animation_idle2();
				} // pacman bocca aperta
				break;
			case 'P':	// play (disegna fantasmino spaventato)
				if(HoChiamatoGameOver == 1){
					break;
				}
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
					play_eat_sound();
					pet_clear_animation_pursuit();
				}
			break;
			case 'S': // snack (disegna fragola)
				if(HoChiamatoGameOver == 1){
					break;
				}
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
					play_eat_sound();
					pet_clear_animation_pursuit();
				}
				break;
			case 'T': // animazione di petting
				if(HoChiamatoGameOver == 1){
					break;
				}
				if(frame_number == 0){
					disable_timer(1); //gestisce age e stats
					disable_RIT();
					frame_number++;
					pet_animation_pet1(PET_STARTING_X, PET_STARTING_Y);
				} else if(frame_number == 1) {
					frame_number++;
					pet_animation_pet2(PET_STARTING_X, PET_STARTING_Y);
				} else if(frame_number == 2) {
					frame_number++;
					pet_animation_pet3(PET_STARTING_X, PET_STARTING_Y);
				} else if(frame_number == 3){
					frame_number++;
					pet_animation_pet4(PET_STARTING_X, PET_STARTING_Y);
				} else if(frame_number == 4) {
					frame_number++;
					pet_animation_pet1(PET_STARTING_X, PET_STARTING_Y);
			  } else if(frame_number == 5) {
					frame_number++;
					pet_animation_pet2(PET_STARTING_X, PET_STARTING_Y);
				} else if(frame_number == 6) {
					frame_number++;
					pet_animation_pet3(PET_STARTING_X, PET_STARTING_Y);
				} else if(frame_number == 7) {
					frame_number++;
					pet_animation_pet4(PET_STARTING_X, PET_STARTING_Y);
					set_animation_type('I');
					frame_number=0;
					pet_increaseHappiness();
					enable_RIT();
					enable_timer(1);
					play_pet_sound();
					// non c'è bisogno di cancellare l'ultimo frame disegnato perché riprende da idle
				}
				break;	
			case 'D': // death
				if(HoChiamatoGameOver == 1){
					break;
				}
				if(frame_number == 0){
					frame_number++;
					pet_animation_death1(PET_STARTING_X, PET_STARTING_Y);
				} else if(frame_number == 1) {
					frame_number++;
					pet_animation_death2(PET_STARTING_X, PET_STARTING_Y);
				} else if(frame_number == 2) {
					frame_number++;
					pet_animation_death3(PET_STARTING_X, PET_STARTING_Y);
				} else if(frame_number == 3) {
					frame_number++;
					pet_animation_death4(PET_STARTING_X, PET_STARTING_Y);
				} else if(frame_number == 4) {
					frame_number++;
					pet_animation_death5(PET_STARTING_X, PET_STARTING_Y);
				} else if(frame_number == 5) {
					frame_number++;
					pet_animation_death6(PET_STARTING_X, PET_STARTING_Y);
				} else if(frame_number == 6) {
					frame_number=0;
					disable_timer(0);
					set_animation_type('I');
					reset_timer(0);
					canProceed(1);		// can proceed with GameOver()
				}
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

void TIMER1_IRQHandler (void){
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

void TIMER2_IRQHandler (void)
{
	static int sineticks=0;
	/* DAC management */	
	static int currentValue; 
	
	currentValue = (uint16_t)((float)SinTable[sineticks]*get_volume()/1024*1.25);
	
	if(currentValue < 32){
		currentValue = 0;
	}
	
	LPC_DAC->DACR = (currentValue << 6);
	sineticks++;
	if(sineticks == 45) sineticks=0;
	
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER3_IRQHandler (void)
{
	disable_timer(2);
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}


// <-------------------------------------------------------------------------->

/******************************************************************************
**                            End Of File
******************************************************************************/
