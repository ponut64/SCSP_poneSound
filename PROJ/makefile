
LDFILE = linker
srcs: main.c
	gcc -o srcs main.c -Os -fno-use-linker-plugin -std=gnu99 -Wall -Wno-char-subscripts -nodefaultlibs -nostdlib -mc68000 -mno-align-int -mno-strict-align -T linker
	objcopy -O binary srcs sdrv.bin 