//pcm_stm.h
//part of pcm_stm.c

#ifndef __PCM_STM_H__
# define __PCM_STM_H__

#include <jo/jo.h>
#include "pcmsys.h"

//This is sound RAM, addressable by the MC68EC000 / SCSP
#define BUFFER_SIZE (32768)
#define PCMBUF0 (PCMEND - BUFFER_SIZE)
#define PCMBUF1 (PCMBUF0 - BUFFER_SIZE)
#define PCMBUF2 (PCMBUF1 - BUFFER_SIZE)
#define PCMBUF3 (PCMBUF2 - BUFFER_SIZE)

//# of buffers (system will adjust to count, but you have to adjust the buffer play-write order)
#define MUS_BUFCNT (4)

//Pre-calculated pitchwords (by way of pwordprog.c in any online compiler)
#define S3072KHZ	(31122)
#define S1536KHZ	(29074)
//

typedef struct{
	void* rd_pcmbuf;
	int play_pcmbuf;
} snd_ring;

extern snd_ring		music_buf[MUS_BUFCNT];
extern Sint8*		music;

void	music_vblIn(void);
void	init_music(char bitrate_select, Sint8 * music_file_name, unsigned char volume);
void	master_file_system(void(*game_code)(void));

#endif

