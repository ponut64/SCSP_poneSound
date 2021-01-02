//Driver main.c
#define ADDR_PRG (0x408)
#define ADDR_MAX (0x7F000)
#define ADDR_STACK (0x80000 - 0x400)
#define ADDR_END (0x80000)

void _start();

//Big credit to cWx :: cyberWarriorX for a sound driver prototype and most importatly, the linker script!
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int * vecTable[256] __attribute__ ((section ("VECTORS"))) =
{
(int*)ADDR_STACK, (int*)_start, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END, (int*)ADDR_END,
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Place all includes past this line
#define PCM_CTRL_MAX (128)
#define DRV_SYS_END (10 * 1024) //System defined safe end of driver's address space
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*		
		GLOASSARY OF TERMS:
			KX : EXECUTE KEY [select] [Start or stop the sound] [Reset to 0 by system]
			KB : Key ON or Key OFF select [0 is OFF, 1 is ON]
			SBCTL : Source bit control [???]
			SSCTL : Source type control [0: PCM, 1: Internal noise generator (LFO/FM) NOISE, 2: Internal noise generator (LFO/FM) NO NOISE, 3: Illegal] 
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
			RE : LFO Reset [???] - lFO reset LOW will start LFO, LFO reset HIGH .. appears to just turn it off?
			LFOF : Low-frequency oscillator frequency selection
			PLFOWS : Waveform type select for pitch oscillator 
			PLFOS : Modulation level of pitch
			ALFOWS : Waveform type select for amplitude oscillator
			ALFOS : Modulation level of amplitude (volume)
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
	unsigned char sh2_permit; //Does the SH2 permit this command? If TRUE, run the command. If FALSE, key its ICSR OFF.
	char icsr_target; //Which explicit ICSR is this to land in? Can be controlled by SH2 or by driver.
} _PCM_CTRL; //Driver Local Command Struct

typedef struct{
	unsigned short start; //System Start Boolean
	unsigned short dT_ms; //delta time supplied by SH2 in miliseconds 
	_PCM_CTRL * pcmCtrl;
} sysComPara;

//Warning: Do not alter the master volume register from within the 68k program.
//It's legal, but dangerous.
volatile sysComPara * sh2Com = (volatile sysComPara  *)(ADDR_PRG + DRV_SYS_END);
volatile _ICSR * csr = (volatile _ICSR *)0x100000; //There are 32 of these.
//
_PCM_CTRL	pcmCtrlData[PCM_CTRL_MAX];
char		ICSR_Busy[32];
char		icsr_index = 0;
short		loopingIndex = 0;
short		volatileIndex = 0;
short		loopingPCMs[PCM_CTRL_MAX];
short		volatilePCMs[PCM_CTRL_MAX];
int			dataTimers[32];

void	driver_data_init(void)
{
		sh2Com->pcmCtrl = (_PCM_CTRL *)((unsigned int)&pcmCtrlData[0] + 0x25A00000); //I'm so bad at C it took me an hour to realize I had to typecast this
			//Assignment is for the SH2, so it adds the SNDRAM base uncached address.
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
	
	//Set max master volume (0-15 volume levels valid).
	unsigned short * master_volume = (unsigned short *)0x100400;
	*master_volume |= 15;

}

/*
NOTICE: To play the same sound struct multiple times per frame (why?) you have to copy its PCM_CTRL struct into another array member, and issue it to play.
*/

