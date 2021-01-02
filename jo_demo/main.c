
#include <jo/jo.h>
#include "pcmsys.h"

int framerate;

//Sound Numbers
short exertSnd;
short winSnd;
short stahpSnd;
//

void	update_gamespeed(void)
{
	// "fmrt" - a representation of the delta time as some division of vblank periods (1 for 60hz, 2 for 30hz, 3 for 20hz, 4 for 15hz).
	int frmrt = delta_time>>6;
	jo_fixed_point_time();

	// "lastTimes" - a list of the last 66 frametimes (relatively vague approximations anyway).
 	static int lastTimes[66];
	// "time_selector" - the entry into last times being written to.
	static int time_selector = 0;
	// "bad_frames" - the # of frames since startup that have been over 40ms. Maybe change that to 17ms for 60hz? 
	static int bad_frames = 0;
	
	lastTimes[time_selector] = frmrt;
	bad_frames += (frmrt > 40) ? 1 : 0;
	time_selector = (time_selector > 66) ? 0 : time_selector+1;
	
    framerate = (frmrt)>>4;
	slPrintFX(delta_time, slLocate(0, 3));
	
    if (framerate <= 0) framerate=1;
    else if (framerate > 5) framerate=5;
	//

		//Framegraph
	char curLine = frmrt;
	char prevLine = (time_selector < 1) ? lastTimes[65] : lastTimes[time_selector-1];
	char nthLine = (time_selector < 2) ? lastTimes[65] : lastTimes[time_selector-2];

	jo_draw_background_line(time_selector+4, 22, time_selector+4, 8, 0xC210);
	jo_draw_background_line(time_selector+4, 22, time_selector+4, (curLine>>2)+6, 0x8200);
		if(time_selector > 1){
	jo_draw_background_line((time_selector-1)+4, 22, (time_selector-1)+4, (prevLine>>2)+6, 0xC000);
		}
		if(time_selector > 2){
	jo_draw_background_line((time_selector-2)+4, 22, (time_selector-2)+4, (nthLine>>2)+6, 0x8010);
		} 
		//
}


void			my_draw(void)
{
	
	update_gamespeed();
	
	jo_printf(0, 5, "P64 PCM Driver Usage Demo");
	jo_printf(0, 6, "See lines 71, 72, and 73 of main.c");
	jo_printf(0, 8, "Press A to start a semi-protected sound");
	jo_printf(0, 9, "(will only start this sound type)");
	jo_printf(0, 10, "(will restart whenever told to play)");
	jo_printf(0, 12, "(Hold B to start an alt-looping sound.)");
	jo_printf(0, 13, "Release to stop the sound.)");
	jo_printf(0, 15, "Hold C to repeat a protected sound");
	jo_printf(0, 16, "(this sound type plays while true)");
	jo_printf(0, 17, "(and will only restart when done)");
	
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
	pcm_play(stahpSnd, PCM_PROTECTED, 6);
	}
	
	if(jo_is_input_key_pressed(0, JO_KEY_Y))
	{
	pcm_parameter_change(winSnd, 5, PCM_PAN_LEFT);
	} else {
	pcm_parameter_change(winSnd, 5, PCM_PAN_RIGHT);
	}
	
	//slSynch();
}

void			sdrv_vblank_rq(void)
{
	m68k_com->start = 1;
	m68k_com->dT_ms = delta_time>>6; //The driver currently doesn't need this, but you may as well let it know, yeah?
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
	
	jo_core_add_vblank_callback(sdrv_vblank_rq);
	jo_core_add_callback(my_draw);
	jo_core_run();
}

/*
** END OF FILE
*/

