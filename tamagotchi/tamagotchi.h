#ifndef __TAMAGOTCHI_H
#define __TAMAGOTCHI_H

#include <stdint.h>

/*	User function	protoypes --------------------------------------------------*/

void Tamagotchi_Init(void);

void DrawBackground(void);
void DrawSatietyBar(void);
void DrawHappinessBar(void);
void DrawAgeBar(int8_t hours, int8_t minutes, int8_t seconds);
void DrawPlayButton(uint8_t option);
void DrawSnackButton(uint8_t option);

void GameOver(void);
void pet_play(void);
void pet_snack(void);
void pet_decreaseSatiety(void);
void pet_decreaseHappiness(void);

#endif 
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
