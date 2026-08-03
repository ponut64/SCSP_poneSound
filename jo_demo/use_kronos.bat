@ECHO Off

if exist game.iso (
"D:\games\emug\kronos-2.3.1\kronos.exe" -a -i game.iso
) else (
echo Please compile first !
)
