
#include <jo/jo.h>
#include "timer.h"
#include "pcmsys.h"
#include "input.h"

extern Sint8 SynchConst; //SGL System Variable
int framerate;

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


void	get_file_in_memory(Sint8 * filename, void * destination)
{

	GfsHn gfs_tga;
	Sint32 sector_count;
	Sint32 file_size;
	
	Sint32 local_name = GFS_NameToId(filename);

//Open GFS
	gfs_tga = GFS_Open((Sint32)local_name);
//Get sectors
	GFS_GetFileSize(gfs_tga, NULL, &sector_count, NULL);
	GFS_GetFileInfo(gfs_tga, NULL, NULL, &file_size, NULL);
	
	GFS_Close(gfs_tga);
	
	GFS_Load(local_name, 0, (Uint32 *)destination, file_size);

}


void			my_draw(void)
{

	short winSnd = load_16bit_pcm((Sint8 *)"WIN.PCM", 15360);
	short cronchSnd = load_16bit_pcm((Sint8 *)"CRONCH.PCM", 15360);
	short clickSnd = load_16bit_pcm((Sint8 *)"CLCK1.PCM", 15360);
	
while(1)
{
	update_gamespeed();
	
	jo_printf(0, 5, "P64 PCM Driver Usage Demo");
	jo_printf(0, 6, "See lines 71, 72, and 73 of main.c");
	jo_printf(0, 8, "Press A to initiate a semi-protected sound");
	jo_printf(0, 10, "(Hold B to initiate a reverse-looping sound. )");
	jo_printf(0, 11, "Release to stop the sound.)");
	jo_printf(0, 13, "Hold C to repeat a protected sound");
	
	if(is_key_struck(DIGI_A))
	{
	pcm_play(winSnd, PCM_SEMI, 6);
	}
	
	if(is_key_struck(DIGI_B))
	{
	pcm_play(cronchSnd, PCM_RVS_LOOP, 6);
	} else if(is_key_release(DIGI_B)){
	pcm_cease(cronchSnd);
	}
	
	if(is_key_pressed(DIGI_C))
	{
	pcm_play(clickSnd, PCM_PROTECTED, 6);
	}
	
	slSynch();
}
}

void			sdrv_vblank_rq(void)
{
	operate_digital_pad1();
	m68k_com->start = 1;
	m68k_com->dT_ms = dt>>6;
}

void			jo_main(void)
{
	slDynamicFrame(ON); 
    SynchConst=2;  
	jo_core_init(JO_COLOR_Black);

	load_drv();
	
	slIntFunction(sdrv_vblank_rq);
	my_draw();
}

/*
** END OF FILE
*/

