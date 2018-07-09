@echo off
set target_ip=yarik@192.168.0.%1
set workspace=/home/yarik/Documents/diploma
set password=yarik
set file=%2

IF EXIST %file%\NUL rmdir %file% /s /q
ELSE erase %file% 

pscp -r -pw %password% %target_ip%:%workspace%/%file% .\%file%