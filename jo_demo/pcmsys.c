//pcm_sys.c
//this file is compiled separately
//hopefully somewhat portable
//
#include <jo/jo.h> //Mostly to link us with SBL file system
#include "pcmsys.h"


const static int logtbl[] = {
/* 0 */		0, 
/* 1 */		1, 
/* 2 */		2, 2, 
/* 4 */		3, 3, 3, 3, 
/* 8 */		4, 4, 4, 4, 4, 4, 4, 4, 
/* 16 */	5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
/* 32 */	6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 
			6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 
/* 64 */	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
			7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
			7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
			7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
/* 128 */	8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 
			8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 
			8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 
			8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 
			8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 
			8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 
			8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 
			8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
	};
	
#define PCM_MSK1(a)				((a)&0x0001)
#define PCM_MSK3(a)				((a)&0x0007)
#define PCM_MSK4(a)				((a)&0x000F)
#define PCM_MSK5(a)				((a)&0x001F)
#define PCM_MSK10(a)			((a)&0x03FF)

#define PCM_SCSP_FREQUENCY					(44100L)

#define PCM_CALC_OCT(smpling_rate) 											\
		((int)logtbl[PCM_SCSP_FREQUENCY / ((smpling_rate) + 1)])
		
#define PCM_CALC_SHIFT_FREQ(oct)											\
		(PCM_SCSP_FREQUENCY >> (oct))
		
#define PCM_CALC_FNS(smpling_rate, shift_freq)								\
		((((smpling_rate) - (shift_freq)) << 10) / (shift_freq))
		
#define PCM_SET_PITCH_WORD(oct, fns)										\
		((int)((PCM_MSK4(-(oct)) << 11) | PCM_MSK10(fns)))
		
		#define DRV_SYS_END (10 * 1024) //System defined safe end of driver's address space

	sysComPara * m68k_com = (sysComPara *)(SNDPRG + DRV_SYS_END);
	unsigned int * scsp_load =  (unsigned int*)(0x408 + DRV_SYS_END + 0x20); //Local loading address for sound data, is DRV_SYS_END ahead of the SNDPRG, and ahead of the communication data
	unsigned short * master_volume = (unsigned short *)(SNDRAM + 0x100400);
	short numberPCMs = 0;

//////////////////////////////////////////////////////////////////////////////

inline void smpc_wait_till_ready (void)
{
   // Wait until SF register is cleared
   while(SMPC_REG_SF & 0x1) { }
}

//////////////////////////////////////////////////////////////////////////////

inline void smpc_issue_command(unsigned char cmd)
{
   // Set SF register so that no other command can be issued.
   SMPC_REG_SF = 1;

   // Writing COMREG starts execution
   SMPC_REG_COMREG = cmd;
}

//////////////////////////////////////////////////////////////////////////////

void	load_driver_binary(Sint8 * filename, void * buffer)
{

	GfsHn s_gfs;
	Sint32 sector_count;
	Sint32 file_size;
	
	Sint32 local_name = GFS_NameToId(filename);

//Open GFS
	s_gfs = GFS_Open((Sint32)local_name);
//Get sectors
	GFS_GetFileSize(s_gfs, NULL, &sector_count, NULL);
	GFS_GetFileInfo(s_gfs, NULL, NULL, &file_size, NULL);
	
	GFS_Close(s_gfs);
	
	GFS_Load(local_name, 0, (Uint32 *)buffer, file_size);
	
	//The immediacy of these commands is important.
	//As per SEGA technical bulletin 51, the Sound CPU is not to be turned off for more than 0.5 seconds.
	// Turn off Sound CPU
	smpc_issue_command(SMPC_CMD_SNDOFF);
	smpc_wait_till_ready();
	//
	*master_volume = 0x20F; //Set max master volume + 4mbit memory // Very important, douglath
	slDMACopy(buffer, (void*)SNDRAM, file_size);
	slDMAWait();
	// Turn on Sound CPU again
	smpc_wait_till_ready();
	smpc_issue_command(SMPC_CMD_SNDON);
	//
}
	
void			load_drv(void)
{
	// Make sure SCSP is set to 512k mode
	*(unsigned char *)(0x25B00400) = 0x02;

	// Clear Sound Ram
	for (int i = 0; i < 0x80000; i+=4){
		*(unsigned int *)(SNDRAM + i) = 0x00000000;
	}
	void * binary_buffer = (void*)2097152;
	
	// Copy driver over
	load_driver_binary((Sint8*)"SDRV.BIN", binary_buffer);

}

short			calculate_bytes_per_blank(int sampleRate, bool is8Bit, bool isPAL)
{
	int frameCount = (isPAL == true) ? 50 : 60;
	int sampleSize = (is8Bit == true) ? 8 : 16;
	return ((sampleRate * sampleSize)>>3)/frameCount;
	
}

