@echo off
mode con:cols=80 lines=40

g++ LMAOrio.cpp functions.cpp -o LMAOrio
LMAOrio.exe

pause