
#include <jo/jo.h>
#include "timer.h"
#include "pcmsys.h"
#include "input.h"
#include "pcm_stm.h"

extern Sint8 SynchConst; //SGL System Variable
int framerate;

//Sound Numbers
short exertSnd;
short winSnd;
short stahpSnd;
//

void	update_gamespeed(void)
{
	int frmrt = dt>>6;
	timer();
	
 	static int lastTimes[66];
	static int time_selector = 0;
	static int bad_frames = 0;
	
	lastTimes[time_selector] = frmrt;
	bad_frames += (frmrt > 40) ? 1 : 0;
	time_selector = (time_selector > 66) ? 0 : time_selector+1;
	
    framerate = (frmrt)>>4;
	jo_printf(0, 3, "(%i) Bad Frames)", bad_frames);
	
    if (framerate <= 0) framerate=1;
    else if (framerate > 5) framerate=5;

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
	
	if(is_key_struck(DIGI_A))
	{
	pcm_play(winSnd, PCM_SEMI, 6);
	}
	
	if(is_key_struck(DIGI_B))
	{
	pcm_play(exertSnd, PCM_ALT_LOOP, 6);
	} else if(is_key_release(DIGI_B)){
	pcm_cease(exertSnd);
	}
	
	if(is_key_pressed(DIGI_C))
	{
	pcm_play(stahpSnd, PCM_PROTECTED, 6);
	}
	
	slSynch();
}

void			run_the_game(void)
{
	do{
	master_file_system(my_draw);
	}while(1);
}

void			sdrv_vblank_rq(void)
{
	m68k_com->start = 1;
	m68k_com->dT_ms = dt>>6;
	music_vblIn();
	operate_digital_pad1();
}

void			jo_main(void)
{
	slDynamicFrame(ON); 
    SynchConst=2;  
	jo_core_init(JO_COLOR_Black);

	load_drv();
	
	 winSnd = load_16bit_pcm((Sint8 *)"WIN.PCM", 15360);
	 exertSnd = load_8bit_pcm((Sint8 *)"EXERT.PCM", 15360);
	 stahpSnd = load_8bit_pcm((Sint8 *)"STAHP.PCM", 15360);
	
	slIntFunction(sdrv_vblank_rq);
	init_music('L', (Sint8*)"EVE.MUS", 7);
	run_the_game();
}

/*
** END OF FILE
*/

