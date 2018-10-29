rmdir /s/q Binaries
rmdir /s/q Intermediate
del PruebaDisembodied.sln
"C:\Program Files\Epic Games\UE_4.19\Engine\Binaries\DotNET\UnrealBuildTool.exe" -projectfiles -project="%cd%\PruebaDisembodied.uproject" -game -rocket -progress