short			load_16bit_pcm(Sint8 * filename, int sampleRate)
{
	if( (int)scsp_load > 0x7F800) return -1; //Illegal PCM data address, exit

	GfsHn s_gfs;
	Sint32 sector_count;
	Sint32 file_size;
	
	int octr;
	int shiftr;
	int fnsr;
	
	Sint32 local_name = GFS_NameToId(filename);

//Open GFS
	s_gfs = GFS_Open((Sint32)local_name);
//Get sectors
	GFS_GetFileSize(s_gfs, NULL, &sector_count, NULL);
	GFS_GetFileInfo(s_gfs, NULL, NULL, &file_size, NULL);
	
	GFS_Close(s_gfs);
	
	if(file_size > (128 * 1024)) return -1; //PCM size too large for general-purpose playback [could still work with timed execution & offets]
	
	file_size += ((unsigned int)file_size & 1) ? 1 : 0;
	file_size += ((unsigned int)file_size & 3) ? 2 : 0;
	
	GFS_Load(local_name, 0, (Uint32 *)((unsigned int)scsp_load + SNDRAM), file_size);
	
	octr = PCM_CALC_OCT(sampleRate);
	shiftr = PCM_CALC_SHIFT_FREQ(octr);
	fnsr = PCM_CALC_FNS(sampleRate, shiftr);
 
	m68k_com->pcmCtrl[numberPCMs].hiAddrBits = (unsigned short)( (unsigned int)scsp_load >> 16);
	m68k_com->pcmCtrl[numberPCMs].loAddrBits = (unsigned short)( (unsigned int)scsp_load & 0xFFFF);
	
	m68k_com->pcmCtrl[numberPCMs].pitchword = PCM_SET_PITCH_WORD(octr, fnsr);
	m68k_com->pcmCtrl[numberPCMs].playsize = (file_size>>1);
	m68k_com->pcmCtrl[numberPCMs].bytes_per_blank = calculate_bytes_per_blank(sampleRate, false, PCM_SYS_REGION); //Iniitalize as max volume
	m68k_com->pcmCtrl[numberPCMs].bitDepth = 0; //Select 16-bit
	m68k_com->pcmCtrl[numberPCMs].loopType = 0; //Initialize as non-looping
	m68k_com->pcmCtrl[numberPCMs].volume = 7; //Iniitalize as max volume


	numberPCMs++; //Increment pcm #
	scsp_load = (unsigned int *)((unsigned int )scsp_load + file_size);
	return (numberPCMs-1); //Return the PCM # this sound recieved
}

short			load_8bit_pcm(Sint8 * filename, int sampleRate)
{
	if( (int)scsp_load > 0x7F800) return -1; //Illegal PCM data address, exit

	GfsHn s_gfs;
	Sint32 sector_count;
	Sint32 file_size;
	
	int octr;
	int shiftr;
	int fnsr;
	
	Sint32 local_name = GFS_NameToId(filename);

//Open GFS
	s_gfs = GFS_Open((Sint32)local_name);
//Get sectors
	GFS_GetFileSize(s_gfs, NULL, &sector_count, NULL);
	GFS_GetFileInfo(s_gfs, NULL, NULL, &file_size, NULL);
	
	GFS_Close(s_gfs);
	
	
	if(file_size > (64 * 1024)) return -1; //PCM size too large for general-purpose playback [could still work with timed execution & offets]
	

	file_size += ((unsigned int)file_size & 1) ? 1 : 0;
	file_size += ((unsigned int)file_size & 3) ? 2 : 0;
	
	GFS_Load(local_name, 0, (Uint32 *)((unsigned int)scsp_load + SNDRAM), file_size);
	
	octr = PCM_CALC_OCT(sampleRate);
	shiftr = PCM_CALC_SHIFT_FREQ(octr);
	fnsr = PCM_CALC_FNS(sampleRate, shiftr);
 
	m68k_com->pcmCtrl[numberPCMs].hiAddrBits = (unsigned short)( (unsigned int)scsp_load >> 16);
	m68k_com->pcmCtrl[numberPCMs].loAddrBits = (unsigned short)( (unsigned int)scsp_load & 0xFFFF);
	
	m68k_com->pcmCtrl[numberPCMs].pitchword = PCM_SET_PITCH_WORD(octr, fnsr);
	m68k_com->pcmCtrl[numberPCMs].playsize = (file_size);
	m68k_com->pcmCtrl[numberPCMs].bytes_per_blank = calculate_bytes_per_blank(sampleRate, true, PCM_SYS_REGION); //Iniitalize as max volume
	m68k_com->pcmCtrl[numberPCMs].bitDepth = 1; //Select 8-bit
	m68k_com->pcmCtrl[numberPCMs].loopType = 0; //Initialize as non-looping
	m68k_com->pcmCtrl[numberPCMs].volume = 7; //Iniitalize as max volume


	numberPCMs++; //Increment pcm #
	scsp_load = (unsigned int *)((unsigned int )scsp_load + file_size);
	return (numberPCMs-1); //Return the PCM # this sound recieved
}

void	pcm_play(short pcmNumber, char ctrlType, char volume)
{
	m68k_com->pcmCtrl[pcmNumber].sh2_permit = 1;
	m68k_com->pcmCtrl[pcmNumber].volume = volume;
	m68k_com->pcmCtrl[pcmNumber].loopType = ctrlType;
}

void	pcm_parameter_change(short pcmNumber, char volume, char pan)
{
	m68k_com->pcmCtrl[pcmNumber].volume = volume;
	m68k_com->pcmCtrl[pcmNumber].pan = pan;
}

void	pcm_cease(short pcmNumber)
{

	if(m68k_com->pcmCtrl[pcmNumber].loopType <= 0) //If it is a volatile or protected sound, the expected control method is to mute the sound and let it end itself.
	{												//Protected sounds have a permission state of "until they end".
	m68k_com->pcmCtrl[pcmNumber].volume = 0;
	} else {
	m68k_com->pcmCtrl[pcmNumber].sh2_permit = 0; //If it is a looping sound, the control method is to command it to stop.
	}
}

