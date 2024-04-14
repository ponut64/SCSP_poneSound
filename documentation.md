//
// Documentation
//
//

What follows is a basic documentation of what/how Ponésound is.

////////////////////////////////////////////////////////////////////////
// *********************PLEASE READ THIS PART***************************
// IMPORTANT NOTES ABOUT PCM CHANNEL CONTROL
////////////////////////////////////////////////////////////////////////

Within the driver, there are four basic control types for PCM sound effects:
Volatile, Protected, Semi-protected, and looping.
Let us go through these types so that I may describe what their names mean and how they should be used.

1. Volatile, defined as:
#define PCM_VOLATILE	(0)
This should !!!NEVER!!! be used unless you KNOW WHAT YOU ARE DOING.
Volatile sounds have **NO CHANNEL MANAGEMENT!**. For this reason, ADX sounds cannot be played as volatile.
A volatile sound will find the first unprotected channel and select it for playback of the sound.
It will not protect the channel nor will the driver remember that channel as being used for anything.
This play type remains in the driver in case the user wishes to do manual channel management.
I remind you: THIS SHOULD NEVER BE USED unless you want the driver to do nothing with a sound except play it.

2. Protected, defined as:
#define PCM_PROTECTED	(-1)
With this type, the first free channel will be found and playback for this sound will start.
This is a channel control type which will protect the channel the sound is playing back in.
It will also protect the channel from play commands from the SH2.
That means a sound played back as `PCM_PROTECTED` will not stop or restart unless finished or commanded to stop.

3. Semi-protected, defined as:
#define PCM_SEMI		(-2)
With this type, the first free channel will be found and playback for this sound will start.
This channel control type also protects the channel that the sound is playing back in.
However, it will not protect the slot from play commands from SH2, such that another play command will immediately restart it.
That means a sound played back as `PCM_SEMI` will start or restart when commanded to play, and stop when commanded to.

4. Looping, defined with various types:
#define	PCM_ALT_LOOP	(3)

#define PCM_RVS_LOOP	(2)

#define PCM_FWD_LOOP	(1)

All of these types are technically variants of `PCM_PROTECTED`, except they command the SCSP to perform one of three types of loop.
With `PCM_RVS_LOOP`, the sound will loop backwards. With `PCM_FWD_LOOP`, the sound will loop forwards.
With `PCM_ALT_LOOP`, the sound will alternate between looping backwards and forwards.
These are just hardware features that I decided to support; I've no idea why you'd want anything but `PCM_FWD_LOOP`.
Only `PCM_FWD_LOOP` applies to ADX sounds (and it's a sketchy implementation at that).

5. ADX Streams, defined as:
#define ADX_STREAM		(-3)
Ignore this one. The linked library `pcmstm.c/h` uses it to communicate to the driver that an ADX sound will use a ring buffer.
It does not have any other purpose.

////////////////////////////////////////////////////////////////////////
// Notes about the ADX implementation

The ADX playback is *very strictly* limited to the following rates:
7680	Hz (NTSC) | 6400	Hz (PAL)		for up to 3 channels
11520	Hz (NTSC) | 9600	Hz (PAL)		for up to 2 channels
15360	Hz (NTSC) | 12800	Hz (PAL)		for 1 channel
23040	Hz (NTSC) | 19200	Hz (PAL)		*(only in cases of low sound system activity)

You can find more detail about bitrates in comments inside the driver source code itself.
The ADX decompression is implemented on the driver-side, aka, the M68k is performing the decompression.

It is doing so poorly; with shortcuts and tables abound. These compromise quality. 
I'll just put in that brief statement so you know that ADX doesn't normally sound this bad.

Another note is that the driver requires an ADX Master frequency to start.
You supply this when you load the driver.
They are defined as:
#define ADX_MASTER_768 (0)
#define ADX_MASTER_1152 (1)
#define ADX_MASTER_1536 (2)
#define ADX_MASTER_2304 (3)
For PAL, it is defined as:
#define ADX_PAL_640 (4)
#define ADX_PAL_960 (5)
#define ADX_PAL_1280 (6)
#define ADX_PAL_1920 (7)

The reason a master frequency is required is because the driver builds decompression tables based on this frequency.
You can play back sounds that don't match the master frequency, but they will not sound right.

///////////////////////////////////////////////////////////////
// Wait a minute, why are the PAL rates lower, or different at all?

This is a software-timed driver that is timed on vblank.
All of the channel timers are timed based on the bytes that each bitrate consumes per vblank.
For NTSC, this is 1/60th of a second, or about 16.6ms. For PAL, this is 1/50th of a second, or about 20ms.
You can see then that NTSC screens refresh *faster* and therefore more data is consumed per vblank.
That means the bitrate can be higher.

The reality is that the PAL system does have more time between vblanks to decompress the data for the next vblank,
so hypothetically, the PAL driver should be able to operate more channels simultaneously.
Unfortunately, I just don't care enough to tell you if it really can or not.
None of the streaming systems are guaranteed to work in PAL either.

///////////////////////////////////////////////////////////////
// Wait a minute, I commanded a sound to play twice but it's still only on one channel. What gives?!

The driver does not instance sound effects for you; you must do that on your own.
It only manages the channels for the sounds as listed in `m68k_com->pcmCtrl`.
In order to instance a sound effect, you must copy the contents of the `pcmCtrl` entry (what is returned from loading the sound)
into `m68k_com->pcmCtrl[numberPCMs]` entry, then perform `numberPCMs++`.
The driver should be able to handle out-of-order instancing (e.g. setting aside certain entries for instancing).

// But why don't you do that for me? It seems like an obvious feature...

The 68k's subsystem has the discrete potential to be heavily bottlenecked on memory bandwidth.
The way the driver is currently designed to work, sound instancing would make the 68k responsible for more data management.
Because of the performance concern, sound instancing should not be performed "on the fly";
instances should be managed after they are loaded, but before they are played, for ideal performance.
This is especially true in the case where ADX and/or sound streaming is being used.

How much more frustrated would you be with me if loading a sound also required an instance number argument?
And playing a sound required not only a sound number, but an instance number?

Also, I didn't need it, so I didn't add it. :)

