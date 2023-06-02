//
// Documentation
//
//

What follows is a basic documentation of what/how Ponésound is.

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



