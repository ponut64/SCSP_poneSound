#
# IMPORTANT CRITICAL ACTUAL REAL GENUINE NOTICE!!!
# You can't use std libs or default libds. They unfortunately cause a crash that I don't understand.
# I suspect it has to do with the linker script.
#
LDFILE = linker
srcs: main.c
	m68k-elf-gcc -o srcs main.c -O2 -fno-use-linker-plugin -std=gnu99 -Wall -Wno-char-subscripts -nodefaultlibs -nostdlib -mc68000 -mno-align-int -mno-strict-align -T linker
	objcopy -O binary srcs sdrv.bin 