///////////////////////////////////////////////////////////////
//
//	DRIVER WORK-FLOW
//
///////////////////////////////////////////////////////////////

The core of ponésound is the code that runs on the 68K inside of the Sega Saturn.
This code will hitherto be referred to as "the binary", or "the driver".

The driver is designed to operate on a vblank cycle. If you did not know, "vblank" is short for "Vertical Blank In Interrupt". It will also work on blank OUT. This is unlike most sound control software, which tends to run on-demand or by hardware timed registers. The driver also does not control this timing; it does not have any guarantee, limit, stop or overrun management despite it being designed to operate specifically on a vblank timing. The driver relies on the SH2, and thus the linked library, in order to function on this timing. So while the core is the binary, the linked library that your project must incorporate is also 100% essential to the function of the driver. The simple result of timing the driver's operation based on vblank is that, assuming the driver never runs for more than vblank interval (the time from one vblank to the next), the driver will always be able to start operation assuming a consistent amount of time has passed. For NTSC, this is 1/60th of a second, and for PAL, it is 1/50th of a second.

The reason that the linked library is needed for the driver to operate based on vblank is because the 68K cannot access the CD system to load its own binary, and it cannot access the relevant SCU registers in order to write its own interrupt state. In fact, the linked library itself does not register any interrupts for the 68K or SCSP, either between each other or the SCU. When the driver has gone through its work-flow, it will end in a loop, waiting for the CPUs to write a 1 (literal 1) where the driver will write a 0 (literal 0) after starting its work. If that is done at vblank, the correct work-flow interval for the driver will be achieved. 

This is done by the following line of code:

```m68k_com->start = 1;``` on the CPU side, and immediately thereafter, the driver will start its work-flow.
It will also immediately write back:
```sh2Com->start = 0;```

The area where this data is written to is extremely important to coordinate. After all, the binary is NOT cross-compiled with your project's code. This means the driver does NOT synchronize objects or addresses with your project at compile time. The driver binary is compiled separately. As such, the location of communication data between the driver and the CPUs is at a fixed, mutually agreed upon location in sound RAM. This data is housed in a struct. This is also a mutually agreed upon struct; if you change the contents/layout of this struct in the linked library (pcmsys.h), you must also change it in the driver source code, recompile it, then copy over the new binary to your CD directory. This work-flow is a consequence of not being cross-compiled. The benefit of not being cross-compiled is that you don't have to set up a another cross-compiler and linker script, and you also don't have to suffer the consequences upon the compiler and optimization flags between two different architectures.

