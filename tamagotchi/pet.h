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
#endif 

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
