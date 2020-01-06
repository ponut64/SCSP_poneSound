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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*		
		GLOASSARY OF TERMS:
			KX : EXECUTE KEY [select] [Start or stop the sound] [Reset to 0 by system]
			KB : Key ON or Key OFF select [0 is OFF, 1 is ON]
			SBCTL : Source bit control [???]
			SSCTL : Source type control [0: PCM, 1: Noise Generator, 2: Waveform generator, 3: Illegal] - Pertains to LFO registers in 1&2
			LPCTL : loop control [0: Sound ends when LEA is reached, 1: normal loop, 2: reverse loop, 3: alternating loop]
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
			RE : LFO Reset [???] - lFO pertains to the sound generator, both FM and waveform [not PCM though]
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
6		|													LOOP END ADDRESS	[LEA] 15-0												| loop_end
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
	unsigned short	loop_end;
	unsigned short	decay_1_2_attack;
	unsigned short	key_decay_release;
	unsigned short	attenuation;
	unsigned short	FM_data; //Should leave 0 for PCM
	unsigned short	oct_fns;
	unsigned short	lfo_data; //Should leave 0 for PCM
	unsigned short	input_sel; //Should leave 0 for PCM
	unsigned short	pan_send;
	unsigned short	blanks[4];
} _ICSR;

typedef struct{
	unsigned short start; //System Start Boolean
	unsigned short dT_ms; //delta time supplied by SH2 in miliseconds 
	unsigned short hiTDatPtr; //Test data pointer
	unsigned short lowTDatPtr;
} sysComPara;

//Warning: Do not alter the master volume register from within the 68k program.
//It's legal, but dangerous.
volatile sysComPara * sh2Com = (volatile sysComPara  *)(ADDR_PRG + 0x10000);
volatile _ICSR * csr = (volatile _ICSR *)0x100000; //There are 32 of these.

void	play_test_sound(void)
{
	csr[0].keys = (1<<11 | 1<<5 | sh2Com->hiTDatPtr); //Key select ON | Normal loop | high bits of address
	csr[0].start_addr = sh2Com->lowTDatPtr;

	csr[0].loop_end = 0xFFFF;
	
	csr[0].decay_1_2_attack = 31;
	csr[0].key_decay_release = 31;
	
	csr[0].attenuation = 1<<9; //Set direct output with no attentuation
	
	csr[0].oct_fns = 29074;
	
	csr[0].pan_send = 6<<13;
	
	csr[0].keys |= 1<<12; //KEY ON '' Due to the multi-cycle instruction nature of the M68K, and the limited RAM access,
						//KEY EXECUTE must be written last.
}

void	_start(void)
{
	while(1){
		//
		do{
			if(sh2Com->start != 0) break;
		}while(1);
			sh2Com->start = 0;
		// Region will run the program once for every time the SH2 commands the driver to start.
		play_test_sound();
	}
}

