@ECHO Off
SET EMULATOR_DIR=..\..\Emulators

if exist sl_coff.iso (
"%EMULATOR_DIR%\med\mednafen.exe" sl_coff.cue
) else (
echo Please compile first !
)