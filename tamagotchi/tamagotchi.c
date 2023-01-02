#include <stdio.h>
#include "tamagotchi.h"
#include "pet.h"
#include "../GLCD/GLCD.h"
#include "../timer/timer.h"

# define pet_starting_position_x 185
# define pet_starting_position_y 105

static uint8_t satiety = 5;
static uint8_t happiness = 5;
	
void Tamagotchi_Init(void){
	//DrawBackground();
	DrawHappinessBar();
	DrawSatietyBar();
	DrawPet_idle_stance2(pet_starting_position_x, pet_starting_position_y);
}

void DrawAgeBar(uint8_t *updatedTime){
	GUI_Text(0, 0, updatedTime, White, Blue);
}

void pet_decreaseSatiety(void){
	satiety--;
	
	if (satiety == 0){
		GameOver();
	}
	
	DrawSatietyBar();
}

void pet_decreaseHappiness(void){
	happiness--;
	
	if (happiness == 0){
		GameOver();
	}
	
	DrawHappinessBar();
}

void DrawSatietyBar(void){
	char str[16];
	sprintf(str, "Hunger: %02d", satiety);
	GUI_Text(0, 20, (uint8_t *) str, White, Red);
}

void DrawHappinessBar(void){
	char str[16];
	sprintf(str, "Happiness: %02d", happiness);
	GUI_Text(0, 40, (uint8_t *) str, White, Green);
}

void GameOver(void){
	DrawPet_death(pet_starting_position_x, pet_starting_position_y);
	disable_timer(0);
	disable_timer(1);
}
