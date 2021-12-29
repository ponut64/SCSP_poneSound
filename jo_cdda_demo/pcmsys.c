//pcm_sys.c
//this file is compiled separately
//hopefully somewhat portable
//
#include <jo/jo.h> //Mostly to link us with SBL file system
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
		
	sysComPara * m68k_com = (sysComPara *)(SNDPRG + DRV_SYS_END);
	unsigned int * scsp_load =  (unsigned int*)(0x408 + DRV_SYS_END + 0x20); //Local loading address for sound data, is DRV_SYS_END ahead of the SNDPRG, and ahead of the communication data
	unsigned short * master_volume = (unsigned short *)(SNDRAM + 0x100400);
	short numberPCMs = 0;
	
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
	
/**stolen from xl2**/
#define     OPEN_MAX    (Sint32)5
#define     DIR_MAX     (Sint32)1024
#define     RD_UNIT     (10)
#define     SECT_SIZE   (2048)
GfsDirTbl gfsDirTbl;
GfsDirName gfsDirName[DIR_MAX];
Uint32 gfsLibWork[GFS_WORK_SIZE(OPEN_MAX)/sizeof(Uint32)];
Sint32 gfsDirN;
void    cd_init(void)
{
    GFS_DIRTBL_TYPE(&gfsDirTbl) = GFS_DIR_NAME;
    GFS_DIRTBL_DIRNAME(&gfsDirTbl) = gfsDirName;
    GFS_DIRTBL_NDIR(&gfsDirTbl) = DIR_MAX;
    gfsDirN = GFS_Init(OPEN_MAX, gfsLibWork, &gfsDirTbl);
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

void	load_driver_binary(Sint8 * filename, void * buffer, int master_adx_frequency)
{
	cd_init();
	GfsHn s_gfs;
	Sint32 file_size;
	
	Sint32 local_name = GFS_NameToId(filename);

	//Open GFS
	s_gfs = GFS_Open((Sint32)local_name);
	//Get file information (mostly, the file size)
	GFS_GetFileInfo(s_gfs, NULL, NULL, &file_size, NULL);
	
	GFS_Close(s_gfs);
	
	GFS_Load(local_name, 0, (Uint32 *)buffer, file_size);
	
	//The immediacy of these commands is important.
	//As per SEGA technical bulletin 51, the Sound CPU is not to be turned off for more than 0.5 seconds.
	// Turn off Sound CPU
	smpc_issue_command(SMPC_CMD_SNDOFF);
	smpc_wait_till_ready();
	//Set max master volume + 4mbit memory 
	*master_volume = 0x20F; 
	//Copy the driver binary (code) over to sound RAM. The binary includes the vector table information.
	slDMACopy(buffer, (void*)SNDRAM, file_size);
	slDMAWait();
	//Set the ADX coefficients for the driver to use, if one was selected.
	if(master_adx_frequency == ADX_MASTER_768)
	{
		m68k_com->drv_adx_coef_1 = ADX_768_COEF_1;
		m68k_com->drv_adx_coef_2 = ADX_768_COEF_2;
	} else if(master_adx_frequency == ADX_MASTER_1152){
		m68k_com->drv_adx_coef_1 = ADX_1152_COEF_1;
		m68k_com->drv_adx_coef_2 = ADX_1152_COEF_2;
	} else if(master_adx_frequency == ADX_MASTER_1536){
		m68k_com->drv_adx_coef_1 = ADX_1536_COEF_1;
		m68k_com->drv_adx_coef_2 = ADX_1536_COEF_2;
	} else if(master_adx_frequency == ADX_MASTER_2304){
		m68k_com->drv_adx_coef_1 = ADX_2304_COEF_1;
		m68k_com->drv_adx_coef_2 = ADX_2304_COEF_2;
	} else {
		m68k_com->drv_adx_coef_1 = 1;
		m68k_com->drv_adx_coef_2 = 1;
	}
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
	load_driver_binary((Sint8*)"SDRV.BIN", binary_buffer, master_adx_frequency);
	m68k_com->start = 0xFFFF;
}

short			calculate_bytes_per_blank(int sampleRate, bool is8Bit, bool isPAL)
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

short			load_16bit_pcm(Sint8 * filename, int sampleRate)
{
	if( (int)scsp_load > 0x7F800) return -1; //Illegal PCM data address, exit

	GfsHn s_gfs;
	Sint32 file_size;
	
	Sint32 local_name = GFS_NameToId(filename);

	//Open GFS
	s_gfs = GFS_Open((Sint32)local_name);
	//Get file information (mostly, the file size)
	GFS_GetFileInfo(s_gfs, NULL, NULL, &file_size, NULL);
	
	GFS_Close(s_gfs);
	
	if(file_size > (128 * 1024)) return -1; //PCM size too large for general-purpose playback [could still work with timed execution & offets]
	
	file_size += ((unsigned int)file_size & 1) ? 1 : 0;
	file_size += ((unsigned int)file_size & 3) ? 2 : 0;
	
	GFS_Load(local_name, 0, (Uint32 *)((unsigned int)scsp_load + SNDRAM), file_size);
 
	m68k_com->pcmCtrl[numberPCMs].hiAddrBits = (unsigned short)( (unsigned int)scsp_load >> 16);
	m68k_com->pcmCtrl[numberPCMs].loAddrBits = (unsigned short)( (unsigned int)scsp_load & 0xFFFF);
	
	m68k_com->pcmCtrl[numberPCMs].pitchword = convert_bitrate_to_pitchword(sampleRate);
	m68k_com->pcmCtrl[numberPCMs].playsize = (file_size>>1);
	m68k_com->pcmCtrl[numberPCMs].bytes_per_blank = calculate_bytes_per_blank(sampleRate, false, PCM_SYS_REGION); //Iniitalize as max volume
	m68k_com->pcmCtrl[numberPCMs].bitDepth = PCM_TYPE_16BIT; //Select 16-bit
	m68k_com->pcmCtrl[numberPCMs].loopType = 0; //Initialize as non-looping
	m68k_com->pcmCtrl[numberPCMs].volume = 7; //Initialize as max volume


	numberPCMs++; //Increment pcm #
	scsp_load = (unsigned int *)((unsigned int )scsp_load + file_size);
	return (numberPCMs-1); //Return the PCM # this sound recieved
}

short			load_8bit_pcm(Sint8 * filename, int sampleRate)
{
	if( (int)scsp_load > 0x7F800) return -1; //Illegal PCM data address, exit

	GfsHn s_gfs;
	Sint32 file_size;

	Sint32 local_name = GFS_NameToId(filename);

	//Open GFS
	s_gfs = GFS_Open((Sint32)local_name);
	//Get file information (mostly, the file size)
	GFS_GetFileInfo(s_gfs, NULL, NULL, &file_size, NULL);
	
	GFS_Close(s_gfs);
	
	
	if(file_size > (64 * 1024)) return -1; //PCM size too large for general-purpose playback [could still work with timed execution & offets]
	

	file_size += ((unsigned int)file_size & 1) ? 1 : 0;
	file_size += ((unsigned int)file_size & 3) ? 2 : 0;
	
	GFS_Load(local_name, 0, (Uint32 *)((unsigned int)scsp_load + SNDRAM), file_size);
 
	m68k_com->pcmCtrl[numberPCMs].hiAddrBits = (unsigned short)( (unsigned int)scsp_load >> 16);
	m68k_com->pcmCtrl[numberPCMs].loAddrBits = (unsigned short)( (unsigned int)scsp_load & 0xFFFF);
	
	m68k_com->pcmCtrl[numberPCMs].pitchword = convert_bitrate_to_pitchword(sampleRate);
	m68k_com->pcmCtrl[numberPCMs].playsize = (file_size);
	m68k_com->pcmCtrl[numberPCMs].bytes_per_blank = calculate_bytes_per_blank(sampleRate, true, PCM_SYS_REGION); //Iniitalize as max volume
	m68k_com->pcmCtrl[numberPCMs].bitDepth = PCM_TYPE_8BIT; //Select 8-bit
	m68k_com->pcmCtrl[numberPCMs].loopType = 0; //Initialize as non-looping
	m68k_com->pcmCtrl[numberPCMs].volume = 7; //Iniitalize as max volume


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

short		load_adx(Sint8 * filename)
{
	static adx_header adx;
	
	if( (int)scsp_load > 0x7F800) return -1; //Illegal PCM data address, exit

	Sint32 local_name = GFS_NameToId(filename);

//////////////////////////
// Step 1: Load the size of the header from the file to the header's location
//////////////////////////
	GFS_Load(local_name, 0, (Uint32 *)&adx, sizeof(adx_header));
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
	if(bpb != 768 && bpb != 512 && bpb != 384 && bpb != 256)
	{
		jo_printf(0, 1, "!(ADX INVALID BYTE-RATE)!");
		return -2;
	}
	m68k_com->pcmCtrl[numberPCMs].bytes_per_blank = bpb;
	m68k_com->pcmCtrl[numberPCMs].decompression_size = lcm(bpb, bpb + 64)<<1;
	m68k_com->pcmCtrl[numberPCMs].bitDepth = PCM_TYPE_ADX; //Select ADX type
	m68k_com->pcmCtrl[numberPCMs].loopType = PCM_SEMI; //Initialize as semi-protected.
	m68k_com->pcmCtrl[numberPCMs].volume = 7; //Iniitalize as max volume
	numberPCMs++;
/////////////////////////
// Step 4: Load the compressed ADX data to sound RAM. Unfortunately, we must include the 20 byte header.
// We want to load from an offset location from CD and then load (sample_ct / 32) * 18 bytes.
// We divide the sample count by 32 to retrieve the ADX frame count. We multiply by 18, as that is the size of an ADX 'frame'.
/////////////////////////
	unsigned int number_of_bytes_to_load = (adx.sample_ct / 32) * 18;
	number_of_bytes_to_load += ((unsigned int)number_of_bytes_to_load & 1) ? 1 : 0;
	number_of_bytes_to_load += ((unsigned int)number_of_bytes_to_load & 3) ? 2 : 0;
	GFS_Load(local_name, 0, (Uint32 *)((unsigned int)scsp_load + SNDRAM), number_of_bytes_to_load);
	scsp_load = (unsigned int *)((unsigned int )scsp_load + number_of_bytes_to_load);
	return (numberPCMs-1); //Return the PCM # this sound recieved
}

void		sdrv_vblank_rq(void)
{
	//jo_printf(0, 0, "drv_stat(%i)", m68k_com->start);
	m68k_com->start = 1;	
}

////////////////////////////////////////////////////////////////////////////////
// Redbook Support
// These are mostly CDC commands.
// credit to: ndiddy, ReyeMe, CyberWarriorX [iapetus]
////////////////////////////////////////////////////////////////////////////////

void CDDASetVolume(int vol)
{
	m68k_com->cdda_volume = (vol & 0x7);	
}

void CDDAPlay(int fromTrack, int toTrack, bool loop)
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

void CDDAPlaySingle(int track, bool loop)
{
    CDDAPlay(track, track, loop);
}

void CDDAStop(void)
{
    CdcPos poswk;
    CDC_POS_PTYPE(&poswk) = CDC_PTYPE_DFL;
    CDC_CdSeek(&poswk);
}

