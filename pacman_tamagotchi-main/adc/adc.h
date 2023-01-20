#include <string.h>
#include "lpc17xx.h"

/* lib_adc.c */
void ADC_init (void);
void ADC_start_conversion (void);

/* IRQ_adc.c */
void ADC_IRQHandler(void);

/*User defined functions*/

uint8_t update_volume(void);
uint16_t get_volume(void);
