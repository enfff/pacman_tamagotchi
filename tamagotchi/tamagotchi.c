#include <stdio.h>
#include <stdint.h>
#include "tamagotchi.h"
#include "pet.h"
#include "../GLCD/GLCD.h"
#include "../timer/timer.h"
#include "../TouchPanel/TouchPanel.h"
#include "../RIT/RIT.h"

# define PET_STARTING_X 185
# define PET_STARTING_Y 105

#define RIT_SEMIMINIMA 8
#define RIT_MINIMA 16
#define RIT_INTERA 32

#define UPTICKS 1

NOTE pacman_sound_startup[] = {
	{c4,	time_semicroma},
	{c5,	time_semicroma},
	{g4,	time_semicroma},
	{e4,	time_semicroma},
	{c5,	time_semicroma},
	{g4,	time_semicroma},
	{e4,	time_semiminima},
	{db4,	time_semicroma},
	{db5,	time_semicroma},
	{ab4,	time_semicroma},
	{f4,	time_semicroma},
	{db5,	time_semicroma},
	{ab4,	time_semicroma},
	{f4,	time_semiminima},
	{c4,	time_semicroma},
	{c5,	time_semicroma},
	{g4,	time_semicroma},
	{e4,	time_semicroma},
	{c5,	time_semicroma},
	{g4,	time_semicroma},
	{e4,	time_croma},
	{e4,	time_biscroma},
	{f4,	time_biscroma},
	{gb4,	time_biscroma},
	{gb4,	time_biscroma},
	{g4,	time_biscroma},
	{ab4,	time_biscroma},
	{ab4,	time_biscroma},
	{a4,	time_biscroma},
	{bb4,	time_biscroma},
	{c5,	time_semiminima}
};

NOTE pacman_sound_eat[] = {
	{c5,	time_semibiscroma},
	{db5,	time_semibiscroma},
	{d5,	time_semibiscroma},
	{eb5,	time_semibiscroma},
	{e5,	time_semibiscroma},
	{f5,	time_semibiscroma},
	{gb5,	time_semibiscroma},
	{g5,	time_semibiscroma},
	{ab5,	time_semibiscroma},
	{a5,	time_semibiscroma},
	{bb5,	time_semibiscroma},
	{b5,	time_semibiscroma}
};

NOTE pacman_sound_death[] = {
	{d6, time_semibiscroma},
	{db6, time_semibiscroma},
	{d6, time_semibiscroma},
	{db6, time_semibiscroma},
	{c6, time_semibiscroma},
	{db6, time_semibiscroma},
	{c6, time_semibiscroma},
	{b5, time_semibiscroma},
	{c6, time_semibiscroma},
	{b5, time_semibiscroma},
	{bb6, time_semibiscroma},
	{b5, time_semibiscroma},
	{bb6, time_semibiscroma},
	{a5, time_semibiscroma},
	{gb5, time_semibiscroma},
	{a5, time_semibiscroma},
	{gb5, time_semibiscroma},
	{g5, time_semibiscroma},
	{gb5, time_semibiscroma},
	{g5, time_semibiscroma},
	{gb5, time_semibiscroma},
	{g5, time_semibiscroma},
	{gb5, time_semibiscroma},
	{f5, time_semibiscroma},
	{gb5, time_semibiscroma},
	{f5, time_semibiscroma},
	{e5, time_semibiscroma},
	{eb5, time_semibiscroma},
	{e5, time_semibiscroma},
	{eb5, time_semibiscroma},
	{d5, time_semibiscroma},
	{eb5, time_semibiscroma},
	{d5, time_semibiscroma},
	{db5, time_semibiscroma},
	{d5, time_semibiscroma},
	{db5, time_semibiscroma},
	{c5, time_semibiscroma},
	{db5, time_semibiscroma},
	{c5, time_semibiscroma},
	{b4, time_semibiscroma},
	{bb4, time_semibiscroma},
	{b4, time_semibiscroma},
	{bb4, time_semibiscroma},
	{a4, time_semibiscroma},
	{bb4, time_semibiscroma},
	{a4, time_semibiscroma},
	{ab4, time_semibiscroma},
	{a4, time_semibiscroma},
	{e4, time_semibiscroma},
	{g4, time_semibiscroma},
	{b4, time_semibiscroma},
	{d5, time_semibiscroma},
	{e4, time_semibiscroma},
	{g4, time_semibiscroma},
	{b4, time_semibiscroma},
	{d5, time_semibiscroma}
};



