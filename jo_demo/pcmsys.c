//pcm_sys.c
//this file is compiled separately
//hopefully somewhat portable
//
#include <jo/jo.h>
#include "pcmsys.h"

static const int logtbl[] = {
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
		
	sysComPara * m68k_com = (sysComPara *)((SNDPRG + DRV_SYS_END) | 0x20000000);
	static unsigned int * scsp_loading_start = (unsigned int*)(0x408 + DRV_SYS_END + 0x20); //Local loading address for sound data, is DRV_SYS_END ahead of the SNDPRG, and ahead of the communication data
	unsigned int * scsp_load;
	unsigned short * master_volume = (unsigned short *)(SNDRAM + 0x100400);
	unsigned short driver_master_volume = 0;
	short numberPCMs = 0;
	
static short adx_coef_tbl[8][2] = 
{
	{ADX_768_COEF_1,   ADX_768_COEF_2},
	{ADX_1152_COEF_1, ADX_1152_COEF_2},
	{ADX_1536_COEF_1, ADX_1536_COEF_2},
	{ADX_2304_COEF_1, ADX_2304_COEF_2},
	{ADX_640_COEF_1,   ADX_640_COEF_2},
	{ADX_960_COEF_1,   ADX_960_COEF_2},
	{ADX_1280_COEF_1, ADX_1280_COEF_2},
	{ADX_1920_COEF_1, ADX_1920_COEF_2}
};

//MVOL is a 4-bit number; values 0-15 are valid.
//If the value is higher than 15, this will just cap it at 15.
void	set_master_volume(unsigned short volume)
{
	volume = (volume >= 0xF) ? 0xF : volume;
	*master_volume = 0x200 | (volume & 0xF);
	driver_master_volume = volume;
}
	
void	pcm_play(short pcmNumber, char ctrlType, char volume)
{
	if(pcmNumber < 0) return;
	m68k_com->pcmCtrl[pcmNumber].sh2_permit = 1;
	m68k_com->pcmCtrl[pcmNumber].volume = volume;
	m68k_com->pcmCtrl[pcmNumber].loopType = ctrlType;
}

void	pcm_parameter_change(short pcmNumber, char volume, char pan)
{
	if(pcmNumber < 0) return;
	m68k_com->pcmCtrl[pcmNumber].volume = volume;
	m68k_com->pcmCtrl[pcmNumber].pan = pan;
}

void	pcm_cease(short pcmNumber)
{
	if(pcmNumber < 0) return;
	if(m68k_com->pcmCtrl[pcmNumber].loopType <= 0) //If it is a volatile or protected sound, the expected control method is to mute the sound and let it end itself.
	{												//Protected sounds have a permission state of "until they end".
	m68k_com->pcmCtrl[pcmNumber].volume = 0;
	} else {
	m68k_com->pcmCtrl[pcmNumber].sh2_permit = 0; //If it is a looping sound, the control method is to command it to stop.
	}
}

//
// Usage:
// Intended as the "level reset" function.
// Does not soft or hard reset driver. To do that, re-load the driver binary (run load_drv again).
// This instead resets the loading pointer and number of PCMs to a specific PCM number.
// In use with proper sequence of asset loading, a certain number of sound assets can be retained in sound memory, with others discarded.
// 
// The argument "highest_pcm_number_to_keep" is the latest sequentially loaded PCM in sound RAM that signals the point at which:
// Any PCM number loaded earlier than this will be kept in memory and its number still valid to play the sound.
// Any PCM number loaded later than this will be ignored in memory when loading new sounds, but the number is still valid to play sound.
// Pass -1 to this function to clear all PCMs.
void	pcm_reset(short highest_pcm_number_to_keep)
{
	//For clearing all sounds, input is negative
	if(highest_pcm_number_to_keep < 0) {
		scsp_load = scsp_loading_start;
		numberPCMs = 0;
		return;
	}
	
	numberPCMs = highest_pcm_number_to_keep+1;
	scsp_load = (unsigned int *)((unsigned int)(m68k_com->pcmCtrl[highest_pcm_number_to_keep].hiAddrBits<<16) | (int)(m68k_com->pcmCtrl[highest_pcm_number_to_keep].loAddrBits));
	if(m68k_com->pcmCtrl[highest_pcm_number_to_keep].bitDepth == 2) 
	{ //If this is an ADX sound, offset the loading pointer by # of frames by 18. Address includes 18-byte header offset.
		scsp_load = (unsigned int *)((unsigned int)scsp_load + (m68k_com->pcmCtrl[highest_pcm_number_to_keep].playsize * 18)); 
	} else if(m68k_com->pcmCtrl[highest_pcm_number_to_keep].bitDepth == 1)
	{ //If this is an 8-bit PCM, offset the loading pointer by the playsize, exactly (one byte samples).
		scsp_load = (unsigned int *)((unsigned int)scsp_load + m68k_com->pcmCtrl[highest_pcm_number_to_keep].playsize);
	} else if(m68k_com->pcmCtrl[highest_pcm_number_to_keep].bitDepth == 0)
	{ //If this is a 16-bit PCM, offset the loading pointer by the playsize, shifted left once (two byte samples).
		scsp_load = (unsigned int *)((unsigned int)scsp_load + (m68k_com->pcmCtrl[highest_pcm_number_to_keep].playsize<<1));
	}
}
	

void smpc_wait_till_ready (void)
{
   // Wait until SF register is cleared
   while(SMPC_REG_SF & 0x1) { }
}

//////////////////////////////////////////////////////////////////////////////

void smpc_issue_command(unsigned char cmd)
{
   // Set SF register so that no other command can be issued.
   SMPC_REG_SF = 1;

   // Writing COMREG starts execution
   SMPC_REG_COMREG = cmd;
}

//////////////////////////////////////////////////////////////////////////////

void	load_driver_binary(char * filename, void * buffer, int master_adx_frequency)
{
    jo_file file;
	int file_size;
	//Open file
	jo_fs_open(&file, filename);
    // Note: file.size gives the size of the file
    //       file.read gives the total of bytes read.
	file_size = file.size;
    jo_fs_read_next_bytes(&file, (char*)buffer, file_size);

    jo_fs_close(&file);
	
	//The immediacy of these commands is important.
	//As per SEGA technical bulletin 51, the Sound CPU is not to be turned off for more than 0.5 seconds.
	// Turn off Sound CPU
	smpc_issue_command(SMPC_CMD_SNDOFF);
	smpc_wait_till_ready();
	//Set max master volume + 4mbit memory 
	set_master_volume(0xF);
	//Copy the driver binary (code) over to sound RAM. The binary includes the vector table information.
	jo_dma_copy(buffer, (void*)SNDRAM, file_size);
	// unsigned char * source = (unsigned char *)buffer;
	// for (int i = 0; i < file_size; i++){
		// *(unsigned char *)(SNDRAM + i) = source[i];
	// }
	//Set the ADX coefficients for the driver to use, if one was selected.

	m68k_com->drv_adx_coef_1 = adx_coef_tbl[master_adx_frequency][0];
	m68k_com->drv_adx_coef_2 = adx_coef_tbl[master_adx_frequency][1];

	// Turn on Sound CPU again
	smpc_wait_till_ready();
	smpc_issue_command(SMPC_CMD_SNDON);
	//
}
	
void			load_drv(int master_adx_frequency)
{
	// Make sure SCSP is set to 512k mode
	*(unsigned char *)(0x25B00400) = 0x02;

	// Clear Sound Ram
	for (int i = 0; i < 0x80000; i+=4){
		*(unsigned int *)(SNDRAM + i) = 0x00000000;
	}
	// Volatile loading buffer
	// This memory is not permanently used, its just a place to temporarily store the driver binary
	void * binary_buffer = (void*)2097152;
	
	// Copy driver over
	load_driver_binary("SDRV.BIN", binary_buffer, master_adx_frequency);
	m68k_com->start = 0xFFFF;
	volatile int i = 0;
	scsp_load = scsp_loading_start; // Re-set loading pointer.
	for(i = 0; i < (int)scsp_load; i++)
	{
		//This is to pop the stack here. Because GCC.
	}
	//Additionally, reset the number of PCMs.
	numberPCMs = 0;
}

short			calculate_bytes_per_blank(int sampleRate, char is8Bit, char isPAL)
{
	int frameCount = (isPAL == true) ? 50 : 60;
	int sampleSize = (is8Bit == true) ? 8 : 16;
	return ((sampleRate * sampleSize)>>3)/frameCount;
	
}

short			convert_bitrate_to_pitchword(short sampleRate)
{
	
	int octr;
	int shiftr;
	int fnsr;
	
	octr = PCM_CALC_OCT(sampleRate);
	shiftr = PCM_CALC_SHIFT_FREQ(octr);
	fnsr = PCM_CALC_FNS(sampleRate, shiftr);
	
	return PCM_SET_PITCH_WORD(octr, fnsr);
}

//2048 sound async loading buffer. size of 1 ISO-9660 sector.
unsigned char * snd_async_buf[64 * 1024];

void            cpy_buf(void)
{
	jo_dma_copy((void*)snd_async_buf, (void*)scsp_load, 2048);
	scsp_load = (unsigned int *)((unsigned int )scsp_load + 2048);
}


short			load_16bit_pcm(char * filename, int sampleRate)
{
	if( (int)scsp_load > 0x7F800) return -1; //Illegal PCM data address, exit
	if( numberPCMs >= PCM_CTRL_MAX) return -1; //Maximum number of PCMs reached, exit

    jo_file file;
	//Open file
	
	jo_fs_open(&file, filename);
	int file_size = file.size;
    // Note: file.size gives the size of the file
    //       file.read gives the total of bytes read.
    
	if(file.size > (128 * 1024)) return -1; //PCM size too large for general-purpose playback [could still work with timed execution & offets]
	
	file_size += ((unsigned int)file.size & 1) ? 1 : 0;
	file_size += ((unsigned int)file.size & 3) ? 2 : 0;
	
	m68k_com->pcmCtrl[numberPCMs].hiAddrBits = (unsigned short)( (unsigned int)scsp_load >> 16);
	m68k_com->pcmCtrl[numberPCMs].loAddrBits = (unsigned short)( (unsigned int)scsp_load & 0xFFFF);
	
	m68k_com->pcmCtrl[numberPCMs].pitchword = convert_bitrate_to_pitchword(sampleRate);
	m68k_com->pcmCtrl[numberPCMs].playsize = (file_size>>1);
	m68k_com->pcmCtrl[numberPCMs].bytes_per_blank = calculate_bytes_per_blank(sampleRate, false, PCM_SYS_REGION); //Iniitalize as max volume
	m68k_com->pcmCtrl[numberPCMs].bitDepth = PCM_TYPE_16BIT; //Select 16-bit
	m68k_com->pcmCtrl[numberPCMs].loopType = 0; //Initialize as non-looping
	m68k_com->pcmCtrl[numberPCMs].volume = 0; //Initialize as max volume
	
    jo_fs_read_next_bytes(&file, (char*)((unsigned int)scsp_load + SNDRAM), file_size);

    jo_fs_close(&file);

	numberPCMs++; //Increment pcm #
	scsp_load = (unsigned int *)((unsigned int )scsp_load + file_size);
	return (numberPCMs-1); //Return the PCM # this sound received
}

short			load_8bit_pcm(char * filename, int sampleRate)
{
	if( (int)scsp_load > 0x7F800) return -1; //Illegal PCM data address, exit
	if( numberPCMs >= PCM_CTRL_MAX) return -1; //Maximum number of PCMs reached, exit
	
    jo_file file;
	int file_size;
	//Open file
	jo_fs_open(&file, filename);
    // Note: file.size gives the size of the file
    //       file.read gives the total of bytes read.
	file_size = file.size;

	if(file_size > (64 * 1024)) return -1; //PCM size too large for general-purpose playback [could still work with timed execution & offets]

	file_size += ((unsigned int)file_size & 1) ? 1 : 0;
	file_size += ((unsigned int)file_size & 3) ? 2 : 0;
	
	
 
	m68k_com->pcmCtrl[numberPCMs].hiAddrBits = (unsigned short)( (unsigned int)scsp_load >> 16);
	m68k_com->pcmCtrl[numberPCMs].loAddrBits = (unsigned short)( (unsigned int)scsp_load & 0xFFFF);
	
	m68k_com->pcmCtrl[numberPCMs].pitchword = convert_bitrate_to_pitchword(sampleRate);
	m68k_com->pcmCtrl[numberPCMs].playsize = (file_size);
	m68k_com->pcmCtrl[numberPCMs].bytes_per_blank = calculate_bytes_per_blank(sampleRate, true, PCM_SYS_REGION); //Iniitalize as max volume
	m68k_com->pcmCtrl[numberPCMs].bitDepth = PCM_TYPE_8BIT; //Select 8-bit
	m68k_com->pcmCtrl[numberPCMs].loopType = 0; //Initialize as non-looping
	m68k_com->pcmCtrl[numberPCMs].volume = 0; //Iniitalize as max volume
	
    jo_fs_read_next_bytes(&file, (char*)((unsigned int)scsp_load + SNDRAM), file_size);

    jo_fs_close(&file);

	numberPCMs++; //Increment pcm #
	scsp_load = (unsigned int *)((unsigned int )scsp_load + file_size);
	return (numberPCMs-1); //Return the PCM # this sound received
}

// Recursive function to return gcd of a and b 
short gcd(short a, short b) 
{ 
    if (a == 0)
        return b; 
    return gcd(b % a, a); 
} 
 
// Function to return LCM of two numbers 
// Used specifically to find the buffer size for ADX sound effects
short lcm(short a, short b) 
{ 
    return (a / gcd(a, b)) * b;
} 

short		load_adx(char * filename)
{
	static adx_header adx;
	
	if( (int)scsp_load > 0x7F800) return -1; //Illegal PCM data address, exit
	if( numberPCMs >= PCM_CTRL_MAX) return -1; //Maximum number of PCMs reached, exit

    jo_file file;
	//Open file
	jo_fs_open(&file, filename);


//////////////////////////
// Step 1: Load the size of the header from the file to the header's location
//////////////////////////
	jo_fs_read_next_bytes(&file, (char*)&adx, sizeof(adx_header));
//////////////////////////
// Step 2: Check the data we just loaded and make sure it's an ADX file.
// If the data does not match what the decompression routine expects, this function will return -1.
//////////////////////////
	// jo_printf(13, 9, "ohalf(%i)", adx.one_half);
	// jo_printf(13, 10, "blocksz(%i)", adx.block_size);
	// jo_printf(13, 11, "bitdepth(%i)", adx.bit_depth);
	// jo_printf(13, 12, "srate(%i)", adx.sample_rate);
	if(adx.one_half != 32768 || adx.block_size != 18 || adx.bit_depth != 4) return -1; 
//////////////////////////
// Step 3: Parse the data in the header to the sound driver PCM control struct.
// Special things for ADX is the playsize is actually the # of ADX frames, not the number of samples.
// We expect a block size of 16, so each frame has 16 bytes of sample data which is 32 samples.
//////////////////////////
	// Because we ""dumbly"" load the header to sound RAM, let's give the used pointer the offset.
	unsigned int working_address = (unsigned int)(scsp_load) + adx.offset2data + 4;
	m68k_com->pcmCtrl[numberPCMs].hiAddrBits = (unsigned short)( (unsigned int)working_address >> 16);
	m68k_com->pcmCtrl[numberPCMs].loAddrBits = (unsigned short)( (unsigned int)working_address & 0xFFFF);
	m68k_com->pcmCtrl[numberPCMs].pitchword = convert_bitrate_to_pitchword(adx.sample_rate);
	m68k_com->pcmCtrl[numberPCMs].playsize = (adx.sample_ct / 32);
	short bpb = calculate_bytes_per_blank((int)adx.sample_rate, false, PCM_SYS_REGION); //Iniitalize as max volume
	if(bpb != 768 && bpb != 512 && bpb != 384 && bpb != 256 && bpb != 192 && bpb != 128)
	{
		jo_printf(0, 1,"!(ADX INVALID BYTE-RATE)!");
		return -2;
	}
	m68k_com->pcmCtrl[numberPCMs].bytes_per_blank = bpb;
	unsigned short big_dct_sz = (bpb >= 256) ? lcm(bpb, bpb + 64)<<1 : 5376; // Dirty fix for ultra low bitrate
	m68k_com->pcmCtrl[numberPCMs].decompression_size = (big_dct_sz > (adx.sample_ct<<1)) ? adx.sample_ct<<1 : big_dct_sz;
	m68k_com->pcmCtrl[numberPCMs].bitDepth = PCM_TYPE_ADX; //Select ADX type
	m68k_com->pcmCtrl[numberPCMs].loopType = PCM_SEMI; //Initialize as semi-protected.
	m68k_com->pcmCtrl[numberPCMs].volume = 0; //Iniitalize as max volume
	numberPCMs++;
/////////////////////////
// Step 4: Load the compressed ADX data to sound RAM. Unfortunately, we must include the 20 byte header.
// We want to load from an offset location from CD and then load (sample_ct / 32) * 18 bytes.
// We divide the sample count by 32 to retrieve the ADX frame count. We multiply by 18, as that is the size of an ADX 'frame'.
/////////////////////////
	unsigned int number_of_bytes_to_load = (adx.sample_ct / 32) * 18;
	number_of_bytes_to_load += ((unsigned int)number_of_bytes_to_load & 1) ? 1 : 0;
	number_of_bytes_to_load += ((unsigned int)number_of_bytes_to_load & 3) ? 2 : 0;
	jo_fs_close(&file);
	jo_fs_open(&file, filename);
	jo_fs_read_next_bytes(&file, (char*)((unsigned int)scsp_load + SNDRAM), number_of_bytes_to_load);
	scsp_load = (unsigned int *)((unsigned int )scsp_load + number_of_bytes_to_load);
	jo_fs_close(&file);
	return (numberPCMs-1); //Return the PCM # this sound recieved
}

void		sdrv_vblank_rq(void)
{
	jo_printf(0, 0, "drv_stat(%i)", m68k_com->start);
	m68k_com->start = 1;	
}

////////////////////////////////////////////////////////////////////////////////
// Redbook Support
// These are mostly CDC commands.
// credit to: ndiddy, ReyeMe, CyberWarriorX [iapetus]
////////////////////////////////////////////////////////////////////////////////

/* 
void CDDA_SetVolume(int vol)
{
	//Step 1: Remove the volume bits from the value (isolate the pan)
	unsigned char newvol = m68k_com->cdda_left_channel_vol_pan & 0x1F;
	//Step 2: Apply the volume to the correct bits
	newvol |= ((vol & 0x7)<<5);
	//Step 3: Apply value back to left channel
	m68k_com->cdda_left_channel_vol_pan = newvol;
	//Step 4: Repeat for right channel
	newvol = m68k_com->cdda_right_channel_vol_pan & 0x1F;
	//Step 5: Apply the volume to the correct bits
	newvol |= ((vol & 0x7)<<5);
	//Step 6: Apply value back to right channel
	m68k_com->cdda_right_channel_vol_pan = newvol;
}

//	To see what this does and how to use it, refer to the SCSP manual.
//	Warning: Use without reading the manual may break your CD audio.
void CDDA_SetChannelVolPan(unsigned char left_channel, unsigned char right_channel)
{
	m68k_com->cdda_left_channel_vol_pan = left_channel;
	m68k_com->cdda_right_channel_vol_pan = right_channel;
}

void CDDA_Play(int fromTrack, int toTrack, char loop)
{
    CdcPly ply;
    CDC_PLY_STYPE(&ply) = CDC_PTYPE_TNO; // track number
    CDC_PLY_STNO(&ply) = fromTrack;
    CDC_PLY_SIDX(&ply) = 1;
    CDC_PLY_ETYPE(&ply) = CDC_PTYPE_TNO;
    CDC_PLY_ETNO(&ply) = toTrack;
    CDC_PLY_EIDX(&ply) = 1;

    if (loop)
    {
        CDC_PLY_PMODE(&ply) = CDC_PM_DFL | 0xf; // 0xf = infinite repetitions
    }
    else
    {
        CDC_PLY_PMODE(&ply) = CDC_PM_DFL;
    }

    CDC_CdPlay(&ply);
}

void CDDA_PlaySingle(int track, char loop)
{
    CDDA_Play(track, track, loop);
}

void CDDA_Stop(void)
{
    CdcPos poswk;
    CDC_POS_PTYPE(&poswk) = CDC_PTYPE_DFL;
    CDC_CdSeek(&poswk);
}
 */
