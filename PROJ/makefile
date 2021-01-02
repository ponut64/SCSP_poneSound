
LDFILE = linker
srcs: main.c
	m68k-elf-gcc -o srcs main.c -Os -std=gnu99 -Wall -Wno-char-subscripts -nodefaultlibs -nostdlib -mc68000 -mno-align-int -mno-strict-align -T linker
	m68k-elf-objcopy -O binary srcs sdrv.bin 