@echo off
chcp 1251 > log
del log

set CPP_FILES="main.cpp menu_parts.cpp menu_functions.cpp"
set EXE=menu.exe
set CHARSET="-finput-charset=utf-8 -fexec-charset=windows-1251"

if exist %EXE% del %EXE%


g++ -O0 -flto -march=native "%CHARSET%" "%CPP_FILES%" -o %EXE%

%EXE%

pause