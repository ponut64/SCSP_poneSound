//Driver main.c
#define ADDR_PRG (0x408)
#define ADDR_MAX (0x7F000)
#define ADDR_STACK (0x80000 - 0x400)
#define ADDR_END (0x80000)
//Big credit to cWx :: cyberWarriorX for a sound driver prototype and most importatly, the linker script!
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int * vecTable[256] __attribute__ ((section ("VECTORS"))) =
{
(int*)ADDR_STACK, (int*)ADDR_PRG, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
(int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
uArch warning:
Some operations that handle 4-bytes (void, boolean, int, unsigned int, pointers) will not work as expected.
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void	lead_function(void) //Link start to main
{
	__asm__("jmp _start"); //note that _start is the ASM label that equates to the lead function in this compiler.
							//In a normal compiler, it would be "main".
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Place all includes past this line
#define PCM_CTRL_MAX	(64)
#define ADX_CTRL_MAX	(2)
#define DRV_SYS_END		(45 * 1024) //System defined safe end of driver's address space
//////////////////////////////////////////////////////////////////////////////
#define	PCM_ALT_LOOP	(3)
#define PCM_RVS_LOOP	(2)
#define PCM_FWD_LOOP	(1)
#define PCM_VOLATILE	(0)
#define PCM_PROTECTED	(-1)
#define PCM_SEMI		(-2)
//////////////////////////////////////////////////////////////////////////////
#define PCM_TYPE_ADX (2) // 4-bit (compressed audio)
#define PCM_TYPE_8BIT (1) // 8-bit
#define PCM_TYPE_16BIT (0) // 16-bit
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*		
		GLOASSARY OF TERMS:
			KX : EXECUTE KEY [select] [Start or stop the sound] [Reset to 0 by system]
			KB : Key ON or Key OFF select [0 is OFF, 1 is ON]
			SBCTL : Source bit control - Boolean for whether data is signed or unsigned
			SSCTL : Source type control [0: PCM, 1: Noise Generator, 2: Waveform generator, 3: Illegal] - Pertains to LFO registers in 1&2
			LPCTL : loop control [0: Sound ends when LEA is reached, 1: normal loop, 2: reverse loop, 3: alternating loop]
					It is important to note that looping commands still need continuous KEY_ON setting?
			8B : PCM 8-bit wave data boolean [1: 8 bit 0: 16 bit]
			SA : Start address of waveform data [PCM]. If the PCM data is 16-bit, the data must be aligned on a 2 byte boundary.
			LSA : Sample count, in distance from SA, to start the loop [at 8b, sample is 1 byte]
			LEA : Sample count, in distance from SA, to end the loop [at 16b, sample is 2 bytes]
			HO : EG Hold Mode Boolean [Changes volume rise according to attack rate setting]
			LS : LPSLINK : Loop start link [Links or unlinks attack rates with looping playback]
			SI : STWINH : Stack wrtie inhibit [FM generator write inhibit, normally false is fine]
			SD : SDIR : Sound direct [0: Attenuated by TL; 1: Output wave data directly]
			TL : Total level [Bitwise data struct which may attenuate or divide the waveform of the input]
			...
			...
			RE : 	LFO Reset - Low frequency oscillator reset switch
			PLF.. : LFO frequency modulation wave form select [OWS] or select [S] [PITCH] [???]
			ALF.. : LFO amplitude modulation wave form select [OWS] or select [A] [AMP]	[???]
			...
			DISDL: Direct data send level [???]
			DIPAN: Direct data pan level [MSB: Left/right boolean, bits 0-4: distance from center]
			EFSDL: Effect send level [???]
			EFPAN: Effect pan level [MSB: Left/right boolean, bits 0-4: distance from center]
			..
			For FM sound source, there are a lot more things to set outside of the indiviual commmand.
		BIG ENDIAN														Byte+1
INTEGER	|---MSB--------------------------------------------------------------------------------------------------------------------LSB--|
	BIT	|	15	|	14	|	13	|	12	|	11	|	10	|	9	|	8	|	7	|	6	|	5	|	4	|	3	|	2	|	1	|	0	|
BYTE	|-------------------------------------------------------------------------------------------------------------------------------|
0		|	-		-		-	|	KX	|	KB	|	SBCTL-2BIT	|	SSCTL-2BIT	|	LPCTL-2BIT	|	8B	|	START ADDRESS	19-16		| keys
2		|													START ADDRESS [SA] 15-0														| start_addr
4		|													LOOP START ADDRESS [LSA] 15-0												| loop_start
6		|													LOOP END ADDRESS	[LEA] 15-0												| playsize
8		|	D2R-DECAY 2 RATE	5 BIT			|	D1R-DECAY 1 RATE	5 BIT			|	HO	|	AR-ATTACK RATE	5 BIT				| decay_1_2_attack
10		|	-	|	LS	|	KRS-KEY RATE SCALE 4 BIT	|	DL-DECAY LEVEL		5 BIT			|	RR-RELEASE RATE	5 BIT				| key_decay_release
12		|	-		-		-		-		-		-	|	SD	|	SI	|	TL-TOTAL LEVEL	8 BIT	[VOLUME]							| attenuation
14		|	MDL-MODULATION LEVEL 4BIT	|	MDXSL-X MODULATION SELECT	6 BIT			|	MDYSL-Y MODULATION SELECT	6 BIT			| FM_data
16		|	-	|	OCT-OCTAVE 4BIT				|	-	| FNS-FREQUENCY NUMBER SWITCH [PITCH] 10 BIT									| oct_fns
18		|	RE	|	LFOF-LFO FREQUENCY 5 BIT			|	PLFOWS-2BIT	|	PLFOS-3BIT [PITCH]	|	AFLOWS-2BIT	|	AFLOS-3BIT	[AMP]	| lfo_data
20		|	-		-		-		-		-		-		-		-		-	|	ISEL-INPUT SELECT 4 BIT		|	IMXL-INPUT MIX LVL	| input_sel
22		|	DISDL-3BIT			|	DIPAN-5 BIT							|	EFSDL-3BIT			|	EFPAN - EFFECT PAN	5 BIT			| pan_send
	BIT	|	15	|	14	|	13	|	12	|	11	|	10	|	9	|	8	|	7	|	6	|	5	|	4	|	3	|	2	|	1	|	0	|
24		|																EMPTY															| blanks
26		|																EMPTY															|
28		|																EMPTY															|
30		|												EMPTY			|	Byte 31 End of individual command slot register				|
INTEGER	|---MSB--------------------------------------------------------------------------------------------------------------------LSB--|
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct{
	unsigned short	keys;
	unsigned short	start_addr;
	unsigned short	loop_start;
	unsigned short	playsize;
	unsigned short	decay_1_2_attack;
	unsigned short	key_decay_release;
	unsigned short	attenuation;
	unsigned short	FM_data; //Should leave 0 for PCM
	unsigned short	oct_fns;
	unsigned short	lfo_data; //Should leave 0 for PCM
	unsigned short	input_sel; //Should leave 0 for PCM
	unsigned short	pan_send;
	unsigned short	blanks[4];
} _ICSR; //SCSP Individual Command Slot Register

typedef struct {
	char loopType; //[0,1,2,3] No loop, normal loop, reverse loop, alternating loop
	unsigned char bitDepth; //0 or 1, boolean
	unsigned short hiAddrBits; //bits 19-16 of...
	unsigned short loAddrBits; //Two 16-bit chunks that when combined, form the start address of the sound.
	unsigned short LSA; //The # of samples forward from the start address to return to after loop.
	unsigned short playsize; //The # of samples to play before the sound shall loop. **Otherwise used as the length of the sound.** Do not leave at 0!
						//8 bit PCM is 1 byte per sample. 16 bit PCM is 2 bytes per sample. Therefore an 8bit PCM is a maximum of 64KB, and 16bit is 128KB.
	unsigned short pitchword; //the OCT & FNS word to use in the ICSR, verbatim.
	unsigned char pan; //Direct pan setting
	unsigned char volume; //Direct volume setting
	unsigned short bytes_per_blank; //Bytes the PCM will play every time the driver is run (vblank)
	unsigned short decompression_size; //Size of the buffer used for an ADX sound effect. Specifically sized by Master SH2.
	unsigned char sh2_permit; //Does the SH2 permit this command? If TRUE, run the command. If FALSE, key its ICSR OFF.
	char icsr_target; //Which explicit ICSR is this to land in? Can be controlled by SH2 or by driver.
} _PCM_CTRL; //Driver Local Command Struct

typedef struct {
	short decomp_demand;
	short decomp_space;
	short recharge_point;
	short work_play_pt;
	short work_decomp_pt;
	short status;
	short pcm_number;
	short current_frame;
	short last_sample;
	short last_last_sample;
	volatile short * dst;
	volatile unsigned short * src;
} _ADX_CTRL; //Driver Local ADX Struct

typedef struct{
	unsigned short start; //System Start Boolean
	unsigned short debug_state; //A region which the driver will write information about its state.
	short drv_adx_coef_1; //The (signed!) coefficient 1 the driver will use to build ADX multiplication tables.
	short drv_adx_coef_2; //The (signed!) coefficient 2 the driver will use to build ADX multiplication tables.
	_PCM_CTRL * pcmCtrl;
} sysComPara;


//Warning: Do not alter the master volume register from within the 68k program.
volatile sysComPara * sh2Com = (volatile sysComPara  *)(ADDR_PRG + DRV_SYS_END);
volatile _ICSR * csr = (volatile _ICSR *)0x100000; //There are 32 of these.
//
_PCM_CTRL	pcmCtrlData[PCM_CTRL_MAX + ADX_CTRL_MAX];
char		ICSR_Busy[32];
char		icsr_index = 0;
short		loopingIndex = 0;
short		volatileIndex = 0;
short		loopingPCMs[PCM_CTRL_MAX];
short		volatilePCMs[PCM_CTRL_MAX];
int			dataTimers[32];
///////////////////////////
#define ADX_STATUS_NONE			(0)
#define ADX_STATUS_DECOMP		(1<<1)
#define ADX_STATUS_EMPTY		(1<<2)
#define ADX_STATUS_FULL			(1<<3)
#define ADX_STATUS_PLAY			(1<<4)
#define ADX_STATUS_START		(1<<5)
#define ADX_STATUS_END			(1<<6)
#define ADX_STATUS_LAST			(1<<7)
#define ADX_STOP			(0)
#define ADX_LOOP			(1)
#define ADX_PROTECTED		(2)
#define ADX_SEMI_PROTECTED	(3)
///////////////////////////
// ADX Control Data Struct
///////////////////////////
_ADX_CTRL adx;
///////////////////////////
// ADX Decompression Tables
// Filled at driver start-up
///////////////////////////
short coef_tbl_1[4096];
short * center_coef_1;
short coef_tbl_2[4096];
short * center_coef_2;
// ADX decompression work buffer
short adx_work_buf[(10 * 1024)];
// ADX decompression nibble table
const short nibble_to_int[16] = {0,1,2,3,4,5,6,7,-8,-7,-6,-5,-4,-3,-2,-1};
// ADX PCM VDP1_BASE_CMDCTRL Dummy. Sound slot that is configured by the ADX system.
short adx_dummy_1 = PCM_CTRL_MAX;

void	driver_data_init(void)
{
	//I'm so bad at C it took me an hour to realize I had to typecast this
	//Assignment is for the SH2, so it adds the SNDRAM base uncached address.
		sh2Com->pcmCtrl = (_PCM_CTRL *)((unsigned int)&pcmCtrlData[0] + 0x25A00000); 
	//Set "start" to a specific number during start up to communicate the driver is initailizing.
		sh2Com->start = 0xFFFF; 
		sh2Com->debug_state = ('I' | ('N'<<8));
	for(char i = 0; i < 32; i++)
	{
		ICSR_Busy[i] = -1;
		dataTimers[i] = 0;
	}
	for(short k = 0; k < PCM_CTRL_MAX; k++)
	{
		pcmCtrlData[k].sh2_permit = 0;
		pcmCtrlData[k].icsr_target = -1;
		loopingPCMs[k] = -1;
		volatilePCMs[k] = -1;
	}
	/////////////////////////////////////////////////////
	// ADX Control Struct init
	adx.status = 0;
	/////////////////////////////////////////////////////
	// ADX Decompression Table Initialization
	/////////////////////////////////////////////////////
	center_coef_1 = &coef_tbl_1[2048];
	center_coef_2 = &coef_tbl_2[2048];
	int last_shift = 0;
	//Filling coef table 1
	int coef_1 = sh2Com->drv_adx_coef_1;
	int coef_2 = sh2Com->drv_adx_coef_2;
	for(int a = -32768; a < 32768; a++)
	{
		int temp_value = (a * coef_1)>>12;
		temp_value = (temp_value > 32767) ? 32767 : (temp_value < -32768) ? -32768 : temp_value;
		if(a>>4 == last_shift) continue;
		center_coef_1[a>>4] = (short)temp_value;
		last_shift = a>>4;
	}
	//Filling coef table 2
	for(int a = -32768; a < 32768; a++)
	{
		int temp_value = (a * coef_2)>>12;
		temp_value = (temp_value > 32767) ? 32767 : (temp_value < -32768) ? -32768 : temp_value;
		if(a>>4 == last_shift) continue;
		center_coef_2[a>>4] = (short)temp_value;
		last_shift = a>>4;
	}
	/////////////////////////
	// ADX Dummy Set-up
	/////////////////////////
	pcmCtrlData[adx_dummy_1].loopType = 1; // fwd loop
	pcmCtrlData[adx_dummy_1].hiAddrBits = (unsigned short)( (unsigned int)&adx_work_buf[0] >> 16);
	pcmCtrlData[adx_dummy_1].loAddrBits = (unsigned short)( (unsigned int)&adx_work_buf[0] & 0xFFFF);
	pcmCtrlData[adx_dummy_1].volume = 7;
	pcmCtrlData[adx_dummy_1].bitDepth = 0;
	// Set start to a specific number to communicate the driver has initialized
	sh2Com->start = 0x7777;
}
/*
NOTICE: To play the same sound struct multiple times per frame you have to copy its PCM_CTRL
struct into another array member, and issue it to play.
*/

#pragma GCC push_options
#pragma GCC optimize ("O3")
void	decompress_adx_frame(_ADX_CTRL * adx)
{
	

//Retrieve the scale which is a big-endian value less than 0x2000
short scale = *adx->src++;
register short hist1 = adx->last_sample;
register short hist2 = adx->last_last_sample;
register short histi;
register int sample_raw;
register short delta1;
register short delta2;
register short delta3;
register short delta4;


for (short i = 0; i < 8; i++)
{
	/* this contains four nibbles, four samples */
   register short sample_short = *adx->src++; 
   /* Even samples use the high nibble. */
   /* Each nibble is a 4 bit two's complement signed value. */
   /* Due to big-endian data, the first nibbles come from the more significant byte */
	delta1 = nibble_to_int[(sample_short & 0xF000) >> 12] * scale;
	delta2 = nibble_to_int[(sample_short & 0xF00) >> 8] * scale;
	delta3 = nibble_to_int[(sample_short & 0xF0) >> 4] * scale;
	delta4 = nibble_to_int[sample_short & 0xF] * scale;
	////////////////////////////////////////////////////////////////////////////////////////////
	//The data of hist1 is kept, so use another register.
	histi = center_coef_1[hist1]; //We do not need to check the histories for their sign, as the tables themsselves are signed.
	//The data of hist2 is discarded, so use the same register.
	hist2 = center_coef_2[hist2]; //We do not need to check the histories for their sign, as the tables themsselves are signed.
	sample_raw = histi + hist2 + delta1;
	sample_raw = (sample_raw > 32767) ? 32767 : (sample_raw < -32768) ? -32768 : sample_raw;
	hist2 = hist1;
	hist1 = sample_raw>>4;
	*adx->dst++ = sample_raw;
	////////////////////////////////////////////////////////////////////////////////////////////
	//The data of hist1 is kept, so use another register.
	histi = center_coef_1[hist1];
	//The data of hist2 is discarded, so use the same register.
	hist2 = center_coef_2[hist2];
	sample_raw = histi + hist2 + delta2;
	sample_raw = (sample_raw > 32767) ? 32767 : (sample_raw < -32768) ? -32768 : sample_raw;
	hist2 = hist1;
	hist1 = sample_raw>>4;
	*adx->dst++ = sample_raw;
	////////////////////////////////////////////////////////////////////////////////////////////
	//The data of hist1 is kept, so use another register.
	histi = center_coef_1[hist1];
	//The data of hist2 is discarded, so use the same register.
	hist2 = center_coef_2[hist2];
	sample_raw = histi + hist2 + delta3;
	sample_raw = (sample_raw > 32767) ? 32767 : (sample_raw < -32768) ? -32768 : sample_raw;
	hist2 = hist1;
	hist1 = sample_raw>>4;
	*adx->dst++ = sample_raw;
	////////////////////////////////////////////////////////////////////////////////////////////
	//The data of hist1 is kept, so use another register.
	histi = center_coef_1[hist1];
	//The data of hist2 is discarded, so use the same register.
	hist2 = center_coef_2[hist2];
	sample_raw = histi + hist2 + delta4;
	sample_raw = (sample_raw > 32767) ? 32767 : (sample_raw < -32768) ? -32768 : sample_raw;
	hist2 = hist1;
	hist1 = sample_raw>>4;
	*adx->dst++ = sample_raw;
}

adx->last_sample = hist1;
adx->last_last_sample = hist2;

}
#pragma GCC pop_options

void	driver_end_sound(short * cst, _PCM_CTRL * lctrl)
{
	csr[*cst].keys = (0); //Key select OFF
	csr[*cst].keys |= 1<<12; //Key EXECUTE OFF
	lctrl->sh2_permit = 0; 
	lctrl->icsr_target = -1;
	ICSR_Busy[*cst] = -1; //Flag this ICSR as no longer busy
	dataTimers[*cst] = 0; //Clear playback timer
}

void	driver_stop_slot(short * cst)
{
	csr[*cst].keys = (0); //Key select OFF
	csr[*cst].keys |= 1<<12; //Key EXECUTE OFF
	dataTimers[*cst] = 0;
}

void	driver_start_slot_with_sound(short * cst, _PCM_CTRL * lctrl)
{
	csr[*cst].keys = (1<<11 | lctrl->bitDepth<<4 | lctrl->hiAddrBits); //Key select ON | Bit depth | high bits of address
	csr[*cst].start_addr = lctrl->loAddrBits;
	csr[*cst].loop_start = lctrl->LSA;
	csr[*cst].playsize = lctrl->playsize;
	csr[*cst].oct_fns = lctrl->pitchword; //It would be possible to include a pseudorandom table to randomize the pitch slightly.
										//The octave is in this word, so that's what you would change for randomized pitch. +1 or -1.
	csr[*cst].pan_send = ((lctrl->volume<<13) | (lctrl->pan<<8));
	
	csr[*cst].decay_1_2_attack = 31;		//We could skip writing these and specify direct data playback,
	csr[*cst].key_decay_release = 31;	//but as far as I understand, this removes sound panning. Attenuation, bit 9 [SD].
	
	csr[*cst].keys |= 1<<12; //KEY EXECUTE must be written last.
}

/*
This function is for non-looping sounds that will restart every time the driver detects sh2 permit. In other words, it is "volatile".
This is a volatile playback function, meaning the sound is stopped and played back again from the start when this is triggered.
The trigger is "sh2_permit", as written by the SH2, expectedly.
To use this wisely, either limit sound trigger by a timer, or simply ensure the routine that has sound playback attached to it has some statute of limitations.
Bonus: You could attach volatile playback to an sh2 function to *know* if its happening more than it should :)
*/
void	play_volatile_sound(_PCM_CTRL * lctrl)
{

	short cst = lctrl->icsr_target;
	
	driver_stop_slot(&cst);
	driver_start_slot_with_sound(&cst, lctrl);
	
	csr[cst].keys |= 1<<12; //KEY EXECUTE must be written last.
	lctrl->sh2_permit = 0; //Disallow sound
	lctrl->icsr_target = -1; //Disassociate this command struct with any ICSR
}

/*
This function is for playing non-looping sounds that will only restart once their entire length has played. In other words, they are "protected".
*/
void	play_protected_sound(short index)
{
	_PCM_CTRL * lctrl = &pcmCtrlData[index];
	short cst = lctrl->icsr_target;
//This ICSR is not presently associated with the protected sound, so we set it up.
		if(ICSR_Busy[cst] != index){
			
	driver_stop_slot(&cst);
	driver_start_slot_with_sound(&cst, lctrl);
	
		} else {
	//Allow live volume and pitch adjustment of semi protected soundssounds
	csr[cst].oct_fns = lctrl->pitchword;							
	csr[cst].pan_send = ((lctrl->volume<<13) | (lctrl->pan<<8));	//
		}
	
		if(dataTimers[cst] >= (lctrl->playsize<<(1 - lctrl->bitDepth)) ) //1 - bitDepth is an expression that will or will not multiply the playsize by 2,
		{																//depending on if it is 8 bits per sample or 16 bits per sample. Remember,
			driver_end_sound(&cst, lctrl);								//if the bits per sample is 16, the playsize >>=1 its data size.
		} else {
			ICSR_Busy[cst] = index;	//Associate this ICSR with this protected sound.
			dataTimers[cst] += lctrl->bytes_per_blank;
		}
}

/*
This function is for playing non-looping sounds that will restart whenever the SH2 commands them to, however, the duration of playback locks an ICSR from other sounds.
*/
void	play_semi_protected_sound(short index)
{
	
	_PCM_CTRL * lctrl = &pcmCtrlData[index];
	short cst = lctrl->icsr_target;
		if(lctrl->sh2_permit == 1)
		{
			
	driver_stop_slot(&cst);
	driver_start_slot_with_sound(&cst, lctrl);
	//With semi-protected sound, the SH2 can command the sound to re-start.
	//To facilitate this, the permission boolean is set to 0 in antipication of the SH2 potentially permitting another start.
	lctrl->sh2_permit = 0; 
		} else {
	//Allow live volume and pitch adjustment of semi protected soundssounds
	csr[cst].oct_fns = lctrl->pitchword;							
	csr[cst].pan_send = ((lctrl->volume<<13) | (lctrl->pan<<8));	//
		}
		
		if(dataTimers[cst] >= (lctrl->playsize<<(1 - lctrl->bitDepth)) ) //1 - bitDepth is an expression that will or will not multiply the playsize by 2,
		{																//depending on if it is 8 bits per sample or 16 bits per sample. Remember,
			driver_end_sound(&cst, lctrl);								//if the bits per sample is 16, the playsize >>=1 its data size.
		} else {
			ICSR_Busy[cst] = index;	//Associate this ICSR with this protected sound.
			dataTimers[cst] += lctrl->bytes_per_blank;
		}
		
		
}

/*
This function is for setting up or updating a sound with looping playback
*/
void	set_looping_sound(short index)
{
	_PCM_CTRL * lctrl = &pcmCtrlData[index];
	short cst = lctrl->icsr_target;
	//This ICSR is not presently associated with the looping sound, so we decimate its current playback.
		if(ICSR_Busy[cst] != index){ 
	csr[cst].keys = (0); //Key select OFF
	csr[cst].keys |= 1<<12; //Key EXECUTE OFF
			}
	//Then, set up the sound.
	csr[cst].keys = (1<<11 | lctrl->loopType<<5 | lctrl->bitDepth<<4 | lctrl->hiAddrBits); //Key select ON | loop type | Bit depth | high bits of address
	csr[cst].start_addr = lctrl->loAddrBits;
	csr[cst].loop_start = lctrl->LSA;
	csr[cst].playsize = lctrl->playsize;
	csr[cst].oct_fns = lctrl->pitchword; //It would be possible to include a pseudorandom table to randomize the pitch slightly.
										//The octave is in this word, so that's what you would change for randomized pitch. +1 or -1.
	csr[cst].pan_send = ((lctrl->volume<<13) | (lctrl->pan<<8));
	
	csr[cst].decay_1_2_attack = 31;		//We could skip writing these and specify direct data playback,
	csr[cst].key_decay_release = 31;	//but as far as I understand, this removes sound panning. Attenuation, bit 9 [SD].
	
	csr[cst].keys |= 1<<12; //KEY EXECUTE must be written last.

	ICSR_Busy[cst] = index;	//Associate this ICSR with the looping sound
}

void	play_adx(short adx_index, short adx_control_type)
{
	_PCM_CTRL * snd = &pcmCtrlData[adx_index];
	short cst = snd->icsr_target;
	sh2Com->debug_state = adx.status;
	///////////////////////////////////////
	// ADX Play-type Condition Management
	// A structured copy of "PCM_PROTECTED", "PCM_SEMI", and "PCM_FWD_LOOP".
	// It should be noted that ADX sounds **cannot** be played volatile, or in any other kind of loop.
	if(snd->sh2_permit == 1)
	{
		if(adx_control_type == ADX_SEMI_PROTECTED || (adx_control_type == ADX_PROTECTED && adx.status == ADX_STATUS_NONE))
		{
			//sh2Com->debug_state = ('A' | ('S'<<8));
			if(adx_control_type == ADX_SEMI_PROTECTED) snd->sh2_permit = 0;
			adx.status = ADX_STATUS_START;
			//Decompresion demand is the # of bytes to decompress every 1/60 seconds (60hz).
			// + 64 must be added for magain ahead of the SCSP's playback. It is the size of 1 ADX frame.
			adx.decomp_demand = snd->bytes_per_blank + 64;
			//Decompression space is the size of the playback buffer, in bytes.
			adx.decomp_space = snd->decompression_size;
			//Recharge point is the point at which decompression will start.
			//It is compared against a value to which the bytes per blank is added every 1/60 seconds.
			adx.recharge_point = snd->decompression_size >> 1;
			adx.current_frame = 0;
			adx.src = (unsigned short *)((int)((snd->hiAddrBits<<16) | (snd->loAddrBits)));
			adx.dst = &adx_work_buf[0];
			adx.work_decomp_pt = 0;
			adx.work_play_pt = 0;
		} else if(adx_control_type == ADX_LOOP && adx.status == ADX_STATUS_NONE)
		{
			adx.status = ADX_STATUS_START;
			//Decompresion demand is the # of bytes to decompress every 1/60 seconds (60hz).
			// + 64 must be added for magain ahead of the SCSP's playback. It is the size of 1 ADX frame.
			adx.decomp_demand = snd->bytes_per_blank + 64;
			//Decompression space is the size of the playback buffer, in bytes.
			adx.decomp_space = snd->decompression_size;
			//Recharge point is the point at which decompression will start.
			//It is compared against a value to which the bytes per blank is added every 1/60 seconds.
			adx.recharge_point = snd->decompression_size >> 1;
			adx.current_frame = 0;
			adx.src = (unsigned short *)((int)((snd->hiAddrBits<<16) | (snd->loAddrBits)));
			adx.dst = &adx_work_buf[0];
			adx.work_decomp_pt = 0;
			adx.work_play_pt = 0;
		}
	}
	
	///////////////////////////////////////
	// ADX Starting
	// When an ADX sound is started, first our decompression demand for this refresh cycle is completed.
	// The adx dummy recieves playback parameters from the ADX PCM slot, including the ICSR to be used.
	// This is used because we need more data than we have in a single PCM slot to control a separate PCM loop.
	// The ADX dummy is set to point to the decompression buffer,
	// and the SCSP is set to play back 16-bit signed PCM from that region.
	// On the next refresh cycle, the driver will undergo decompression of more data, as the buffer is not full.
	if(adx.status == ADX_STATUS_START)
	{
		//sh2Com->debug_state = ('S' | ('T'<<8));
		//Decompress (decomp_demand) # of bytes to (dst)
		//Then start playing the sound
		for(short i = 0; i < adx.decomp_demand; )
		{
			decompress_adx_frame(&adx);
			i += 64;
			adx.current_frame += 1;
		}
		adx.work_decomp_pt += adx.decomp_demand;
		//ADX dummy 1 being a looping PCM control set to point at the adx work buf.
		pcmCtrlData[adx_dummy_1].playsize = (adx.decomp_space)>>1;
		pcmCtrlData[adx_dummy_1].pitchword = snd->pitchword;
		pcmCtrlData[adx_dummy_1].bytes_per_blank = snd->bytes_per_blank;
		pcmCtrlData[adx_dummy_1].pan = snd->pan;
		pcmCtrlData[adx_dummy_1].volume = snd->volume;
		pcmCtrlData[adx_dummy_1].icsr_target = cst;
		set_looping_sound(adx_dummy_1);
		adx.status |= (ADX_STATUS_PLAY | ADX_STATUS_DECOMP);
	} else if(adx.status & ADX_STATUS_DECOMP && !(adx.status & ADX_STATUS_FULL))
	{
		///////////////////////////////////////
		// ADX Real-time Decompression
		// Very simple - an amount of ADX frames is decompressed every refresh cycle.
		// An ADX "frame" is 18 bytes which contains 64 4-bit nibbles and 1 16-bit scale value.
		// It should be noted, if it wasn't clear already, that your sound's byterate must be divisible by 64.
		// The amount of frames decompressed is the 60hz byterate of the raw PCM frequency, divided by 64, plus 1.
		for(short i = 0; i < adx.decomp_demand; )
		{
			///////////////////////////////////////
			// ADX Decompression Completion Condition
			// The playsize of the ADX PCM control slot contains the # of ADX frames of the sound.
			// If the current frame being decompressed is greater than this, the sound has been fully decompressed.
			// The status is updated as such, and no more ADX frames are to be decompressed (there are no more!).
			if(adx.current_frame > snd->playsize)
			{
				adx.status |= ADX_STATUS_FULL;
				break;
			}
			decompress_adx_frame(&adx);
			i += 64;
			adx.current_frame += 1;
		}
		adx.work_decomp_pt += adx.decomp_demand;
	}

	if(adx.status & ADX_STATUS_PLAY)
	{
		adx.work_play_pt += snd->bytes_per_blank;
		///////////////////////////////////////
		// ADX Decompression Starting
		// If the play pointer has met or exceeded the recharge point,
		// this is the time we have have calculated as the appropriate time to begin decompression into the buffer.
		// We do start this now to maintain synchronization: It will finish before the SCSP gets back here after it loops,
		// and it will be done after the SCSP has looped.
		if(adx.work_play_pt >= adx.recharge_point && !(adx.status & ADX_STATUS_FULL))
		{
			adx.status |= ADX_STATUS_DECOMP;
		}
		///////////////////////////////////////
		// ADX Decompression Ending
		// If we have decompressed enough data to fill up the decompression buffer,
		// cease decompression and re-set the decompression target tracker and pointer.
		if(adx.work_decomp_pt >= adx.decomp_space)
		{
			adx.status ^= ADX_STATUS_DECOMP;
			adx.work_decomp_pt = 0;
			adx.dst = &adx_work_buf[0];
		}
		///////////////////////////////////////
		// ADX Play Tracking
		// If the maximal position of the SCSP in the playback buffer will have met or exceeded the size of it,
		// we **know** the SCSP is going to go back to the beginning of the buffer.
		// We know this because the SCSP has been set to play back this region of sound as a loop.
		if(adx.work_play_pt >= adx.decomp_space)
		{
			adx.work_play_pt = 0;
		}
		///////////////////////////////////////
		// ADX End Condition
		// When we have decompressed all the data from the ADX sound,
		// we have flagged the ADX status as FULL. The sound has been fully decompressed.
		// At this point, we shouldn't immediately end the sound. The decompression point is ahead of the playback point.
		// Thus, we want to end the sound only when the play point meets or passes the decompression point.
		if(adx.work_play_pt >= adx.work_decomp_pt && adx.status & ADX_STATUS_FULL)
		{
			if(adx_control_type == ADX_LOOP)
			{
			//To set an ADX sound to loop, just.. restart it!
			//But you *do* have to end the sound slot, and there is a blanking period involved.
			adx.status = ADX_STATUS_START;
			adx.current_frame = 0;
			adx.src = (unsigned short *)((int)((snd->hiAddrBits<<16) | (snd->loAddrBits)));
			adx.dst = &adx_work_buf[0];
			adx.work_decomp_pt = 0;
			adx.work_play_pt = 0;
			driver_end_sound(&cst, &pcmCtrlData[adx_dummy_1]);
			} else {
			adx.status = ADX_STATUS_END;
			}
		}
	}

	///////////////////////////////////////
	// ADX Stop Condition
	// This is controlled by conditions above, and exactly what gets us here changes.
	// Control data from the ADX dummy, ADX PCM control, and ADX control struct is cleared.
	// In all cases, it is acceptable to indicate that the SH2 no longer permits the sound as looping conditions happen earlier.
	// However, it's not always needed.
	if(adx.status & ADX_STATUS_END || adx_control_type == ADX_STOP)
	{
		snd->sh2_permit = 0;
		adx.status = ADX_STATUS_NONE;
		driver_end_sound(&cst, &pcmCtrlData[adx_dummy_1]);
		driver_end_sound(&cst, snd);
	}

}


void	pcm_control_loop(void)
{
	icsr_index = 0;
	_PCM_CTRL * lctrl;

	loopingIndex = 0;
	volatileIndex = 0;
	
	/*
	A new control loop for multiple ADX sounds is required.
	*/
	
	//Loop to find the looping indexes
	for(short k = 0; k < PCM_CTRL_MAX; k++)
	{
		lctrl = &pcmCtrlData[k];
		if(lctrl->loopType == PCM_VOLATILE && lctrl->bitDepth != PCM_TYPE_ADX)
		{
			volatilePCMs[volatileIndex] = k;
			volatileIndex++;
		} else if(lctrl->loopType != PCM_VOLATILE)
		{
			loopingPCMs[loopingIndex] = k;
			loopingIndex++;
		}
	}
	
	//Control loop for looping or protected sounds
	for(short l = 0; l < loopingIndex; l++)
	{
		lctrl = &pcmCtrlData[loopingPCMs[l]];
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//	PCM LOOP CONTROL SEGMENT
		//	PCM loop start and end conditions are based on SH2.
		//	Write 1 to start the loop and 0 to end it.
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if(lctrl->loopType > 0)
		{
			if(lctrl->sh2_permit == 1) //If the loop is allowed by SH2, either start it, or update its parameters.
			{
				if(lctrl->icsr_target == -1) //The loop is not associated with an ICSR which _should_ mean it is not playing.
				{
					//
					while(ICSR_Busy[icsr_index] != -1) //Find an inactive channel for the sound
					{
						icsr_index++; //Set forward the icsr_index until it has reached an inactive ICSR
					}
					if(icsr_index >= 32) break;
					//
					//Start the sound
					lctrl->icsr_target = icsr_index;
					if(lctrl->bitDepth == PCM_TYPE_ADX)
					{
					play_adx(loopingPCMs[l], ADX_LOOP);
					} else {
					set_looping_sound(loopingPCMs[l]); 
					}
					icsr_index++;
				} else {
					//Update the sound
					if(lctrl->bitDepth == PCM_TYPE_ADX)
					{
					play_adx(loopingPCMs[l], ADX_LOOP);
					} else {
					set_looping_sound(loopingPCMs[l]); 
					}
				}
			} else if(lctrl->icsr_target != -1) //If the loop is not allowed by the SH2, and it is associated with an ICSR, it is active. Turn it off.
			{
				if(lctrl->bitDepth == PCM_TYPE_ADX)
				{
					play_adx(loopingPCMs[l], ADX_STOP);
				} else {
					short csr = lctrl->icsr_target;
					driver_end_sound(&csr, lctrl);
				}
			}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//	PROTECTED SOUND CONTROL SEGMENT
		//	Protected sounds are expected to manage permission end by themselves.
		//	In this case, the SH2 is never to write 0 to SH2 Permit to stop a protected sound.
		//	To prematurely stop a protected sound, set its volume to zero and let the timer conclude.
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		} else if(lctrl->loopType == PCM_PROTECTED  && lctrl->sh2_permit == 1)//If normal protected sound, if permitted...
		{
			if(lctrl->icsr_target == -1)	//If first run (no current ICSR)
			{
				//
				while(ICSR_Busy[icsr_index] != -1) //Find an inactive channel for the sound
				{
					icsr_index++; //Set forward the icsr_index until it has reached an inactive ICSR
				}
				if(icsr_index >= 32) break;
				//
				//Start the sound
				lctrl->icsr_target = icsr_index;
				if(lctrl->bitDepth == PCM_TYPE_ADX)
				{
				play_adx(loopingPCMs[l], ADX_PROTECTED);
				} else {
				play_protected_sound(loopingPCMs[l]); 
				}
				icsr_index++;
			} else {
				//Update the sound
				if(lctrl->bitDepth == PCM_TYPE_ADX)
				{
				play_adx(loopingPCMs[l], ADX_PROTECTED);
				} else {
				play_protected_sound(loopingPCMs[l]); 
				}
			}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//	SEMI-PROTECTED SOUND CONTROL SEGMENT
		//	Semi-protected sounds manage the SH2 permit parameter but will still run the timer to the release of the ICSR if they are not permitted.
		//	Permission 0 only disallows updates once the sound has started.
		//	Because of this, writing SH2 Permit to 0 on a semi-protected sound results in undefined behaviour.
		//	To stop a semi-protected sound, change the volume to 0 and let the timer conclude.
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		} else if(lctrl->loopType == PCM_SEMI) //If semi-protected sound...
		{
			if(lctrl->icsr_target == -1 && lctrl->sh2_permit == 1) //Sound does not currently occupy an ICSR
			{
				//
				while(ICSR_Busy[icsr_index] != -1) //Find an inactive channel for the sound
				{
					icsr_index++; //Set forward the icsr_index until it has reached an inactive ICSR
				}
				if(icsr_index >= 32) break;
				//
				//Start the sound
				lctrl->icsr_target = icsr_index;
				if(lctrl->bitDepth == PCM_TYPE_ADX)
				{
				play_adx(loopingPCMs[l], ADX_SEMI_PROTECTED);
				} else {
				play_semi_protected_sound(loopingPCMs[l]); 
				}
				icsr_index++;
			} else if(lctrl->icsr_target != -1){ //Sound has an ICSR
				//Update the sound
				if(lctrl->bitDepth == PCM_TYPE_ADX)
				{
				play_adx(loopingPCMs[l], ADX_SEMI_PROTECTED);
				} else {
				play_semi_protected_sound(loopingPCMs[l]); 
				}
			}
		}
	//////////////////////////////
	//PCM Control Loop End Stub
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	VOLATILE SOUND CONTROL SEGMENT
	//	Volatile sounds are essentially uncontrolled. They immediately write the SH2 no longer permits the sound after the first blank of playback.
	//	But they will still play to their conclusion, provided no other sound decides to occupy their ICSR.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for(short v = 0; v < volatileIndex; v++)
	{
		lctrl = &pcmCtrlData[volatilePCMs[v]];
		//
		while(ICSR_Busy[icsr_index] != -1)
		{
			icsr_index++; //Set forward the icsr_index until it has reached an inactive ICSR
		}
		if(icsr_index >= 32) break;
		//
		if(lctrl->loopType == 0 && lctrl->sh2_permit == 1){
			lctrl->icsr_target = icsr_index;
			play_volatile_sound(lctrl);
			icsr_index++;
		}
	}

}

void	_start(void)
{
	driver_data_init();
	while(1){
		//
		do{
			//sh2Com->debug_state = ('W' | ('A'<<8));
			if(sh2Com->start == 1) break;
		}while(1);
			sh2Com->start = 0;
		// Region will run the program once for every time the SH2 commands the driver to start.
		pcm_control_loop();
		

	}

}