NOTE pacman_sound_pet[] = {
	{bb5,	time_semicroma},
	{eb6,	time_semicroma},
	{gb6,	time_semicroma},
	{f6,	time_semicroma},
	{eb6,	time_biscroma},
	{gb6,	time_semicroma},
	{eb6,	time_semicroma},
	{f6,	time_semicroma},
	{eb6,	time_semicroma},
	{b5,	time_semicroma},
	{db6,	time_semicroma},
	{bb5,	time_semicroma}
};

static uint8_t satiety;
static uint8_t happiness;
static int canGameRestart_flag;
static int canProceed_flag;

extern uint8_t HoChiamatoGameOver;
static int ticks = 0;
static int currentNote = 0;
	
void Tamagotchi_Init(void){
 
	satiety = 5;
	happiness = 5;
	canGameRestart_flag = 0;
	canProceed_flag = 0;
	HoChiamatoGameOver = 0;
	
	DrawBackground();
	DrawPlayButton('N');
	DrawSnackButton('N');
	
	GUI_Text(24, 22, (uint8_t *) "SATIETY:" , White, Black);
	stats_init_satiety_ghosts();
	GUI_Text(24, 40, (uint8_t *) "HAPPINESS:" , White, Black);
	stats_init_happiness_pacman();
	GUI_Text(24, 4, (uint8_t *) "AGE:" , White, Black);
	
	play_startup_sound();
}


// fa l'or logico tra flag e value. La flag viene alla fine settata nell'animazione di morte;
int canProceed(int value){
	canProceed_flag |= value;
	return canProceed_flag;
}
// fa l'or logico tra flag e value. Flag viene settata in GameOver();
int gameCanRestart(int value){
	canGameRestart_flag |= value;
	return canGameRestart_flag;
}

int pet_decreaseSatiety(void){
	satiety--;
	stats_satiety_ghosts('D', satiety);
	
	if (satiety == 0){
		GameOver();
		return 1;
	}
	return 0;
}

void pet_increaseSatiety(void){
	if (satiety < 5){
		satiety++;
		stats_satiety_ghosts('I', satiety);
	}
}

void pet_decreaseHappiness(void){
	happiness--;	
	stats_happiness_pacman('D', happiness);
	
	if (happiness == 0){
		GameOver();
	}
}

void pet_increaseHappiness(void){
	if (happiness < 5){
		happiness++;
		stats_happiness_pacman('I', happiness);
	}
}

void DrawAgeBar(int8_t hours, int8_t minutes, int8_t seconds){
	char updatedTime[13];
	sprintf(updatedTime, "%02d:%02d:%02d", hours, minutes, seconds);
	GUI_Text(149, 4, (uint8_t *) updatedTime, White, Black);
}

void DrawPlayButton(uint8_t option){
	//Case S: selezionato
	//Case N: non selezionato
	switch(option){
		case 'S':
			GUI_Text(45, 292, (uint8_t *) "PLAY", White, Blue);
			break;
		case 'N':
			GUI_Text(45, 292, (uint8_t *) "PLAY", White, Black);
		default:
			break;
	}
}

void DrawSnackButton(uint8_t option){
	//Case S: selezionato
	//Case N: non selezionato
	switch(option){
	case 'S':
		GUI_Text(149, 292, (uint8_t *) "SNACK", White, Blue);
		break;
	case 'N':
		GUI_Text(149, 292, (uint8_t *) "SNACK", White, Black);
	default:
		break;
	}
}

