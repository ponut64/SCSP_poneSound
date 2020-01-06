SET COMPILER_DIR=..\m68k-elf\bin
SET PATH=%COMPILER_DIR%;%cd%
make -f makefile srcs
PAUSE