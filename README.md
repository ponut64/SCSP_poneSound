# 68k
SEGA Saturn SCSP Command & Control Driver and Linked Library
by Ponut64
Hitherto otherwise known as "ponèSound"

Currently supports playback of uncompressed 8-bit signed and 16-bit big-endian signed raw audio samples of up to 65536 samples in size. That would make 64KB the largest 8-bit raw size, and 128kb the largest 16-bit raw size.

Additionally supports real-time decompression and playback of ADX sound data by sound CPU from sound RAM. Three channels are supported, provided the bitrate of each channel is low enough. The available bitrates for use with ADX are 23040 Hz, 15360 Hz, 11520 Hz, and 7680 Hz. Only one bitrate can be properly decompressed by the Sound CPU at a time due to the need to build multiplication tables for ADX' advanced decompression method. That doesn't mean bitrates can't be mixed, it is just that quality is not guaranteed.
The channel allowance is as follows:
1 23040 Hz, 
1 15360 Hz + 1 7680 Hz, 
2 11520 Hz, 
1 1150Hz + 1 7680 Hz, 
3 7680 Hz 

The driver and linked library does not currently accomodate PCM streams nor does it provide abstractions for stereo playback.

The linked library is included in the jo_demo folder, which contains a readily compilable demo for the latest Jo Engine release.

Linker script from CyberWarriorX

Compiler from SGDK, GCC 6.3 - it has some bugs.
