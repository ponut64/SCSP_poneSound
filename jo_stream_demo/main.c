
#include <jo/jo.h>
#include "pcmsys.h"
#include "pcmstm.h"
#include "input.h"

#define LWRAM	(2097152)

extern Sint8 SynchConst; //SGL System Variable
int framerate;

void * loading_system_scratch_buffer = (void*)LWRAM;

void	update_gamespeed(void)
{
	int frmrt = delta_time>>6;
	jo_fixed_point_time();
	
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
		
		if(is_key_down(DIGI_START) && is_key_down(DIGI_A) && is_key_down(DIGI_B) && is_key_down(DIGI_C))
		{
			SYS_Exit(0);
		}
}

//////////////////////////////////////////////////////////////////////////////
//Sound Numbers
//////////////////////////////////////////////////////////////////////////////
int snd_adx = 0;
int snd_exert = 0;
//////////////////////////////////////////////////////////////////////////////

void			my_load(void)
{

	snd_adx = add_adx_front_buffer(23040);
	add_adx_back_buffer((void*)LWRAM);
	
	snd_exert = load_8bit_pcm((Sint8*)"EXERT.PCM", 11520);

}

void			my_draw(void)
{
	update_gamespeed();

	jo_printf(1, 5, "Welcome to the streaming sound demo.");
	jo_printf(1, 6, "Press A to hear about Gordon. (ADX)");
	jo_printf(1, 7, "Press Z to hear about animes. (ADX)");
	jo_printf(1, 8, "These are ADX streams. Only one at a time.");
	jo_printf(1, 9, "The ADX streams can be as long as you like.");
	jo_printf(1, 10, "Notice how quickly they start playing!");
	jo_printf(1, 11, "Press B to stop an ADX stream.");
	
	jo_printf(1, 13, "Press X to start playing music.");
	jo_printf(1, 14, "The music is a raw PCM stream.");
	jo_printf(1, 15, "Notice how long it takes to buffer?");
	jo_printf(1, 16, "Press Y to stop the PCM stream.");
	jo_printf(1, 17, "The PCM stream will loop a set # of times.");
	
	jo_printf(1, 19, "ADX and PCM can stream simultaneously.");

	jo_printf(1, 21, "Lastly, you can press C to play a PCM.");
	jo_printf(1, 22, "Have fun with the source code ...");
	jo_printf(1, 23, "It's a mess! I love it!");
	
	if(is_key_pressed(DIGI_A))
	{
	start_adx_stream((Sint8*)"GORDON.ADX", 6);
	}
	
	if(is_key_pressed(DIGI_Z))
	{
	start_adx_stream((Sint8*)"ANIMES.ADX", 6);
	}
	
	if(is_key_pressed(DIGI_B))
	{
		stop_adx_stream();
	}

	if(is_key_pressed(DIGI_X))
	{
		start_pcm_stream((Sint8*)"MGEAR.PCM", 5);
		stm.times_to_loop = 1;
	}
	
	if(is_key_pressed(DIGI_Y))
	{
		stop_pcm_stream();
		stm.times_to_loop = 0;
	}
	
	if(is_key_pressed(DIGI_C))
	{
		pcm_play(snd_exert, PCM_SEMI, 7);
	}

}

void			handle_the_text_file(void * location_in_memory)
{
	
	//Nothing.
	char * text = (char *)location_in_memory;
	
	jo_printf(0, 14, "text(%c)", *text);
}

void			vblanker(void)
{
	
	//jo_printf(0, 20, "dbg0(%i)", m68k_com->adx_stream_comm);
	// jo_printf(0, 20, "atm0(%i)", m68k_com->adx_buffer_pass[0]);
	// jo_printf(0, 21, "atm1(%i)", m68k_com->adx_buffer_pass[1]);
	// jo_printf(0, 22, "cf2(%i)", m68k_com->drv_adx_coef_1);
	// jo_printf(0, 23, "apm(%i)", m68k_com->pcmCtrl[snd_adx].sh2_permit);
	
	operate_digital_pad1();
	sdrv_stm_vblank_rq();
}

void			jo_main(void)
{

	jo_core_init(JO_COLOR_Black);
	SynchConst=2;  
	load_drv(ADX_MASTER_2304);
	my_load();
	

	//generic_file_sys_id = GFS_NameToId((Sint8*)"TSTF.TXT");
	//file_handler_function = handle_the_text_file;
	//file_setup_requested = true;
	
	slIntFunction(vblanker);
	pcm_stream_init(30720, PCM_TYPE_8BIT);
	pcm_stream_host(my_draw);
}

/*
** END OF FILE
*/

