#ifndef __TAMAGOTCHI_H
#define __TAMAGOTCHI_H

#include <stdint.h>

/*	User function	protoypes --------------------------------------------------*/

void Tamagotchi_Init(void);
void pet_decreaseSatiety(void);
void pet_decreaseHappiness(void);
void DrawSatietyBar(void);
void DrawHappinessBar(void);
void DrawAgeBar(uint8_t *updatedTime);
void GameOver(void);
void DrawBackground(void);


#endif 
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
