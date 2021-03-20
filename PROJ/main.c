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
#define ADX_CTRL_MAX	(3)
#define DRV_SYS_END		(46 * 1024) //System defined safe end of driver's address space
//////////////////////////////////////////////////////////////////////////////
#define	PCM_ALT_LOOP	(3)
#define PCM_RVS_LOOP	(2)
#define PCM_FWD_LOOP	(1)
#define PCM_VOLATILE	(0)
#define PCM_PROTECTED	(-1)
#define PCM_SEMI		(-2)
#define ADX_STREAM		(-3)
#define ADX_STREAM_BUFFERED_FRAME_CT		(1024)
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
	volatile char icsr_target; //Which explicit ICSR is this to land in? Can be controlled by SH2 or by driver.
} _PCM_CTRL; //Driver Local Command Struct

typedef struct {
	short decomp_demand;
	short decomp_space;
	short recharge_point;
	short work_play_pt;
	short work_decomp_pt;
	volatile short status;
	short pcm_number;
	short current_frame;
	short last_sample;
	short last_last_sample;
	short passed_buffers;
	char	buf_string[2];
	volatile short * dst;
	volatile short * original_dst;
	volatile unsigned short * src;
	volatile unsigned short * original_src;
} _ADX_CTRL; //Driver Local ADX Struct

typedef struct{
	volatile unsigned short start; //System Start Boolean
	volatile short adx_stream_comm; //A region which the driver will write information about its state.
	volatile short drv_adx_coef_1; //The (signed!) coefficient 1 the driver will use to build ADX multiplication tables.
	volatile short drv_adx_coef_2; //The (signed!) coefficient 2 the driver will use to build ADX multiplication tables.
	volatile _PCM_CTRL * pcmCtrl;
} sysComPara;


//Warning: Do not alter the master volume register from within the 68k program.
volatile sysComPara * sh2Com = (volatile sysComPara  *)(ADDR_PRG + DRV_SYS_END);
volatile _ICSR * csr = (volatile _ICSR *)0x100000; //There are 32 of these.
//
_PCM_CTRL	pcmCtrlData[PCM_CTRL_MAX + ADX_CTRL_MAX];
char		ICSR_Busy[32];
char		icsr_index = 0;
short		loopingPCMs[PCM_CTRL_MAX];
short		volatilePCMs[PCM_CTRL_MAX];
short		adxPCMs[PCM_CTRL_MAX];
int			dataTimers[32];
///////////////////////////
#define ADX_STATUS_NONE			(0)
#define ADX_STATUS_ACTIVE		(1)
#define ADX_STATUS_DECOMP		(1<<1)
#define ADX_STATUS_EMPTY		(1<<2)
#define ADX_STATUS_FULL			(1<<3)
#define ADX_STATUS_PLAY			(1<<4)
#define ADX_STATUS_START		(1<<5)
#define ADX_STATUS_END			(1<<6)
#define ADX_STATUS_LAST			(1<<7)
///////////////////////////
// ADX Control Data Struct
///////////////////////////
_ADX_CTRL adx[ADX_CTRL_MAX];
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
// ADX PCM_CTRL Dummy. Sound slot that is configured by the ADX system.
short adx_dummy[ADX_CTRL_MAX];
// ADX Buffer Control Data
// "6" buffer slots
/*
	-----------------------NTSC VERSION----------------------------
		DRIVER REFRESH CYCLE : 60 HZ / 16.66ms
	Bitrate	|	Buffer Size	|	Demand	|	Slots?	|	IMA Slots?
	7680		2560			320			2			1
	11520		5376			448			3			2
	15360		9216			576			4			3
	23040		19968			832			6			6
			(Total: 20KB) 	(Total Budget: 960)
	----------------------PAL VERSION------------------------------
		DRIVER REFRESH CYCLE : 50 HZ / 20ms
	Bitrate	|	Buffer Size	|	Demand	|	Slots?	|	IMA Slots?
	6400		2560			320			2			?
	9600		5376			448			3			?
	12800		9216			576			4			?
	19200		19968			832			6			?
			(Total: 20KB) 	(Total Budget: 1152)
*/
short * adx_buf_addr[3] = {&adx_work_buf[0], &adx_work_buf[4608], &adx_work_buf[6000]};
short adx_buffer_used[6];

