//
//pcmsys.h
//
#ifndef __PCMSYS_H__
# define __PCMSYS_H__

///////////////
// Likely duplicates from other libraries (in this case, taken from iapetus)
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
#define DRV_SYS_END (47 * 1024) //System defined safe end of driver's address space
#define PCM_CTRL_MAX (64)
//////////////////////////////////////////////////////////////////////////////
#define	PCM_ALT_LOOP	(3)
#define PCM_RVS_LOOP	(2)
#define PCM_FWD_LOOP	(1)
#define PCM_VOLATILE	(0)
#define PCM_PROTECTED	(-1)
#define PCM_SEMI		(-2)
#define ADX_STREAM		(-3)
//////////////////////////////////////////////////////////////////////////////
#define PCM_TYPE_ADX (2) // 4-bit (compressed audio)
#define PCM_TYPE_8BIT (1) // 8-bit
#define PCM_TYPE_16BIT (0) // 16-bit
//////////////////////////////////////////////////////////////////////////////
#define PCM_SYS_REGION	(0) //0 for NTSC, 1 for PAL
//////////////////////////////////////////////////////////////////////////////
#define PCM_PAN_LEFT	(1<<4)
#define PCM_PAN_RIGHT	(0)
//////////////////////////////////////////////////////////////////////////////
#define ADX_MASTER_768 (0)
#define ADX_MASTER_1152 (1)
#define ADX_MASTER_1536 (2)
#define ADX_MASTER_2304 (3)
/* 7.68 Data */
#define ADX_768_COEF_1 (4401)
#define ADX_768_COEF_2 (-1183)
/* 11.52 data */
#define ADX_1152_COEF_1 (5386)
#define ADX_1152_COEF_2 (-1771)
/* 15.36 data */
#define ADX_1536_COEF_1 (5972)
#define ADX_1536_COEF_2 (-2187)
/* 23.04 data */
#define ADX_2304_COEF_1 (6631)
#define ADX_2304_COEF_2 (-2685)

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
	volatile unsigned int adx_stream_length; //Length of the ADX stream (in ADX frames)
	volatile unsigned short start; //System Start Boolean
	volatile char	adx_buffer_pass[2]; //Booleans
	volatile short drv_adx_coef_1; //The (signed!) coefficient 1 the driver will use to build ADX multiplication tables.
	volatile short drv_adx_coef_2; //The (signed!) coefficient 2 the driver will use to build ADX multiplication tables.
	volatile _PCM_CTRL * pcmCtrl;
	volatile short cdda_volume; // Redbook audio volume. 3-bit value, 13 most significant bits are ignored
} sysComPara;


typedef struct {
	unsigned short one_half; //[this is 32768 or 0x8000]
	short offset2data;
	unsigned char format; //[this is 3]
	unsigned char block_size; //[this is 18]
	unsigned char bit_depth; //[this is 4]
	unsigned char channels; //[this should be 1]
	unsigned int sample_rate;
	unsigned int sample_ct;
	unsigned short hp_cutoff; //[this should be 500]
	unsigned char loop;
	unsigned char illegal; //[boolean, 0 for false, 1 for true]
} adx_header;

//

//
extern	sysComPara * m68k_com;
extern	unsigned int * scsp_load;
extern unsigned short * master_volume;
extern short numberPCMs;

//
// System functions shared for pcmstm.c/h
//
short			convert_bitrate_to_pitchword(short sampleRate);
short			calculate_bytes_per_blank(int sampleRate, bool is8Bit, bool isPAL);
short 			lcm(short a, short b);
void			cd_init(void);

//
// These are likely to be duplicate commands from other libraries.
//
void	smpc_wait_till_ready(void);
void	smpc_issue_command(unsigned char cmd);
//
//
//

short	load_16bit_pcm(Sint8 * filename, int sampleRate);
short	load_8bit_pcm(Sint8 * filename, int sampleRate);
short	load_adx(Sint8 * filename);
void	load_drv(int master_adx_frequency);

void	pcm_play(short pcmNumber, char ctrlType, char volume);
void	pcm_parameter_change(short pcmNumber, char volume, char pan);
void	pcm_cease(short pcmNumber);

void	sdrv_vblank_rq(void);

//
// Redbook support
// Credit: ndiddy, ReyeMe, CyberWarriorX [Iapetus]
//

void CDDASetVolume(int vol);
void CDDAPlay(int fromTrack, int toTrack, bool loop);
void CDDAPlaySingle(int track, bool loop);
void CDDAStop(void);


#endif