void DrawResetButton(uint8_t option){
	//Case S: selezionato
	//Case N: non selezionato
	switch(option){
	case 'S':
		GUI_Text(103, 272, (uint8_t *) "RESET", White, Blue);
		break;
	case 'N':
		GUI_Text(103, 272, (uint8_t *) "RESET", Black, Black);
	default:
		break;
	}
}

void pet_play(void){
	disable_timer(1);
	
	play_eat_sound();
	set_animation_type('P');
	pet_increaseHappiness();
	
	enable_timer(1);
	reset_countdown();			// satiety and happiness countdown
}

void pet_snack(void){
	disable_timer(1);
	
	play_eat_sound();
	set_animation_type('S');
	pet_increaseSatiety();

	enable_timer(1);
	reset_countdown();			// satiety and happiness countdown
}

void GameOver(void){
	disable_timer(1);				// age
	reset_timer(1);
	
	play_death_sound();
	set_animation_type('D');
	
	while(canProceed(0) == 1){
		DelayUS(1);
	}
	
	LCD_SetBackground(Black);
	
	GUI_Text(85, 100, (uint8_t *) "GAME OVER", Red, Black);
	
	DrawResetButton('S');
	gameCanRestart(1);
}


void DrawBackground(void){
	// Avrei dovuto implementare una funzione per disegnare le righe spesse...
	LCD_Clear(Black);
	//Linee orizzontali
	LCD_DrawLine(0, 0, 239, 0, Blue);
	LCD_DrawLine(0, 1, 239, 1, Blue);
	LCD_DrawLine(0, 2, 239, 2, Blue);
	
	LCD_DrawLine(7, 58, 49, 58, Blue);
	LCD_DrawLine(7, 59, 49, 59, Blue);
	LCD_DrawLine(7, 60, 49, 60, Blue);
	
	LCD_DrawLine(54, 58, 185, 58, Blue);
	LCD_DrawLine(54, 59, 185, 59, Blue);
	LCD_DrawLine(54, 60, 185, 60, Blue);
	
	LCD_DrawLine(190, 58, 232, 58, Blue);
	LCD_DrawLine(190, 59, 232, 59, Blue);
	LCD_DrawLine(190, 60, 232, 60, Blue);

	LCD_DrawLine(100, 65, 139, 65, Blue);
	LCD_DrawLine(100, 66, 139, 66, Blue);
	LCD_DrawLine(100, 67, 139, 67, Blue);
	
	LCD_DrawLine(137, 85, 146, 85, Blue);
	LCD_DrawLine(137, 86, 146, 86, Blue);
	LCD_DrawLine(137, 87, 146, 87, Blue);

	LCD_DrawLine(137, 150, 146, 150, Blue);
	LCD_DrawLine(137, 151, 146, 151, Blue);
	LCD_DrawLine(137, 152, 146, 152, Blue);

	LCD_DrawLine(100, 172, 139, 172, Blue);
	LCD_DrawLine(100, 173, 139, 173, Blue);
	LCD_DrawLine(100, 174, 139, 174, Blue);

	LCD_DrawLine(47, 179, 56, 179, Blue);
	LCD_DrawLine(47, 180, 56, 180, Blue);
	LCD_DrawLine(47, 181, 56, 181, Blue);
	
	LCD_DrawLine(93, 179, 146, 179, Blue);
	LCD_DrawLine(93, 180, 146, 180, Blue);
	LCD_DrawLine(93, 181, 146, 181, Blue);

	LCD_DrawLine(183, 177, 192, 177, Blue);
	LCD_DrawLine(183, 178, 192, 178, Blue);
	LCD_DrawLine(183, 179, 192, 179, Blue);
	
	LCD_DrawLine(7, 218, 55, 218, Blue);
	LCD_DrawLine(7, 219, 55, 219, Blue);
	LCD_DrawLine(7, 220, 55, 220, Blue);

	LCD_DrawLine(91, 218, 100, 218, Blue);
	LCD_DrawLine(91, 219, 100, 219, Blue);
	LCD_DrawLine(91, 220, 100, 220, Blue);

	LCD_DrawLine(139, 218, 232, 218, Blue);
	LCD_DrawLine(139, 219, 232, 219, Blue);
	LCD_DrawLine(139, 220, 232, 220, Blue);

	LCD_DrawLine(7, 225, 55, 225, Blue);
	LCD_DrawLine(7, 226, 55, 226, Blue);
	LCD_DrawLine(7, 227, 55, 227, Blue);

	LCD_DrawLine(146, 225, 232, 225, Blue);
	LCD_DrawLine(146, 226, 232, 226, Blue);
	LCD_DrawLine(146, 227, 232, 227, Blue);

	LCD_DrawLine(91, 249, 100, 249, Blue);
	LCD_DrawLine(91, 250, 100, 250, Blue);
	LCD_DrawLine(91, 251, 100, 251, Blue);

	LCD_DrawLine(139, 249, 148, 249, Blue);
	LCD_DrawLine(139, 250, 148, 250, Blue);
	LCD_DrawLine(139, 251, 148, 251, Blue);

	LCD_DrawLine(7, 280, 232, 280, Blue);
	LCD_DrawLine(7, 281, 232, 281, Blue);
	LCD_DrawLine(7, 282, 232, 282, Blue);

	LCD_DrawLine(0, 317, 239, 317, Blue);
	LCD_DrawLine(0, 318, 239, 318, Blue);
	LCD_DrawLine(0, 319, 239, 319, Blue);

	//Linee verticali
	LCD_DrawLine(0, 1, 0, 316, Blue);
	LCD_DrawLine(1, 1, 1, 316, Blue);
	LCD_DrawLine(2, 1, 2, 316, Blue);

	LCD_DrawLine(7, 61, 7, 217, Blue);
	LCD_DrawLine(8, 61, 8, 217, Blue);
	LCD_DrawLine(9, 61, 9, 217, Blue);

	LCD_DrawLine(7, 228, 7, 279, Blue);
	LCD_DrawLine(8, 228, 8, 279, Blue);
	LCD_DrawLine(9, 228, 9, 279, Blue);

	LCD_DrawLine(47, 61, 47, 178, Blue);
	LCD_DrawLine(48, 61, 48, 178, Blue);
	LCD_DrawLine(49, 61, 49, 178, Blue);

	LCD_DrawLine(54, 61, 54, 178, Blue);
	LCD_DrawLine(55, 61, 55, 178, Blue);
	LCD_DrawLine(56, 61, 56, 178, Blue);

	LCD_DrawLine(53, 221, 53, 224, Blue);
	LCD_DrawLine(54, 221, 54, 224, Blue);
	LCD_DrawLine(55, 221, 55, 224, Blue);

	LCD_DrawLine(93, 61, 93, 178, Blue);
	LCD_DrawLine(94, 61, 94, 178, Blue);
	LCD_DrawLine(95, 61, 95, 178, Blue);

	LCD_DrawLine(100, 68, 100, 171, Blue);
	LCD_DrawLine(101, 68, 101, 171, Blue);
	LCD_DrawLine(102, 68, 102, 171, Blue);

	LCD_DrawLine(137, 153, 137, 171, Blue);
	LCD_DrawLine(138, 153, 138, 171, Blue);
	LCD_DrawLine(139, 153, 139, 171, Blue);

	LCD_DrawLine(137, 68, 137, 84, Blue);
	LCD_DrawLine(138, 68, 138, 84, Blue);
	LCD_DrawLine(139, 68, 139, 84, Blue);

	LCD_DrawLine(144, 61, 144, 84, Blue);
	LCD_DrawLine(145, 61, 145, 84, Blue);
	LCD_DrawLine(146, 61, 146, 84, Blue);

	LCD_DrawLine(144, 153, 144, 178, Blue);
	LCD_DrawLine(145, 153, 145, 178, Blue);
	LCD_DrawLine(146, 153, 146, 178, Blue);

	LCD_DrawLine(139, 96, 139, 141, 0xFFDF); //Stanghetta bianchina
	LCD_DrawLine(140, 96, 140, 141, 0xFFDF);
	LCD_DrawLine(141, 96, 141, 141, 0xFFDF);
	LCD_DrawLine(142, 96, 142, 141, 0xFFDF);
	LCD_DrawLine(143, 96, 143, 141, 0xFFDF);

	LCD_DrawLine(183, 61, 183, 176, Blue);
	LCD_DrawLine(184, 61, 184, 176, Blue);
	LCD_DrawLine(185, 61, 185, 176, Blue);

	LCD_DrawLine(190, 61, 190, 176, Blue);
	LCD_DrawLine(191, 61, 191, 176, Blue);
	LCD_DrawLine(192, 61, 192, 176, Blue);

	LCD_DrawLine(91, 221, 91, 248, Blue);
	LCD_DrawLine(92, 221, 92, 248, Blue);
	LCD_DrawLine(93, 221, 93, 248, Blue);

	LCD_DrawLine(98, 221, 98, 248, Blue);
	LCD_DrawLine(99, 221, 99, 248, Blue);
	LCD_DrawLine(100, 221, 100, 248, Blue);

	LCD_DrawLine(139, 221, 139, 248, Blue);
	LCD_DrawLine(140, 221, 140, 248, Blue);
	LCD_DrawLine(141, 221, 141, 248, Blue);

	LCD_DrawLine(146, 225, 146, 248, Blue);
	LCD_DrawLine(147, 225, 147, 248, Blue);
	LCD_DrawLine(148, 225, 148, 248, Blue);

	LCD_DrawLine(183, 61, 183, 61, Blue);
	LCD_DrawLine(184, 61, 184, 61, Blue);
	LCD_DrawLine(185, 61, 185, 61, Blue);

	LCD_DrawLine(230, 61, 230, 217, Blue);
	LCD_DrawLine(231, 61, 231, 217, Blue);
	LCD_DrawLine(232, 61, 232, 217, Blue);
	
	LCD_DrawLine(230, 228, 230, 279, Blue);
	LCD_DrawLine(231, 228, 231, 279, Blue);
	LCD_DrawLine(232, 228, 232, 279, Blue);

	LCD_DrawLine(237, 2, 237, 316, Blue);
	LCD_DrawLine(238, 2, 238, 316, Blue);
	LCD_DrawLine(239, 2, 239, 316, Blue);
}

