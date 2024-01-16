
#include <jo/jo.h>
#include "pcmsys.h"

int framerate;

//Sound Numbers
short pcm8snd;
short pcm16snd;
short adx4snd;
//

void			my_draw(void)
{
	jo_printf(0, 5, "P64 PCM + CD-DA Usage Demo");
	jo_printf(0, 7, "Simple warnings:");
	jo_printf(0, 8, "1. Be VERY CAREFUL with the track setting.");
	jo_printf(0, 9, "Compile first, then check the '.cue' file.");
	jo_printf(0, 10, "Select tracks accordingly, and recompile.");
	
	jo_printf(0, 12, "2. Redbook audio tracks MUST be stereo.");
	jo_printf(0, 13, "Should be be 16-bit wav files.");
	jo_printf(0, 14, "Some CD build tools will auto-convert.");
	jo_printf(0, 15, "No matter what format they are originally,");
	jo_printf(0, 16, "they'll be specially encoded as audio tracks");
	jo_printf(0, 17, "Redbook tracks are 44.1 KHz, Stereo, 16-bit.");
	
	jo_printf(0, 19, "3. Redbook tracks are huge.");
	jo_printf(0, 20, "Even for a small project, be careful.");
	jo_printf(0, 21, "You could run out of CD space using CDDA.");
	
	jo_printf(0, 24, "Press Z to start CD-DA");
	jo_printf(0, 25, "Press Y to make CD-DA quiet");
	
	// jo_printf(0, 18, "Y pans sound from A button");
	
	if(jo_is_input_key_down(0, JO_KEY_A))
	{
	pcm_play(adx4snd, PCM_SEMI, 7);
	}
	
	if(jo_is_input_key_pressed(0, JO_KEY_B))
	{
		//jo_printf(0, 14, "(--Loop Play--)");
	pcm_play(pcm16snd, PCM_ALT_LOOP, 6);
	} else {
		//jo_printf(0, 14, "(--Loop Stop--)");
	pcm_cease(pcm16snd);
	}
	
	if(jo_is_input_key_pressed(0, JO_KEY_C))
	{
	pcm_play(pcm8snd, PCM_PROTECTED, 6);
	}
	
	if(jo_is_input_key_pressed(0, JO_KEY_Z))
	{
		CDDA_PlaySingle(2, true);
	}
	
	if(jo_is_input_key_pressed(0, JO_KEY_Y))
	{
		CDDA_SetVolume(2);
	}
	
	if(jo_is_input_key_pressed(0, JO_KEY_X))
	{
		pcm_cease(adx4snd);
	}
	
	//slSynch();
}

void			jo_main(void)
{
	jo_core_init(JO_COLOR_Black);

	load_drv(ADX_MASTER_2304);
	////////////////////////////////////////////////
	// REMINDER: All file names must comply with the 8.3 standard.
	// File extensions can be no longer than 3 letters.
	// File names can be no longer than 8 letters.
	// The total length is thusly 12 characters (as there is a period).
	////////////////////////////////////////////////
	/*
	To convert a sound to 16-bit
	ffmpeg -i %this%.wav -f s16be -ac 1 -ar (bitrate) %this%.PCM
	To convert a sound to 8-bit
	ffmpeg -i %this%.wav -f s8 -ac 1 -ar (bitrate) %this%.PCM
	*/
	 pcm16snd = load_16bit_pcm((Sint8 *)"DEF_FLAG.PCM", 15360);
	 pcm8snd = load_8bit_pcm((Sint8 *)"HAV_FLAG.PCM", 15360);
	 adx4snd = load_adx((Sint8 *)"NBGM.ADX");

	slZoomNbg0(65535, 73720);
	jo_core_add_vblank_callback(sdrv_vblank_rq);
	jo_core_add_callback(my_draw);
	jo_core_run();
}

/*
** END OF FILE
*/

