@ECHO Off
SET EMULATOR_DIR=D:\Games\joengine-master\Emulators

if exist game.iso (
"%EMULATOR_DIR%\med\mednafen.exe" game.cue
) else (
echo Please compile first !
)