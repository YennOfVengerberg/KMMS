@echo off
mode con:cols=80 lines=40

g++ LMAOrio.cpp game_logic.cpp map_and_displays.cpp objects.cpp -o LMAOrio
LMAOrio.exe

pause