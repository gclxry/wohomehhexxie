@echo off
echo Begin to clean...

del /f /s /q *.aps
del /f /s /q *.ncb
del /f /s /q /ah *.suo
del /f /s /q *.vcproj.*.user
del /f /s /q *.plg
del /f /s /q *.opt

echo Finished!
echo. & pause 