/*
This function is for non-looping sounds that will restart every time the driver detects sh2 permit. In other words, it is "volatile".
This is a volatile playback function, meaning the sound is stopped and played back again from the start when this is triggered.
The trigger is "sh2_permit", as written by the SH2, expectedly.
To use this wisely, either limit sound trigger by a timer, or simply ensure the routine that has sound playback attached to it has some statute of limitations.
Bonus: You could attach volatile playback to an sh2 function to *know* if its happening more than it should :)
*/
void	play_volatile_sound(_PCM_CTRL * lctrl)
{

	char cst = lctrl->icsr_target;
	csr[cst].keys = (0); //Key select OFF
	csr[cst].keys |= 1<<12; //Key EXECUTE OFF
	
	csr[cst].keys = (1<<11 | lctrl->bitDepth<<4 | lctrl->hiAddrBits); 
	//Key select ON | Bit depth | high bits of address
	csr[cst].start_addr = lctrl->loAddrBits;
	csr[cst].loop_start = lctrl->LSA;
	csr[cst].playsize = lctrl->playsize;
	csr[cst].oct_fns = lctrl->pitchword; //It would be possible to include a pseudorandom table to randomize the pitch slightly.
										//The octave is in this word, so that's what you would change for randomized pitch. +1 or -1.
	csr[cst].pan_send = ((lctrl->volume<<13) | (lctrl->pan<<8));
	
	csr[cst].decay_1_2_attack = 31;		//We could skip writing these and specify direct data playback,
	csr[cst].key_decay_release = 31;	//but as far as I understand, this removes sound panning. Attenuation, bit 9 [SD].
	
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
	char cst = lctrl->icsr_target;
		if(ICSR_Busy[cst] != index){ //This ICSR is not presently associated with the protected sound, so we set it up.
	dataTimers[cst] = 0; //Clear playback timer
	csr[cst].keys = (0); //Key select OFF
	csr[cst].keys |= 1<<12; //Key EXECUTE OFF

		
	csr[cst].keys = (1<<11  | lctrl->bitDepth<<4 | lctrl->hiAddrBits); 
	//Key select ON | LFO use | Bit depth | high bits of address
	csr[cst].start_addr = lctrl->loAddrBits;
	csr[cst].loop_start = lctrl->LSA;
	csr[cst].playsize = lctrl->playsize;
	csr[cst].oct_fns = lctrl->pitchword;
	csr[cst].pan_send = ((lctrl->volume<<13) | (lctrl->pan<<8));
	
	csr[cst].decay_1_2_attack = 31;		//We could skip writing these and specify direct data playback,
	csr[cst].key_decay_release = 31;	//but as far as I understand, this removes sound panning. Attenuation, bit 9 [SD].
	
	csr[cst].keys |= 1<<12; //KEY EXECUTE must be written last.
									}
	
		if(dataTimers[cst] >= (lctrl->playsize<<(1 - lctrl->bitDepth)) ) //1 - bitDepth is an expression that will or will not multiply the playsize by 2,
		{																//depending on if it is 8 bits per sample or 16 bits per sample. Remember,
			csr[cst].keys = (0); //Key select OFF						//if the bits per sample is 16, the playsize >>=1 its data size.
			csr[cst].keys |= 1<<12; //Key EXECUTE OFF
			lctrl->sh2_permit = 0; //The SH2 has commanded a protected sound, and this signals that the protection period is over.	
			lctrl->icsr_target = -1;
			ICSR_Busy[cst] = -1; //Flag this ICSR as no longer busy
			dataTimers[cst] = 0; //Clear playback timer
		} else {
			ICSR_Busy[cst] = index;	//Associate this ICSR with this protected sound.
			dataTimers[cst] += lctrl->bytes_per_blank;
			
			csr[cst].oct_fns = lctrl->pitchword;							//Allow live volume and pitch adjustment of protected sounds
			csr[cst].pan_send = ((lctrl->volume<<13) | (lctrl->pan<<8));	//
		}
}

/*
This function is for playing non-looping sounds that will restart whenever the SH2 commands them to, however, the duration of playback locks an ICSR from other sounds.
*/
void	play_semi_protected_sound(short index)
{
	
	_PCM_CTRL * lctrl = &pcmCtrlData[index];
	char cst = lctrl->icsr_target;
		if(lctrl->sh2_permit == 1)
		{
	dataTimers[cst] = 0; //Clear playback timer
	csr[cst].keys = (0); //Key select OFF
	csr[cst].keys |= 1<<12; //Key EXECUTE OFF
	
	csr[cst].keys = (1<<11  | lctrl->bitDepth<<4 | lctrl->hiAddrBits); 
	//Key select ON | LFO use | Bit depth | high bits of address
	csr[cst].start_addr = lctrl->loAddrBits;
	csr[cst].loop_start = lctrl->LSA;
	csr[cst].playsize = lctrl->playsize;
	csr[cst].oct_fns = lctrl->pitchword; //It would be possible to include a pseudorandom table to randomize the pitch slightly.
										//The octave is in this word, so that's what you would change for randomized pitch. +1 or -1.
	csr[cst].pan_send = ((lctrl->volume<<13) | (lctrl->pan<<8));

	csr[cst].decay_1_2_attack = 31;		//We could skip writing these and specify direct data playback,
	csr[cst].key_decay_release = 31;	//but as far as I understand, this removes sound panning. Attenuation, bit 9 [SD].
	
	csr[cst].keys |= 1<<12; //KEY EXECUTE must be written last.
	lctrl->sh2_permit = 0; //Unhinge control struct
		}
		
		if(dataTimers[cst] >= (lctrl->playsize<<(1 - lctrl->bitDepth)) ) //1 - bitDepth is an expression that will or will not multiply the playsize by 2,
		{																//depending on if it is 8 bits per sample or 16 bits per sample. Remember,
			csr[cst].keys = (0); //Key select OFF						//if the bits per sample is 16, the playsize >>=1 its data size.
			csr[cst].keys |= 1<<12; //Key EXECUTE OFF
			lctrl->sh2_permit = 0; //The SH2 has commanded a protected sound, and this signals that the protection period is over.	
			lctrl->icsr_target = -1;
			ICSR_Busy[cst] = -1; //Flag this ICSR as no longer busy
			dataTimers[cst] = 0; //Clear playback timer
		} else {
			ICSR_Busy[cst] = index;	//Associate this ICSR with this protected sound.
			dataTimers[cst] += lctrl->bytes_per_blank;
			
			csr[cst].oct_fns = lctrl->pitchword;							//Allow live volume and pitch adjustment of protected sounds
			csr[cst].pan_send = ((lctrl->volume<<13) | (lctrl->pan<<8));	//
		}
		
		
}