void	driver_data_init(void)
{
	//I'm so bad at C it took me an hour to realize I had to typecast this
	//Assignment is for the SH2, so it adds the SNDRAM base uncached address.
		sh2Com->pcmCtrl = (_PCM_CTRL *)((unsigned int)&pcmCtrlData[0] + 0x25A00000); 
	//Set "start" to a specific number during start up to communicate the driver is initailizing.
		sh2Com->start = 0xFFFF; 
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
		adxPCMs[k] = -1;
	}
	/////////////////////////////////////////////////////
	// ADX Control Struct init
	/////////////////////////
	for(short a = 0; a < ADX_CTRL_MAX; a++)
	{
		adx_dummy[a] = PCM_CTRL_MAX + a;
		adx[a].pcm_number = -1;
		adx[a].status = ADX_STATUS_NONE;
		pcmCtrlData[adx_dummy[a]].loopType = 1; // fwd loop
		pcmCtrlData[adx_dummy[a]].hiAddrBits = (unsigned short)( (unsigned int)&adx_work_buf[0] >> 16);
		pcmCtrlData[adx_dummy[a]].loAddrBits = (unsigned short)( (unsigned int)&adx_work_buf[0] & 0xFFFF);
		pcmCtrlData[adx_dummy[a]].volume = 7;
		pcmCtrlData[adx_dummy[a]].bitDepth = 0;
	}
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
	
static short scale_table[16];
static short last_scale = 0;

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

//Optimization: This reduces the most multiplications per 32 samples to 16, halving the # of muls.
//Loop unrolling also means only one logical branch is added. The effective cost saving per sample is at least 32 cycles,
//however it is likely more, as the scale between frames is not guaranteed to vary.
if(scale != last_scale)
{
	scale_table[0] = nibble_to_int[0] * scale; scale_table[8] = nibble_to_int[8] * scale;
	scale_table[1] = nibble_to_int[1] * scale; scale_table[9] = nibble_to_int[9] * scale;
	scale_table[2] = nibble_to_int[2] * scale; scale_table[10] = nibble_to_int[10] * scale;
	scale_table[3] = nibble_to_int[3] * scale; scale_table[11] = nibble_to_int[11] * scale;
	scale_table[4] = nibble_to_int[4] * scale; scale_table[12] = nibble_to_int[12] * scale;
	scale_table[5] = nibble_to_int[5] * scale; scale_table[13] = nibble_to_int[13] * scale;
	scale_table[6] = nibble_to_int[6] * scale; scale_table[14] = nibble_to_int[14] * scale;
	scale_table[7] = nibble_to_int[7] * scale; scale_table[15] = nibble_to_int[15] * scale;
}
last_scale = scale;