void play_startup_sound(void){
	uint16_t noteNumber = (sizeof(pacman_sound_startup)/sizeof(pacman_sound_startup[0]));
	while(currentNote < noteNumber){
		if(!isNotePlaying())
			{
				++ticks;
				if(ticks == UPTICKS)
				{
					ticks = 0;
					playNote(pacman_sound_startup[currentNote++]);
				}
			}
	}
	currentNote = 0;
	ticks = 0;
}

void play_death_sound(void){
	uint16_t noteNumber = (sizeof(pacman_sound_death)/sizeof(pacman_sound_death[0]));
	while(currentNote < noteNumber){
		if(!isNotePlaying())
			{
				++ticks;
				if(ticks == UPTICKS)
				{
					ticks = 0;
					playNote(pacman_sound_death[currentNote++]);
				}
			}
	}
	currentNote = 0;
	ticks = 0;
}

void play_eat_sound(void){
	uint16_t noteNumber = (sizeof(pacman_sound_eat)/sizeof(pacman_sound_eat[0]));
	while(currentNote < noteNumber){
		if(!isNotePlaying())
			{
				++ticks;
				if(ticks == UPTICKS)
				{
					ticks = 0;
					playNote(pacman_sound_eat[currentNote++]);
				}
			}
	}
	currentNote = 0;
	ticks = 0;
}

void play_pet_sound(void){
	uint16_t noteNumber = (sizeof(pacman_sound_pet)/sizeof(pacman_sound_pet[0]));
	while(currentNote < noteNumber){
		if(!isNotePlaying())
			{
				++ticks;
				if(ticks == UPTICKS)
				{
					ticks = 0;
					playNote(pacman_sound_pet[currentNote++]);
				}
			}
	}
	currentNote = 0;
	ticks = 0;
}


