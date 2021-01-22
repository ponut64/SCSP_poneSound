
#include <jo/jo.h>
#include "pcmsys.h"
#include <SEGA_INT.h>

int framerate;

//Sound Numbers
short exertSnd;
short winSnd;
short stahpSnd;
short aweSnd;
//

void			my_draw(void)
{
	
	 jo_printf(0, 5, "P64 PCM Driver Usage Demo");
	jo_printf(0, 8, "Press A to start a semi-protected sound");
	jo_printf(0, 9, "(will only start this sound type)");
	jo_printf(0, 10, "(will restart whenever told to play)");
	jo_printf(0, 12, "(Hold B to start an alt-looping sound.");
	jo_printf(0, 13, "Release to stop the sound.)");
	jo_printf(0, 15, "Hold C to repeat a protected sound");
	jo_printf(0, 16, "(this sound type plays while true)");
	jo_printf(0, 17, "(and will only restart when done)");
	
	// jo_printf(0, 18, "Y pans sound from A button");
	
	if(jo_is_input_key_down(0, JO_KEY_A))
	{
	pcm_play(winSnd, PCM_SEMI, 6);
	}
	
	if(jo_is_input_key_pressed(0, JO_KEY_B))
	{
		jo_printf(0, 21, "(1)");
	pcm_play(exertSnd, PCM_ALT_LOOP, 6);
	} else {
		jo_printf(0, 21, "(0)");
	pcm_cease(exertSnd);
	}
	
	if(jo_is_input_key_pressed(0, JO_KEY_C))
	{
	pcm_play(aweSnd, PCM_PROTECTED, 6);
	}
	
	if(jo_is_input_key_pressed(0, JO_KEY_Y))
	{
	//pcm_parameter_change(winSnd, 5, PCM_PAN_LEFT);
	
	} else {
	//pcm_parameter_change(winSnd, 5, PCM_PAN_RIGHT);
	}

	unsigned int * dummy = (unsigned int *)(SNDRAM);

	//slSynch();
}

void			sdrv_vblank_rq(void)
{
	m68k_com->start = 1;
}

void			jo_main(void)
{
	jo_core_init(JO_COLOR_Black);

	load_drv();
	
	/*
	To convert a sound to 16-bit
	ffmpeg -i %this%.wav -f s16be -ac 1 -ar (bitrate) %this%.PCM
	To convert a sound to 8-bit
	ffmpeg -i %this%.wav -f s8 -ac 1 -ar (bitrate) %this%.PCM
	*/
	 winSnd = load_16bit_pcm((Sint8 *)"WIN.PCM", 15360);
	 exertSnd = load_8bit_pcm((Sint8 *)"EXERT.PCM", 15360);
	 stahpSnd = load_8bit_pcm((Sint8 *)"STAHP.PCM", 15360);
	 aweSnd = load_8bit_pcm((Sint8 *)"AWSUM.PCM", 15360);
	 
	
	jo_core_add_vblank_callback(sdrv_vblank_rq);
	jo_core_add_callback(my_draw);
	jo_core_run();
}

/*
** END OF FILE
*/

