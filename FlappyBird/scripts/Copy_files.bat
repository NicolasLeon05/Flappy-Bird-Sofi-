@echo off
set origin=%1
set destiny=%2

echo Copiando archivos de %origen% a %destino%

if not exist "%destiny%" mkdir "%destiny%"
xcopy "%origin%\*.*" "%destiny%\" /i /y /s

echo Copy completed.
pause