@echo off
echo %1 origin
echo %2 destiny

xcopy "%origin%\" "%destiny%\" /i /y /s