The mutually-agreed upon location of the communication struct is established by the following lines, mirrored in the linked library (pcmsys.h) and the driver source code:
```#define DRV_SYS_END  (47 * 1024) // System defined safe end of driver's address space```
On the driver's side (marked as SH2 Com because the driver uses this to communicate with the SH2):
```volatile sysComPara *sh2Com = (volatile sysComPara *) (ADDR_PRG + DRV_SYS_END);```
On the SH2's side, marked as M68K Com, because ditto:
```sysComPara * m68k_com = (sysComPara *)((SNDPRG + DRV_SYS_END) | 0x20000000);```
Note the type difference. Doesn't mean anything to me, it just ended up working that way.

The `ADDR_PRG` and `SNDPRG` labels are ambiguous mirrors; I should fix that.
These refer to the same concept: On the Saturn's M68K, the first 1KB of addressable memory in sound RAM is reserved as an interrupt vector table. Why it has 1kb of that is strange to me, but I suppose each instrument in sequenced music could reserve an interrupt? No idea, it's probably just a standard part of an M68K's operation, or something.
Anyway, these labels both equate to the start of sound RAM plus `0x408`, or 1032 bytes. Why that, and not 1024 ? Well, 1032 didn't crash. Soo...

The communication struct at those addresses is as follows:
```
typedef struct {
  volatile unsigned int adx_stream_length; // Length of the ADX stream (in ADX frames)
  volatile unsigned short start;           // System Start Boolean
  volatile char adx_buffer_pass[2];        // Booleans
  volatile short drv_adx_coef_1;           // The (signed!) coefficient 1 the driver will
                                           // use to build ADX multiplication tables.
  volatile short drv_adx_coef_2;           // The (signed!) coefficient 2 the driver will
                                           // use to build ADX multiplication tables.
  volatile _PCM_CTRL *pcmCtrl;
  volatile unsigned char cdda_left_channel_vol_pan;  // Redbook left channel volume & pan.
  volatile unsigned char cdda_right_channel_vol_pan; // Redbook right channel volume & pan.
} sysComPara;
```
The most important member of this communication struct, aside from `start`, is the `pcmCtrl` pointer.
This is an SH2-mapped pointer to the list of sounds registered with the driver.
Note the driver does not use this pointer; only the linked library (SH2) does.
The driver addresses this data as an array, not a pointer.

This struct has two elements which are only communicated on first boot of the driver, that being the ADX coefficients.
The way the ADX coefficients affect the ADX playback will be covered in a different part of the documentation.

Most of the real-time communication data that the driver and CPU bounce back and forth are data which deals with streaming audio.
With regards to non-streaming audio, the master CPU does not do a whole lot with the sound. It generally just writes to play the sound, and the driver decides what to do based on the configuration of the sound. With streaming audio however, the driver must communicate back to the CPU the state of playback.

When the driver is started for the first time, the 68K's program counter will be at the previously mentioned address: `0x408`
To jump the program counter to the appropriate point in the code, the binary is front-loaded at this address with a jump instruction to send it to the main program management loop. That loop is at the `_start` label. Note this is not normal C `main`, because the driver is not built with a normal C linker script. I got it from CyberWarriorX and that's what it does.

```
void lead_function(void) // Link start to main
{
  // note that _start is the ASM label that equates to
  // the lead function in this compiler. In a normal
  // compiler, it would be "main".
  __asm__("jmp _start");
}
```

The start function leads with the driver boot functions before proceeding to the main loop which will capture the program counter. This boot function is called `driver_data_init`.
In this function, the driver will clean the sound slot registers, set pointers for the SH2, set up the CDDA channels, initialize the PCM control system, build the ADX multiplication tables and control data. Of special note is that the ADX tables will take a lot of time to finish building. Users should be aware that the driver needs time to do this before it is ready to play sound.

Past this, the work-flow of the driver will "proceed as normal" through checking the status of each member of the PCM_CTRL struct. The function which does this is aptly named `pcm_control_loop`. After that, the CD-DA volume is managed (so you can change it at any time).

This concludes the general work-flow of the driver itself. If you want more detail, the source code is public.
You will note this section did not cover much of anything regarding the linked library, which is needed to use the driver.
That is for the following section.

////////////////////////////////////////////////////////////////////////
//
// LIBRARY WORK-FLOW
//
////////////////////////////////////////////////////////////////////////



//// 
// Notes
////



