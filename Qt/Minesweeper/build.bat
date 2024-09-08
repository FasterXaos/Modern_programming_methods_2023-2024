@echo off

chcp 65001


:: Настройки сборки
set BUILD_TYPE=Ninja
set BUILD_SUFFIX=ninja


:: Каталог сборки
set BUILD_FOLDER=build_%BUILD_SUFFIX%

if not exist %BUILD_FOLDER% mkdir %BUILD_FOLDER%

cd %BUILD_FOLDER%

cmake -G %BUILD_TYPE% ..
cmake --build .


xcopy /E /I ..\assets .\assets\


cmd /k