/*
This function is for setting up or updating a sound with looping playback
*/
void	set_looping_sound(short index)
{
	_PCM_CTRL * lctrl = &pcmCtrlData[index];
	char cst = lctrl->icsr_target;

		if(ICSR_Busy[cst] != index){ //This ICSR is not presently associated with the looping sound, so we decimate its current playback.
	csr[cst].keys = (0); //Key select OFF
	csr[cst].keys |= 1<<12; //Key EXECUTE OFF
			}
	csr[cst].keys = (1<<11 | lctrl->loopType << 5 | lctrl->bitDepth<<4 | lctrl->hiAddrBits); 
	//Key select ON | loop type | LFO use | Bit depth | high bits of address
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

void	pcm_control_loop(void)
{
	icsr_index = 0;
	_PCM_CTRL * lctrl;

	loopingIndex = 0;
	volatileIndex = 0;
	
	//Loop to find the looping indexes
	for(short k = 0; k < PCM_CTRL_MAX; k++)
	{
		lctrl = &pcmCtrlData[k];
		if(lctrl->loopType == 0)
		{
			volatilePCMs[volatileIndex] = k;
			volatileIndex++;
		} else if(lctrl->loopType != 0)
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
					lctrl->icsr_target = icsr_index;
					set_looping_sound(loopingPCMs[l]); //Start the sound
					icsr_index++;
				} else {
					set_looping_sound(loopingPCMs[l]); //Update the sound
				}
			} else if(lctrl->icsr_target != -1) //If the loop is not allowed by the SH2, and it is associated with an ICSR, it is active. Turn it off.
			{
				csr[lctrl->icsr_target].keys = (0); //Key select OFF
				csr[lctrl->icsr_target].keys |= 1<<12; //Key EXECUTE OFF
				ICSR_Busy[lctrl->icsr_target] = -1; //Empty the association
				lctrl->icsr_target = -1;	//Empty the target
			}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//	PROTECTED SOUND CONTROL SEGMENT
		//	Protected sounds are expected to manage permission end by themselves.
		//	In this case, the SH2 is never to write 0 to SH2 Permit to stop a protected sound.
		//	To prematurely stop a protected sound, set its volume to zero and let the timer conclude.
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		} else if(lctrl->loopType == -1  && lctrl->sh2_permit == 1)//If normal protected sound, if permitted...
		{
			if(lctrl->icsr_target == -1)	//If first run (no current ICSR)
			{
		//
		while(ICSR_Busy[icsr_index] != -1)
		{
			icsr_index++; //Set forward the icsr_index until it has reached an inactive ICSR
		}
		if(icsr_index >= 32) break;
		//
				lctrl->icsr_target = icsr_index;
				play_protected_sound(loopingPCMs[l]); //Start a new protected sound
				icsr_index++;
			} else {						//If already running (has ICSR)
				play_protected_sound(loopingPCMs[l]); //Run updates on the protected sound
			}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//	SEMI-PROTECTED SOUND CONTROL SEGMENT
		//	Semi-protected sounds manage the SH2 permit parameter but will still run the timer to the release of the ICSR if they are not permitted.
		//	Permission 0 only disallows updates once the sound has started.
		//	Because of this, writing SH2 Permit to 0 on a semi-protected sound results in undefined behaviour.
		//	To stop a semi-protected sound, change the volume to 0 and let the timer conclude.
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		} else if(lctrl->loopType == -2) //If semi-protected sound...
		{
			if(lctrl->icsr_target == -1 && lctrl->sh2_permit == 1) //Sound does not currently occupy an ICSR
			{
		//
		while(ICSR_Busy[icsr_index] != -1)
		{
			icsr_index++; //Set forward the icsr_index until it has reached an inactive ICSR
		}
		if(icsr_index >= 32) break;
		//
				lctrl->icsr_target = icsr_index;
				play_semi_protected_sound(loopingPCMs[l]); //Start new
				icsr_index++;
			} else if(lctrl->icsr_target != -1) //Run the update if the semi-protected sound has an associated target.
			{
				play_semi_protected_sound(loopingPCMs[l]); //Update
			}
			
		}
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
			if(sh2Com->start != 0) break;
		}while(1);
			sh2Com->start = 0;
		// Region will run the program once for every time the SH2 commands the driver to start.
	
		pcm_control_loop();
	}
}

