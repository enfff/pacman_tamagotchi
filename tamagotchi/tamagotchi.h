#ifndef __TAMAGOTCHI_H
#define __TAMAGOTCHI_H

#include <stdint.h>

/*	User function	protoypes --------------------------------------------------*/

void Tamagotchi_Init(void);
void DrawBackground(void);
void pet_decreaseSatiety(void);
void pet_decreaseHappiness(void);
void DrawSatietyBar(void);
void DrawHappinessBar(void);
void DrawAgeBar(int8_t hours, int8_t minutes, int8_t seconds);
void GameOver(void);
void DrawPlayButton(uint8_t option);
void DrawSnackButton(uint8_t option);

#endif 
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
