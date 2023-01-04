#ifndef __PET_H
#define __PET_H

#include <stdint.h>

/*	User function	protoypes --------------------------------------------------*/

void pet_animation_idle1(int x_offset, int y_offset);
void pet_animation_idle2(int x_offset, int y_offset);
void pet_animation_death(int x_offset, int y_offset);
void pet_animation_snack(int x_offset, int y_offset);
void pet_animation_play(int x_offset, int y_offset);
void draw_something(int x_offset, int y_offset, uint16_t* pixel_array, int size);

void stats_init_satiety_ghosts(void);
void stats_init_happiness_pacman(void);

void stats_satiety_ghosts(uint8_t option, uint8_t new_amount);
void stats_happiness_pacman(uint8_t option, uint8_t new_amount);

#endif 

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
