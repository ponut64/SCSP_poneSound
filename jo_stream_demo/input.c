//
//input.c
//this file is compiled separately
//Partially sourced from libyaul
//Directly accesses hardware registers and thus is library agnostic.
//Though I don't start the SMPC or set a peripheral mode. Dear god why is sampling inputs so complex? Ugh!

#include <jo/jo.h>
#include "input.h"

//There are 32 of these
//2-bytes aligned
#define SMPC_OREG_START ((unsigned char *)0x20100021)
#define SMPC_IREG1 ((unsigned char *)0x20100003)
unsigned char * oregs = SMPC_OREG_START;
unsigned char * ireg1 = SMPC_IREG1;

digital_pad pad1 = {.pressed = 0xFFFF,
					.prevPressed = 0xFFFF,
					.up = 0,
					.down = 0xFFFF,
					.change = 0xFFFF,
					.toggle = 0xFFFF};

void	operate_digital_pad1(void)
{
	pad1.pressed = oregs[6] | (oregs[4]<<8); //Holds current frame data
	
	pad1.change = pad1.pressed ^ pad1.prevPressed;
	
	pad1.up ^= pad1.change;
	pad1.down = (pad1.change != 0) ? pad1.down ^ pad1.change : pad1.down;
	
	pad1.toggle ^= (pad1.change != 0) ? pad1.up : 0;
	
	pad1.prevPressed = pad1.pressed;
}

int	is_key_pressed(int keyPattern)
{
	if( (pad1.pressed & keyPattern) != keyPattern)
	{
		return 1;
	} else {
		return 0;
	}
}

int	is_key_up(int keyPattern)
{
	if( (pad1.up & keyPattern) != keyPattern)
	{
		return 1;
	} else {
		return 0;
	}
}

int	is_key_down(int keyPattern)
{
	if( (pad1.down & keyPattern) != keyPattern)
	{
		return 1;
	} else {
		return 0;
	}
}


int	is_key_change(int keyPattern)
{
	if( (pad1.change & keyPattern) == keyPattern)
	{
		return 1;
	} else {
		return 0;
	}
}

int	is_key_toggle(int keyPattern)
{
	if( (pad1.toggle & keyPattern) != keyPattern)
	{
		return 1;
	} else {
		return 0;
	}
}

int is_key_release(int keyPattern)
{
	return (is_key_up(keyPattern) & is_key_change(keyPattern));
}

int is_key_struck(int keyPattern)
{
	return (is_key_down(keyPattern) & is_key_change(keyPattern));
}


