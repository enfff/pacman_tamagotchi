#ifndef __TAMAGOTCHI_H
#define __TAMAGOTCHI_H

#include <stdint.h>

/*	User function	protoypes --------------------------------------------------*/

void Tamagotchi_Init(void);

void DrawBackground(void);
void DrawAgeBar(int8_t hours, int8_t minutes, int8_t seconds);
void stats_satiety_ghosts(uint8_t option, uint8_t new_amount);
void stats_happiness_pacman(uint8_t option, uint8_t new_amount);
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
int canProceed(int value);

void play_startup_sound(void);
void play_death_sound(void);
void play_eat_sound(void);
void play_pet_sound(void);
void play_click_sound(void);

#endif 
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
