#include "timer.h"
#include <jo/jo.h>

// Pointer to SH2 Registers, found by Johannes Fetz, contributed by Ponut64
// High Free Running Counter Register (FCR), counts up to 255, then iterates FCR Low
Uint8 * SH2FRCHigh = (Uint8 *)0xfffffe12;
// Low Free Running Counter Register (FCR), increases every time FCR high reaches 256
Uint8 * SH2FRCLow = (Uint8 *)0xfffffe13;
// Time Control Register (TCR)
Uint8 * SH2TCR = (Uint8 *)0xfffffe16;
// System clock
unsigned int * SysClockReg = (unsigned int*)0x6000324;
//	Time tracking in seconds
FIXED time = 0;
FIXED oldtime = 0;
FIXED dt = 0;
Uint16 delta_time = 1;

//	JO Engine sourced timer adaptation
void timer(void)
{
	//	Set old time for iteration
	oldtime = time;
	
	// Get System Clock Value
	unsigned int SysClock = (*(unsigned int*)0x6000324);
	
	
	FIXED time_add =
		toFIXED(
		//	Clock speed from framerate based on resolution register and NSTC vs PAL
		(((*(Uint16 *)0x25f80004 & 0x1) == 0x1) ?
			((SysClock == 0) ? (float)0.037470726 : (float)0.035164835 ) :
			((SysClock == 0) ? (float)0.037210548 : (float)0.03492059 ))
			*
		//	Get Free Running Counter value
		((*(unsigned char *)SH2FRCHigh) << 8 | (*(unsigned char *)SH2FRCLow))
		*
		//	Determine if clock is on 1/8, 1/32, or 1/128 of count
		(8 << (((*(unsigned char *)RegisterTCR) & 3) << 1)) /
		//	Set to s
		1000000);

	//	Set new time
	time += time_add;
	dt = time - oldtime;
	
	//	Reset FRC's
	(*(unsigned char *)SH2FRCHigh) = 0 >> 8;
	(*(unsigned char *)SH2FRCLow) = 0;
}


