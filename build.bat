set BUILD_TYPE=Ninja
set BUILD_SUFFIX=ninja

chcp 65001

set BUILD_FOLDER=build_%BUILD_SUFFIX%
set SOURCE_FOLDER=.

if not exist %BUILD_FOLDER% mkdir %BUILD_FOLDER%

cd %BUILD_FOLDER%

copy ..\%SOURCE_FOLDER%\testing.bat .

cmake -G %BUILD_TYPE% ..\%SOURCE_FOLDER%
cmake --build .

testing.bat


pause