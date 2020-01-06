
LDFILE = linker
srcs: main.c
	m68k-elf-gcc -o srcs main.c -Os -Wall -nodefaultlibs -nostdlib -mc68000 -mno-align-int -mno-strict-align -T linker
	m68k-elf-objcopy -O binary srcs sdrv.bin 