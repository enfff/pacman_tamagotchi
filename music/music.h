#ifndef MUSIC_H
#define MUSIC_H

#include <stdint.h>
#include "LPC17xx.H" 

//Default: 1.65
#define SPEEDUP 1.6

#define TIMERSCALER 1

#define SECOND 0x17D7840 * TIMERSCALER

typedef char BOOL;
#define TRUE 1
#define FALSE 0


typedef enum note_durations
{
	time_semibiscroma = (unsigned int)(SECOND * SPEEDUP / 64.0f + 0.5), // 1/128
	time_biscroma = (unsigned int)(SECOND * SPEEDUP / 32.0f + 0.5), // 1/64
	time_semicroma = (unsigned int)(SECOND * SPEEDUP / 16.0f + 0.5), // 1/32
	time_croma = (unsigned int)(SECOND * SPEEDUP / 8.0f + 0.5), // 1/16
	time_semiminima = (unsigned int)(SECOND * SPEEDUP / 4.0f + 0.5), // 1/4
	time_minima = (unsigned int)(SECOND * SPEEDUP / 2.0f + 0.5), // 1/2
	time_semibreve = (unsigned int)(SECOND * SPEEDUP + 0.5), // 1
} NOTE_DURATION;


/* k=1/f'*f/n  k=f/(f'*n) k=25MHz/(f'*45) */

/* f' la nota da https://pages.mtu.edu/~suits/notefreqs.html*/

typedef enum frequencies
{
c0 = 36193,
db0 = 32076,
d0 = 30275,
eb0 = 28563, 
e0 = 26969,
f0 = 25449,
gb0 = 24029,
g0 = 22676,
ab0 = 21400,
a0 = 20202,
bb0 = 19065,
b0 = 17997,

c1 = (uint16_t) c0/2,
db1 = (uint16_t) db0/2,
d1 = (uint16_t) d0/2,
eb1 = (uint16_t) eb0/2,
e1 = (uint16_t) e0/2,
f1 = (uint16_t) f0/2,
gb1 = (uint16_t) gb0/2,
g1 = (uint16_t) g0/2,
ab1 = (uint16_t) ab0/2,
a1 = (uint16_t) a0/2,
bb1 = (uint16_t) bb0/2,
b1 = (uint16_t) b0/2,

c2 = (uint16_t) c0/4,
db2 = (uint16_t) db0/4,
d2 = (uint16_t) d0/4,
eb2 = (uint16_t) eb0/4,
e2 = (uint16_t) e0/4,
f2 = (uint16_t) f0/4,
gb2 = (uint16_t) gb0/4,
g2 = (uint16_t) g0/4,
ab2 = (uint16_t) ab0/4,
a2 = (uint16_t) a0/4,
bb2 = (uint16_t) bb0/4,
b2 = (uint16_t) b0/4,

c3 = (uint16_t) c0/8,
db3 = (uint16_t) db0/8,
d3 = (uint16_t) d0/8,
eb3 = (uint16_t) eb0/8,
e3 = (uint16_t) e0/8,
f3 = (uint16_t) f0/8,
gb3 = (uint16_t) gb0/8,
g3 = (uint16_t) g0/8,
ab3 = (uint16_t) ab0/8,
a3 = (uint16_t) a0/8,
bb3 = (uint16_t) bb0/8,
b3 = (uint16_t) b0/8,

c4 = (uint16_t) c0/16,
db4 = (uint16_t) db0/16,
d4 = (uint16_t) d0/16,
eb4 = (uint16_t) eb0/16,
e4 = (uint16_t) e0/16,
f4 = (uint16_t) f0/16,
gb4 = (uint16_t) gb0/16,
g4 = (uint16_t) g0/16,
ab4 = (uint16_t) ab0/16,
a4 = (uint16_t) a0/16,
bb4 = (uint16_t) bb0/16,
b4 = (uint16_t) b0/16,

c5 = (uint16_t) c0/32,
db5 = (uint16_t) db0/32,
d5 = (uint16_t) d0/32,
eb5 = (uint16_t) eb0/32,
e5 = (uint16_t) e0/32,
f5 = (uint16_t) f0/32,
gb5 = (uint16_t) gb0/32,
g5 = (uint16_t) g0/32,
ab5 = (uint16_t) ab0/32,
a5 = (uint16_t) a0/32,
bb5 = (uint16_t) bb0/32,
b5 = (uint16_t) b0/32,

c6 = (uint16_t) c0/64,
db6 = (uint16_t) db0/64,
d6 = (uint16_t) d0/64,
eb6 = (uint16_t) eb0/64,
e6 = (uint16_t) e0/64,
f6 = (uint16_t) f0/64,
gb6 = (uint16_t) gb0/64,
g6 = (uint16_t) g0/64,
ab6 = (uint16_t) ab0/64,
a6 = (uint16_t) a0/64,
bb6 = (uint16_t) bb0/64,
b6 = (uint16_t) b0/64,

c7 = (uint16_t) c0/128,
db7 = (uint16_t) db0/128,
d7 = (uint16_t) d0/128,
eb7 = (uint16_t) eb0/128,
e7 = (uint16_t) e0/128,
f7 = (uint16_t) f0/128,
gb7 = (uint16_t) gb0/128,
g7 = (uint16_t) g0/128,
ab7 = (uint16_t) ab0/128,
a7 = (uint16_t) a0/128,
bb7 = (uint16_t) bb0/128,
b7 = (uint16_t) b0/128,

pause = 0
} FREQUENCY;


typedef struct 
{
	FREQUENCY freq;
	NOTE_DURATION duration;
} NOTE;

void playNote(NOTE note);
BOOL isNotePlaying(void);

#endif
/* EOF */