for (short i = 0; i < 8; i++)
{
	/* this contains four nibbles, four samples */
   register short sample_short = *adx->src++; 
   /* Even samples use the high nibble. */
   /* Each nibble is a 4 bit two's complement signed value. */
   /* Due to big-endian data, the first nibbles come from the more significant byte */
	delta1 = scale_table[(sample_short & 0xF000) >> 12];
	delta2 = scale_table[(sample_short & 0xF00) >> 8];
	delta3 = scale_table[(sample_short & 0xF0) >> 4];
	delta4 = scale_table[sample_short & 0xF];
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

void	driver_end_sound(volatile char * cst, _PCM_CTRL * lctrl)
{
	csr[*cst].keys = (0); //Key select OFF
	csr[*cst].keys |= 1<<12; //Key EXECUTE OFF
	lctrl->sh2_permit = 0; 
	lctrl->icsr_target = -1;
	ICSR_Busy[*cst] = -1; //Flag this ICSR as no longer busy
	dataTimers[*cst] = 0; //Clear playback timer
}

void	driver_stop_slot(volatile char * cst)
{
	csr[*cst].keys = (0); //Key select OFF
	csr[*cst].keys |= 1<<12; //Key EXECUTE OFF
	dataTimers[*cst] = 0;
}

short	find_free_slot(_PCM_CTRL * lctrl)
{
	//
	while(ICSR_Busy[icsr_index] != -1) //Find an inactive channel for the sound
	{
		icsr_index++; //Set forward the icsr_index until it has reached an inactive ICSR
	}
	//If there is no free ICSR, leave the function -- leaving the ICSR set to -1.
	if(icsr_index >= 32) return -1;
	//
	//Give sound an ICSR index
	lctrl->icsr_target = icsr_index;
	return 1;
}


void	driver_start_slot_with_sound(volatile char * cst, _PCM_CTRL * lctrl)
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
	
	driver_stop_slot(&lctrl->icsr_target);
	driver_start_slot_with_sound(&lctrl->icsr_target, lctrl);
	
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
			
	driver_stop_slot(&lctrl->icsr_target);
	driver_start_slot_with_sound(&lctrl->icsr_target, lctrl);
	
		} else {
	//Allow live volume and pitch adjustment of semi protected soundssounds
	csr[cst].oct_fns = lctrl->pitchword;							
	csr[cst].pan_send = ((lctrl->volume<<13) | (lctrl->pan<<8));	//
		}
	
		if(dataTimers[cst] >= (lctrl->playsize<<(1 - lctrl->bitDepth)) ) //1 - bitDepth is an expression that will or will not multiply the playsize by 2,
		{																//depending on if it is 8 bits per sample or 16 bits per sample. Remember,
			driver_end_sound(&lctrl->icsr_target, lctrl);								//if the bits per sample is 16, the playsize >>=1 its data size.
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
			
	driver_stop_slot(&lctrl->icsr_target);
	driver_start_slot_with_sound(&lctrl->icsr_target, lctrl);
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
			driver_end_sound(&lctrl->icsr_target, lctrl);								//if the bits per sample is 16, the playsize >>=1 its data size.
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

void	play_adx(short pcm_control_index, short loop_type)
{
	_PCM_CTRL * snd = &pcmCtrlData[pcm_control_index];
	short target_adx = -1;
	short buffers_empty = 0;
		// sh2Com->adx_stream_comm = adx[0].pcm_number;
		// sh2Com->drv_adx_coef_1 = adx[1].pcm_number;
		// sh2Com->drv_adx_coef_2 = adx[2].pcm_number;
	///////////////////////////////////////
	// ADX Condition Manager Selection
	for(short f = 0; f < ADX_CTRL_MAX; f++)
	{
		if(adx[f].pcm_number == -1 && adx[f].status == ADX_STATUS_NONE && snd->icsr_target == -1 && snd->sh2_permit == 1)
		{
			//Try to find a free slot to play the sound in.
			//If none is found, exit this function.
			if(!find_free_slot(snd)) return;
			target_adx = f;
			adx[f].pcm_number = pcm_control_index;
			adx[f].status = ADX_STATUS_ACTIVE;
			if(snd->bytes_per_blank == 256)
			{
				//Find two free slots
				for(short l = 0; l < 6; l++)
				{
					if(adx_buffer_used[l] == 0)
					{
						buffers_empty++;
					}
					if(buffers_empty >= 2) break;
				}
				if(!adx_buffer_used[5] && !adx_buffer_used[4])
				{
					adx_buffer_used[4] = 1;
					adx_buffer_used[5] = 1;
					adx[f].original_dst = adx_buf_addr[2];
					adx[f].buf_string[0] = 4;
					adx[f].buf_string[1] = 5;
				} else if(!adx_buffer_used[3] && !adx_buffer_used[2])
				{
					adx_buffer_used[2] = 1;
					adx_buffer_used[3] = 1;
					adx[f].original_dst = adx_buf_addr[1];
					adx[f].buf_string[0] = 2;
					adx[f].buf_string[1] = 3;
				} else if(!adx_buffer_used[0] && !adx_buffer_used[1])
				{
					adx_buffer_used[0] = 1;
					adx_buffer_used[1] = 1;
					adx[f].original_dst = adx_buf_addr[0];
					adx[f].buf_string[0] = 0;
					adx[f].buf_string[1] = 1;
				} else {
					adx[f].pcm_number = -1;
					adx[f].status = ADX_STATUS_NONE;
					driver_end_sound(&snd->icsr_target, snd);
					return;
				}
			} else if(snd->bytes_per_blank == 384)
			{
				//Find three free slots
				for(short l = 0; l < 6; l++)
				{
					if(adx_buffer_used[l] == 0)
					{
						buffers_empty++;
					}
					if(buffers_empty >= 3) break;
				}
				if(!adx_buffer_used[5] && !adx_buffer_used[4] && !adx_buffer_used[3])
				{
					adx_buffer_used[3] = 1;
					adx_buffer_used[4] = 1;
					adx_buffer_used[5] = 1;
					adx[f].original_dst = adx_buf_addr[1];
					adx[f].buf_string[0] = 3;
					adx[f].buf_string[1] = 5;
				} else if(!adx_buffer_used[2] && !adx_buffer_used[1] && !adx_buffer_used[0])
				{
					adx_buffer_used[0] = 1;
					adx_buffer_used[1] = 1;
					adx_buffer_used[2] = 1;
					adx[f].original_dst = adx_buf_addr[0];
					adx[f].buf_string[0] = 0;
					adx[f].buf_string[1] = 2;
				} else {
					adx[f].pcm_number = -1;
					adx[f].status = ADX_STATUS_NONE;
					driver_end_sound(&snd->icsr_target, snd);
					return;
				}
			} else if(snd->bytes_per_blank == 512)
			{
				//Find four free slots
				for(short l = 0; l < 6; l++)
				{
					if(adx_buffer_used[l] == 0)
					{
						buffers_empty++;
					}
					if(buffers_empty >= 4) break;
				}
				if(!adx_buffer_used[5] && !adx_buffer_used[4] && !adx_buffer_used[3] && !adx_buffer_used[2])
				{
					adx_buffer_used[2] = 1;
					adx_buffer_used[3] = 1;
					adx_buffer_used[4] = 1;
					adx_buffer_used[5] = 1;
					adx[f].original_dst = adx_buf_addr[1];
					adx[f].buf_string[0] = 2;
					adx[f].buf_string[1] = 5;
				} else if(!adx_buffer_used[3] && !adx_buffer_used[2] && !adx_buffer_used[1] && !adx_buffer_used[0])
				{
					adx_buffer_used[0] = 1;
					adx_buffer_used[1] = 1;
					adx_buffer_used[2] = 1;
					adx_buffer_used[3] = 1;
					adx[f].original_dst = adx_buf_addr[0];
					adx[f].buf_string[0] = 0;
					adx[f].buf_string[1] = 3;
				} else {
					adx[f].pcm_number = -1;
					adx[f].status = ADX_STATUS_NONE;
					driver_end_sound(&snd->icsr_target, snd);
					return;
				}
			} else if(snd->bytes_per_blank == 768)
			{
				//Only work if no slots are used
				
				for(short l = 0; l < 6; l++)
				{
					if(adx_buffer_used[l] == 0)
					{
						buffers_empty++;
					}
					if(buffers_empty >= 6) break;
				}
				if(buffers_empty != 6)
				{
					adx[f].pcm_number = -1;
					adx[f].status = ADX_STATUS_NONE;
					driver_end_sound(&snd->icsr_target, snd);
					return;
				} else {
					adx_buffer_used[0] = 1;
					adx_buffer_used[1] = 1;
					adx_buffer_used[2] = 1;
					adx_buffer_used[3] = 1;
					adx_buffer_used[4] = 1;
					adx_buffer_used[5] = 1;
					adx[f].original_dst = adx_buf_addr[0];
					adx[f].buf_string[0] = 0;
					adx[f].buf_string[1] = 5;
				}

			} else {
				//Invalid byte-rate
					adx[f].pcm_number = -1;
					adx[f].status = ADX_STATUS_NONE;
					driver_end_sound(&snd->icsr_target, snd);
					return;
			}
			break;
		} else if(adx[f].pcm_number == pcm_control_index && (adx[f].status & ADX_STATUS_ACTIVE))
		{
			target_adx = f;
			break;
		}
	}
		//If the above loops did not find an available ADX slot, this value will be -1.
		//We should not continue in this case.
		if(target_adx == -1) return;
	///////////////////////////////////////
	// ADX Play-type Condition Management
	if(snd->sh2_permit == 1)
	{
		if(loop_type == PCM_SEMI || (loop_type == PCM_PROTECTED && adx[target_adx].status == ADX_STATUS_ACTIVE))
		{
			//sh2Com->adx_stream_comm = ('A' | ('S'<<8));
			if(loop_type == PCM_SEMI) snd->sh2_permit = 0;
			adx[target_adx].status = (ADX_STATUS_START | ADX_STATUS_ACTIVE);
			//Decompression demand is the # of bytes to decompress every 1/60 seconds (60hz).
			// + 64 must be added for margin ahead of the SCSP's playback. It is the size of 1 ADX frame.
			adx[target_adx].decomp_demand = snd->bytes_per_blank + 64;
			//Decompression space is the size of the playback buffer, in bytes.
			adx[target_adx].decomp_space = snd->decompression_size;
			//Recharge point is the point at which decompression will start.
			//It is compared against a value to which the bytes per blank is added every 1/60 seconds.
			adx[target_adx].recharge_point = snd->decompression_size >> 1;
			adx[target_adx].current_frame = 0;
			adx[target_adx].original_src = (unsigned short *)((int)((snd->hiAddrBits<<16) | (snd->loAddrBits)));
			adx[target_adx].src = (unsigned short *)((int)((snd->hiAddrBits<<16) | (snd->loAddrBits)));
			adx[target_adx].dst = adx[target_adx].original_dst;
			adx[target_adx].work_decomp_pt = 0;
			adx[target_adx].work_play_pt = 0;
			adx[target_adx].last_sample = 0;
			adx[target_adx].last_last_sample = 0;
			adx[target_adx].passed_buffers = 0;
			sh2Com->adx_stream_comm = 0;
		} else if((loop_type == PCM_FWD_LOOP || loop_type == ADX_STREAM) && adx[target_adx].status == ADX_STATUS_ACTIVE)
		{
			adx[target_adx].status = (ADX_STATUS_START | ADX_STATUS_ACTIVE);
			//Decompression demand is the # of bytes to decompress every 1/60 seconds (60hz).
			// + 64 must be added for margin ahead of the SCSP's playback. It is the size of 1 ADX frame.
			adx[target_adx].decomp_demand = snd->bytes_per_blank + 64;
			//Decompression space is the size of the playback buffer, in bytes.
			adx[target_adx].decomp_space = snd->decompression_size;
			//Recharge point is the point at which decompression will start.
			//It is compared against a value to which the bytes per blank is added every 1/60 seconds.
			adx[target_adx].recharge_point = snd->decompression_size >> 1;
			adx[target_adx].current_frame = (loop_type == ADX_STREAM) ? 2 : 0;
			adx[target_adx].original_src = (unsigned short *)((int)((snd->hiAddrBits<<16) | (snd->loAddrBits)));
			adx[target_adx].src = (unsigned short *)((int)((snd->hiAddrBits<<16) | (snd->loAddrBits)));
			adx[target_adx].dst = adx[target_adx].original_dst;
			adx[target_adx].work_decomp_pt = 0;
			adx[target_adx].work_play_pt = 0;
			adx[target_adx].last_sample = 0;
			adx[target_adx].last_last_sample = 0;
			adx[target_adx].passed_buffers = 0;
			sh2Com->adx_stream_comm = 0;
		}
	}
	//If this function attempted to run past this point to manage an ADX sound without a valid ICSR,
	//exit this function. There is no point in running it then, as it won't play sound.
	if(snd->icsr_target == -1) return;
	//If this function attempted to run past this point with the ADX controller status at "NONE",
	//the attached PCM control data is in an error state. Correct this error, and exit the function.
	if(adx[target_adx].status == ADX_STATUS_NONE)
	{
		adx[target_adx].pcm_number = -1;
		driver_end_sound(&snd->icsr_target, &pcmCtrlData[adx_dummy[target_adx]]);
		return;
	}
	///////////////////////////////////////
	// ADX Starting
	// When an ADX sound is started, first our decompression demand for this refresh cycle is completed.
	// The adx dummy recieves playback parameters from the ADX PCM slot, including the ICSR to be used.
	// This is used because we need more data than we have in a single PCM slot to control a separate PCM loop.
	// The ADX dummy is set to point to the decompression buffer,
	// and the SCSP is set to play back 16-bit signed PCM from that region.
	// On the next refresh cycle, the driver will undergo decompression of more data, as the buffer is not full.
	if(adx[target_adx].status & ADX_STATUS_START)
	{
		//sh2Com->adx_stream_comm = ('S' | ('T'<<8));
		//Decompress (decomp_demand) # of bytes to (dst)
		//Then start playing the sound
		for(short i = 0; i < adx[target_adx].decomp_demand; )
		{
			decompress_adx_frame(&adx[target_adx]);
			i += 64;
			adx[target_adx].current_frame += 1;
		}
		adx[target_adx].work_decomp_pt += adx[target_adx].decomp_demand;
		//ADX dummy 1 being a looping PCM control set to point at the adx work buf.
		pcmCtrlData[adx_dummy[target_adx]].playsize = (adx[target_adx].decomp_space)>>1;
		pcmCtrlData[adx_dummy[target_adx]].pitchword = snd->pitchword;
		pcmCtrlData[adx_dummy[target_adx]].bytes_per_blank = snd->bytes_per_blank;
		pcmCtrlData[adx_dummy[target_adx]].pan = snd->pan;
		pcmCtrlData[adx_dummy[target_adx]].volume = snd->volume;
		pcmCtrlData[adx_dummy[target_adx]].icsr_target = snd->icsr_target;
		pcmCtrlData[adx_dummy[target_adx]].loAddrBits = (unsigned short)((unsigned int)adx[target_adx].original_dst);
		set_looping_sound(adx_dummy[target_adx]);
		adx[target_adx].status ^= ADX_STATUS_START;
		adx[target_adx].status |= (ADX_STATUS_PLAY | ADX_STATUS_DECOMP);
	} else if(adx[target_adx].status & ADX_STATUS_DECOMP && !(adx[target_adx].status & ADX_STATUS_FULL))
	{
		///////////////////////////////////////
		// ADX Real-time Decompression
		// Very simple - an amount of ADX frames is decompressed every refresh cycle.
		// An ADX "frame" is 18 bytes which contains 64 4-bit nibbles and 1 16-bit scale value.
		// It should be noted, if it wasn't clear already, that your sound's byterate must be divisible by 64.
		// The amount of frames decompressed is the 60hz byterate of the raw PCM frequency, divided by 64, plus 1.
		for(short i = 0; i < adx[target_adx].decomp_demand; )
		{
			///////////////////////////////////////
			// ADX Decompression Completion Condition
			// The playsize of the ADX PCM control slot contains the # of ADX frames of the sound.
			// If the current frame being decompressed is greater than this, the sound has been fully decompressed.
			// The status is updated as such, and no more ADX frames are to be decompressed (there are no more!).
			if(adx[target_adx].current_frame > snd->playsize)
			{
				adx[target_adx].status |= ADX_STATUS_FULL;
				break;
			} 
			if(loop_type == ADX_STREAM && adx[target_adx].current_frame >= (ADX_STREAM_BUFFERED_FRAME_CT * adx[target_adx].passed_buffers))
			{
				sh2Com->adx_stream_comm = 0;
				adx[target_adx].passed_buffers++;
				adx[target_adx].src = adx[target_adx].original_src;
			}
			decompress_adx_frame(&adx[target_adx]);
			i += 64;
			adx[target_adx].current_frame += 1;
			sh2Com->adx_stream_comm += 1;
		}
		adx[target_adx].work_decomp_pt += adx[target_adx].decomp_demand;
	}

	if(adx[target_adx].status & ADX_STATUS_PLAY)
	{
		adx[target_adx].work_play_pt += snd->bytes_per_blank;
		///////////////////////////////////////
		// ADX Decompression Starting
		// If the play pointer has met or exceeded the recharge point,
		// this is the time we have have calculated as the appropriate time to begin decompression into the buffer.
		// We do start this now to maintain synchronization: It will finish before the SCSP gets back here after it loops,
		// and it will be done after the SCSP has looped.
		if(adx[target_adx].work_play_pt >= adx[target_adx].recharge_point && !(adx[target_adx].status & ADX_STATUS_FULL))
		{
			adx[target_adx].status |= ADX_STATUS_DECOMP;
		}
		///////////////////////////////////////
		// ADX Decompression Ending
		// If we have decompressed enough data to fill up the decompression buffer,
		// cease decompression and re-set the decompression target tracker and pointer.
		if(adx[target_adx].work_decomp_pt >= adx[target_adx].decomp_space)
		{
			adx[target_adx].status ^= ADX_STATUS_DECOMP;
			adx[target_adx].work_decomp_pt = 0;
			adx[target_adx].dst = adx[target_adx].original_dst;
		}
		///////////////////////////////////////
		// ADX Play Tracking
		// If the maximal position of the SCSP in the playback buffer will have met or exceeded the size of it,
		// we **know** the SCSP is going to go back to the beginning of the buffer.
		// We know this because the SCSP has been set to play back this region of sound as a loop.
		if(adx[target_adx].work_play_pt >= adx[target_adx].decomp_space)
		{
			adx[target_adx].work_play_pt = 0;
		}
		///////////////////////////////////////
		// ADX End Condition
		// When we have decompressed all the data from the ADX sound,
		// we have flagged the ADX status as FULL. The sound has been fully decompressed.
		// At this point, we shouldn't immediately end the sound. The decompression point is ahead of the playback point.
		// Thus, we want to end the sound only when the play point meets or passes the decompression point.
		if(adx[target_adx].work_play_pt >= adx[target_adx].work_decomp_pt && adx[target_adx].status & ADX_STATUS_FULL)
		{
			if(loop_type == PCM_FWD_LOOP)
			{
			//To set an ADX sound to loop, just.. restart it!
			//But you *do* have to end the sound slot, and there is a blanking period involved.
			adx[target_adx].status = (ADX_STATUS_START | ADX_STATUS_ACTIVE);
			adx[target_adx].current_frame = 0;
			adx[target_adx].src = (unsigned short *)((int)((snd->hiAddrBits<<16) | (snd->loAddrBits)));
			adx[target_adx].dst = adx[target_adx].original_dst;
			adx[target_adx].work_decomp_pt = 0;
			adx[target_adx].work_play_pt = 0;
			driver_end_sound(&snd->icsr_target, &pcmCtrlData[adx_dummy[target_adx]]);
			} else {
			adx[target_adx].status = ADX_STATUS_END;
			}
		}
	}

	///////////////////////////////////////
	// ADX Stop Condition
	// This is controlled by conditions above, and exactly what gets us here changes.
	// Control data from the ADX dummy, ADX PCM control, and ADX control struct is cleared.
	// In all cases, it is acceptable to indicate that the SH2 no longer permits the sound as looping conditions happen earlier.
	// However, it's not always needed.
	if(adx[target_adx].status & ADX_STATUS_END || loop_type == ADX_STATUS_NONE)
	{
		snd->sh2_permit = 0;
		for(short s = adx[target_adx].buf_string[0]; s <= adx[target_adx].buf_string[1]; s++)
		{
			adx_buffer_used[s] = 0;
		}
		adx[target_adx].status = ADX_STATUS_NONE;
		adx[target_adx].pcm_number = -1;
		adx[target_adx].passed_buffers = 0;
		driver_end_sound(&snd->icsr_target, &pcmCtrlData[adx_dummy[target_adx]]);
		driver_end_sound(&snd->icsr_target, snd);
	}

}

void	pcm_control_loop(void)
{
	icsr_index = 0;
	_PCM_CTRL * lctrl;

	short	loopingIndex = 0;
	short	adxIndex = 0;
	short	volatileIndex = 0;
	
	/*
	A new control loop for multiple ADX sounds is required.
	*/
	
	//////////////////////////////////////////////////
	// Build List of each type of basic control method
	for(short k = 0; k < PCM_CTRL_MAX; k++)
	{
		lctrl = &pcmCtrlData[k];
		if(lctrl->loopType == PCM_VOLATILE && lctrl->bitDepth != PCM_TYPE_ADX)
		{
			volatilePCMs[volatileIndex] = k;
			volatileIndex++;
		} else if(lctrl->loopType != PCM_VOLATILE && lctrl->bitDepth != PCM_TYPE_ADX)
		{
			loopingPCMs[loopingIndex] = k;
			loopingIndex++;
		} else if(lctrl->bitDepth == PCM_TYPE_ADX)
		{
			adxPCMs[adxIndex] = k;
			adxIndex++;
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
					if(!find_free_slot(lctrl)) break;
					set_looping_sound(loopingPCMs[l]); 
				} else {
					//Update the sound
					set_looping_sound(loopingPCMs[l]); 
				}
			} else if(lctrl->icsr_target != -1) //If the loop is not allowed by the SH2, and it is associated with an ICSR, it is active. Turn it off.
			{
					driver_end_sound(&lctrl->icsr_target, lctrl);
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
				//Attempt to grab a free ICSR. If there is none, function will return -1, and thus we will stop.
				if(!find_free_slot(lctrl)) break;
				play_protected_sound(loopingPCMs[l]); 
			} else {
				//Update the sound
				play_protected_sound(loopingPCMs[l]); 
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
				//Attempt to grab a free ICSR. If there is none, function will return -1, and thus we will stop.
				if(!find_free_slot(lctrl)) break;
				play_semi_protected_sound(loopingPCMs[l]); 
			} else if(lctrl->icsr_target != -1){ //Sound has an ICSR
				//Update the sound
				play_semi_protected_sound(loopingPCMs[l]); 
			}
		}
	//////////////////////////////
	//PCM Control Loop End Stub
	}
	
	//////////////////////////////////////////
	// ADX Control Loop
	for(short a = 0; a < adxIndex; a++)
	{
		
		lctrl = &pcmCtrlData[adxPCMs[a]];
		play_adx(adxPCMs[a], lctrl->loopType);
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	VOLATILE SOUND CONTROL SEGMENT
	//	Volatile sounds are essentially uncontrolled. They immediately write the SH2 no longer permits the sound after the first blank of playback.
	//	But they will still play to their conclusion, provided no other sound decides to occupy their ICSR.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for(short v = 0; v < volatileIndex; v++)
	{
		lctrl = &pcmCtrlData[volatilePCMs[v]];
		if(lctrl->sh2_permit == 1)
		{
		//Attempt to grab a free ICSR. If there is none, function will return -1, and thus we will stop.
			if(!find_free_slot(lctrl)) break;
			play_volatile_sound(lctrl);
		}
	}

}

void	_start(void)
{
	driver_data_init();
	while(1){
		//
		do{
			//sh2Com->adx_stream_comm = ('W' | ('A'<<8));
			if(sh2Com->start == 1) break;
		}while(1);
			sh2Com->start = 0;
		// Region will run the program once for every time the SH2 commands the driver to start.
		pcm_control_loop();
		

	}

}

