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
void DrawResetButton(uint8_t option);

void GameOver(void);
void pet_play(void);
void pet_snack(void);
int pet_decreaseSatiety(void);			//Ritorna una flag... non ne sono fiero
void pet_decreaseHappiness(void);
void pet_increaseSatiety(void);
void pet_increaseHappiness(void);
int gameCanRestart(int value);

#endif 
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
