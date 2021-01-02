/*
** Seniriu
** Matthew Suttinger & Emerald Nova (emeraldnovagames@gmail.com)
** 
** This work is licensed under a Attribution-NonCommercial 4.0 International License
** More info at: https://creativecommons.org/licenses/by-nc/4.0/legalcode
*/

#ifndef __TIMER_H__
#define __TIMER_H__

#include <jo/jo.h>

// Pointer to SH2 Registers, found by Johannes Fetz, contributed by Ponut64
// High Free Running Counter Register (FCR), counts up to 255, then iterates FCR Low
extern Uint8 * SH2FRCHigh;
// Low Free Running Counter Register (FCR), increases every time FCR high reaches 256
extern Uint8 * SH2FRCLow;
// Time Control Register (TCR)
extern Uint8 * SH2TCR;
// System clock
extern unsigned int * SysClockReg;
//	Time tracking in seconds
extern FIXED time;
extern FIXED oldtime;
extern FIXED dt;

//	Functions
void timer(void);

#endif


