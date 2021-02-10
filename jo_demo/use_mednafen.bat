@ECHO Off

if exist game.iso (
"D:\games\med\mednafen.exe" game.cue
) else (
echo Please compile first !
)