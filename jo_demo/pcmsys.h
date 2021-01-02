//
//pcmsys.h
//
#ifndef __PCMSYS_H__
# define __PCMSYS_H__
//////////////////////////////////////////////////////////////////////////////

#define SMPC_REG_IREG(i)        *((volatile unsigned char *)0x20100001+((i) * 2))
#define SMPC_REG_COMREG         *((volatile unsigned char *)0x2010001F)
#define SMPC_REG_OREG(o)        *((volatile unsigned char *)0x20100021+((o) * 2))
#define SMPC_REG_SR             *((volatile unsigned char *)0x20100061)
#define SMPC_REG_SF             *((volatile unsigned char *)0x20100063)
#define SMPC_REG_PDR1           *((volatile unsigned char *)0x20100075)
#define SMPC_REG_PDR2           *((volatile unsigned char *)0x20100077)
#define SMPC_REG_DDR1           *((volatile unsigned char *)0x20100079)
#define SMPC_REG_DDR2           *((volatile unsigned char *)0x2010007B)
#define SMPC_REG_IOSEL          *((volatile unsigned char *)0x2010007D)
#define SMPC_REG_EXLE           *((volatile unsigned char *)0x2010007F)

//////////////////////////////////////////////////////////////////////////////

#define SMPC_CMD_MSHON				0x00
#define SMPC_CMD_SSHON				0x02
#define SMPC_CMD_SSHOFF				0x03
#define SMPC_CMD_SNDON				0x06
#define SMPC_CMD_SNDOFF				0x07
#define SMPC_CMD_CDON				0x08
#define SMPC_CMD_CDOFF				0x09
#define SMPC_CMD_CARTON				0x0A
#define SMPC_CMD_CARTOFF			0x0B
#define SMPC_CMD_SYSRES				0x0D
#define SMPC_CMD_CKCHG352			0x0E
#define SMPC_CMD_CKCHG320			0x0F
#define SMPC_CMD_INTBACK			0x10
#define SMPC_CMD_SETTIM				0x16
#define SMPC_CMD_SETSM				0x17
#define SMPC_CMD_NMIREQ				0x18
#define SMPC_CMD_RESENA				0x19
#define SMPC_CMD_RESDIS				0x1A

//////////////////////////////////////////////////////////////////////////////
//Address mapping shorthand
#define MAP_TO_SCSP(sh2map_snd_adr) ((sh2map_snd_adr - SNDRAM))
//////////////////////////////////////////////////////////////////////////////
//No Touchy Sound Ram Start!
#define SNDRAM  (631242752)
// 1KB here is reserved for interrupts
#define SNDPRG (SNDRAM + 0x408)
//Also the end of sound RAM
#define PCMEND	(SNDRAM + 0x7F000)
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
#define	PCM_ALT_LOOP	(3)
#define PCM_RVS_LOOP	(2)
#define PCM_FWD_LOOP	(1)
#define PCM_VOLATILE	(0)
#define PCM_PROTECTED	(-1)
#define PCM_SEMI		(-2)
//////////////////////////////////////////////////////////////////////////////
#define PCM_SYS_REGION	(0) //0 for NTSC, 1 for PAL
//////////////////////////////////////////////////////////////////////////////
#define PCM_PAN_LEFT	(0x1F)	//It is 5-bit data. The MSB being high will reduce the right channel's volume (pan left).
#define PCM_PAN_RIGHT	(0xF)	//If the MSB is low, it will reduce the left channel's volume (pan right).
//////////////////////////////////////////////////////////////////////////////

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
	short intback; //If non-zero, will fire sound interrupt on protected sound end and write PCM # to intlast.
	char icsr_target; //Which explicit ICSR is this to land in? Can be controlled by SH2 or by driver.
} _PCM_CTRL; //Driver Local Command Struct

typedef struct{
	unsigned short start; //System Start Boolean
	unsigned short dT_ms; //delta time supplied by SH2 in miliseconds 
	//Alignment warning: Is pointer, must be on 4-byte boundary.
	_PCM_CTRL * pcmCtrl;
	//
	unsigned short intlast; //Will recieve the PCM # of the sound which last fired an interrupt
	short intcom; //Semi-protected playback directive slot; intended to be written to by SH2 after a sound sys interrupt.
} sysComPara;

	/*
INTEGER	|---MSB--------------------------------------------------------------------------------------------------------------------LSB--|
	BIT	|	15	|	14	|	13	|	12	|	11	|	10	|	9	|	8	|	7	|	6	|	5	|	4	|	3	|	2	|	1	|	0	|
		|-------------------------------------------------------------------------------------------------------------------------------|
SOUND	|		
ENABLE	|	0	|	0	|	0	|	0	|	0	|	R/W	|	R/W	|	R/W	|	R/W	|	R/W	|	R/W	|	R/W	|	R/W	|	R/W	|	R/W	|	R/W	|
PENDING	|	0	|	0	|	0	|	0	|	0	|	R	|	R	|	R	|	R	|	R	|	R/W	|	R	|	R	|	R	|	R	|	R	|
RESET	|	0	|	0	|	0	|	0	|	0	|	W	|	W	|	W	|	W	|	W	|	W	|	W	|	W	|	W	|	W	|	W	|
		|	0	|	0	|	0	|	0	|	0	|	1FS	|MIDOUT	|TimerC	|TimerA	|TimerB	|CPU/SCU|	DMA	|MIDIIN	|Extern	|Extern	|Extern	|
SCU		|
ENABLE	|	0	|	0	|	0	|	0	|	0	|	W	|	W	|	W	|	W	|	W	|	W	|	W	|	W	|	W	|	W	|	W	|
PENDING	|	0	|	0	|	0	|	0	|	0	|	R	|	R	|	R	|	R	|	R	|	R/W	|	R	|	R	|	R	|	R	|	R	|
RESET	|	0	|	0	|	0	|	0	|	0	|	W	|	W	|	W	|	W	|	W	|	W	|	W	|	W	|	W	|	W	|	W	|
	*/


//
extern unsigned short * sound_cpu_interrupt_enable;
extern unsigned short * sound_cpu_interrupt_pending;
extern unsigned short * sound_cpu_interrupt_reset;
	
//
extern unsigned short * sound_sys_scu_interrupt_enable;
extern unsigned short * sound_sys_scu_interrupt_pending;
extern unsigned short * sound_sys_scu_interrupt_reset;
//

//
extern	sysComPara * m68k_com;
extern	unsigned int * scsp_load;
extern unsigned short * master_volume;
extern short numberPCMs;
//

void	smpc_wait_till_ready(void);
void	smpc_issue_command(unsigned char cmd);
short	load_16bit_pcm(Sint8 * filename, int sampleRate);
short	load_8bit_pcm(Sint8 * filename, int sampleRate);
void	load_drv(void);

void	pcm_play(short pcmNumber, char ctrlType, char volume, char interrupt_when_done);
void	pcm_parameter_change(short pcmNumber, char volume, char pan);
void	pcm_cease(short pcmNumber);

#endif

