
#include <jo/jo.h>
#include "pcmsys.h"

int framerate;

//Sound Numbers
short pcm8snd;
short pcm16snd;
short adx4snd;
//

//
// UP NEXT: Multi-PCM Stream
//

void			my_draw(void)
{
	jo_printf(0, 5, "P64 PCM Driver Usage Demo");
	jo_printf(0, 8, "A to start an ADX semi-protected sound");
	jo_printf(0, 9, "(will only start this sound type)");
	jo_printf(0, 10, "(will restart whenever told to play)");
	jo_printf(0, 12, "(Hold B to start a 16-bit alt-looping sound.");
	jo_printf(0, 13, "Release to stop the sound.)");
	jo_printf(0, 16, "Hold C to repeat an 8-bit protected sound");
	jo_printf(0, 17, "(this sound type plays while true)");
	jo_printf(0, 18, "(and will only restart when done)");
	
	jo_printf(0, 20, "The ADX bitrate in this demo is 23040.");
	jo_printf(0, 21, "23040, 15360, 11520, or 7680Hz can be used.");
	jo_printf(0, 22, "ADX decompression is done in real-time.");
	jo_printf(0, 23, "The driver may only properly decompress one");
	jo_printf(0, 24, "bitrate of ADX, selected at startup.");
	
	// jo_printf(0, 18, "Y pans sound from A button");
	
	if(jo_is_input_key_down(0, JO_KEY_A))
	{
	pcm_play(adx4snd, PCM_SEMI, 7);
	}
	
	if(jo_is_input_key_pressed(0, JO_KEY_B))
	{
		jo_printf(0, 14, "(--Loop Play--)");
	pcm_play(pcm16snd, PCM_ALT_LOOP, 6);
	} else {
		jo_printf(0, 14, "(--Loop Stop--)");
	pcm_cease(pcm16snd);
	}
	
	if(jo_is_input_key_pressed(0, JO_KEY_C))
	{
	pcm_play(pcm8snd, PCM_PROTECTED, 6);
	}
	
	//slSynch();
}

void			jo_main(void)
{
	jo_core_init(JO_COLOR_Black);

	load_drv(ADX_MASTER_2304);
	
	/*
	To convert a sound to 16-bit
	ffmpeg -i %this%.wav -f s16be -ac 1 -ar (bitrate) %this%.PCM
	To convert a sound to 8-bit
	ffmpeg -i %this%.wav -f s8 -ac 1 -ar (bitrate) %this%.PCM
	*/
	 pcm16snd = load_16bit_pcm((Sint8 *)"DEF_FLAG.PCM", 15360);
	 pcm8snd = load_8bit_pcm((Sint8 *)"HAV_FLAG.PCM", 15360);
	 adx4snd = load_adx((Sint8 *)"NBGM.ADX");
	 
	
	jo_core_add_vblank_callback(sdrv_vblank_rq);
	jo_core_add_callback(my_draw);
	jo_core_run();
}

/*
** END OF FILE
*/

