@echo off
mode con:cols=80 lines=40

g++ main.cpp map_and_displays.cpp objects.cpp game_logic_templates.cpp level_creator_templates.cpp -o mario
mario.exe

pause