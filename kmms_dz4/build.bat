set BUILD_TYPE=Ninja
set BUILD_SUFFIX=ninja

chcp 65001

set BUILD_FOLDER=build_%BUILD_SUFFIX%
set SOURCE_FOLDER=projects

if not exist %BUILD_FOLDER% mkdir %BUILD_FOLDER%

cd %BUILD_FOLDER%

cmake -G %BUILD_TYPE% ..\%SOURCE_FOLDER%
cmake --build .

set arr[0].file=sort.bat

set arr[0].folder=sort

copy ..\%SOURCE_FOLDER%\test\run.bat .\test
copy ..\%SOURCE_FOLDER%\menu\run_menu.bat .\menu
copy ..\%SOURCE_FOLDER%\sort\sort.bat .\src

copy ..\%SOURCE_FOLDER%\%arr[0].folder%\%arr[0].file% .\%arr[0].folder%

copy ..\run_tests.bat .

pause