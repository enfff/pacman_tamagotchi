/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_adc.c
** Last modified Date:  20184-12-30
** Last Version:        V1.00
** Descriptions:        functions to manage A/D interrupts
** Correlated files:    adc.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "adc.h"
#include "../timer/timer.h"
#include "../tamagotchi/pet.h"

/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
 *----------------------------------------------------------------------------*/

unsigned short AD_current = 1024;  //inizia con un quarto del volume. il valore max è 4095  
unsigned short AD_last = 0xFF;     /* Last converted value               */

void ADC_IRQHandler(void) {
  	
  AD_current = ((LPC_ADC->ADGDR>>4) & 0xFFF);/* Read Conversion Result             */
  
	AD_current = ((LPC_ADC->ADGDR>>4) & 0xFFF);/* Read Conversion Result             */
  update_volume();
	if(AD_current != AD_last){
		AD_last = AD_current;
	}
	
}


uint8_t update_volume(void){

	static uint8_t ticks = 0;
	uint8_t last_volume_level = AD_last/1024;		 				// Ritorna valori inclusi tra {0, 1, 2, 3}
	uint8_t current_volume_level = AD_current/1024;

	
	if ( AD_current > 50 && current_volume_level == 0){
		current_volume_level = 1;
	}
	
	if ( AD_last > 50 && last_volume_level == 0 ){
		last_volume_level = 1;
	}
	
	if(current_volume_level != last_volume_level){
		draw_speaker_volume(current_volume_level);
		ticks=1;
	}
	
	else{
		if(ticks == 0){
			ticks++;
			if(ticks >= 40){
				draw_speaker_volume(current_volume_level); // clean
				ticks = 0;
			}
		}
	}
	
	return current_volume_level;
}

uint16_t get_volume(void){
	return AD_current/4;
}
