# 68k
SEGA Saturn SCSP Command & Control Driver and Linked Library
by Ponut64
Hitherto otherwise known as "ponèSound"

Currently supports playback of uncompressed 8-bit signed and 16-bit big-endian signed raw audio samples of up to 65536 samples in size. That would make 64KB the largest 8-bit raw size, and 128kb the largest 16-bit raw size.

Additionally supports real-time decompression and playback of ADX sound data by sound CPU from sound RAM. Three channels are supported, provided the bitrate of each channel is low enough. The available bitrates for use with ADX are 23040 Hz, 15360 Hz, 11520 Hz, and 7680 Hz. Only one bitrate can be properly decompressed by the Sound CPU at a time due to the need to build multiplication tables for ADX' advanced decompression method. That doesn't mean bitrates can't be mixed, it is just that quality is not guaranteed.
The channel allowance is as follows:
1 23040 Hz, 
1 15360 Hz + 1 "Ultra Low" Hz, 
2 11520 Hz, 
1 11520Hz + 1 "Ultra Low" Hz, 
3 "Ultra Low" Hz 
"Ultra Low Hz" being interchangable with 7680 Hz, 5760 Hz, and 3840 Hz

The driver has two linked libraries.
Primarily there is pcmsys.c and pcmsys.h ; these are the files needed for general sound playback.
Additionally, there is pcmstm.c and pcmstm.h ; these are the files needed for streaming audio.
With pcmstm.c, one channel of PCM can be streamed at up to 30720, mono, 8-bit with an ADX stream.
The ADX stream can be up to 23040, mono. 
It's important to note that due to the low buffer size, the ADX stream starts playback quickly.
It therefore carries some relevance for use in general sound design (like, for voice lines).
However, the raw PCM stream takes significant time to buffer.

It should be noted that CD-DA makes much better use of CD bandwidth for music. 
The downside is that CD-DA tracks are big, and inflexible in size.
CD-DA also locks access to the CD drive when active; it takes 100% of the bandwidth.

There are two seprate usage demos:
jo_demo, which is for the general-basic functions in pcmsys.c/h.
jo_stream_demo, which is a demonstration of the streaming libraries.

Linker script from CyberWarriorX

Compiler was dug up from the internet.
