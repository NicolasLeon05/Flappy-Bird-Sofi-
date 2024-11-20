@echo off
echo %1 origin
echo %2 destiny

xcopy "%~1res" "%~2res" /i/y/s
