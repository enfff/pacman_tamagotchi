#ifndef __PET_H
#define __PET_H

#include <stdint.h>

/*	User function	protoypes --------------------------------------------------*/

void pet_animation_idle1(void);
void pet_animation_idle2(void);

void pet_animation_death(int x_offset, int y_offset);
void pet_animation_death1(int x_offset, int y_offset);
void pet_animation_death2(int x_offset, int y_offset);
void pet_animation_death3(int x_offset, int y_offset);
void pet_animation_death4(int x_offset, int y_offset);
void pet_animation_death5(int x_offset, int y_offset);
void pet_animation_death6(int x_offset, int y_offset);

void pet_animation_pet1(int x_offset, int y_offset);
void pet_animation_pet2(int x_offset, int y_offset);
void pet_animation_pet3(int x_offset, int y_offset);
void pet_animation_pet4(int x_offset, int y_offset);

void pet_animation_pursuit1(uint8_t k);
void pet_animation_pursuit2(uint8_t k);
void pet_animation_snack(int x_offset, int y_offset);
void pet_animation_play(int x_offset, int y_offset);
void draw_something(int x_offset, int y_offset, uint16_t* pixel_array, int size);

void draw_pet_snack(void); // la fragola
void draw_pet_play(void); // quello spaventato che si deve mangiare

void pet_clear_animation_pursuit(void);
void draw_speaker_volume(uint8_t volume_amount);

void stats_init_satiety_ghosts(void);
void stats_init_happiness_pacman(void);
void stats_satiety_ghosts(uint8_t option, uint8_t new_amount);
void stats_happiness_pacman(uint8_t option, uint8_t new_amount);

#endif 

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
