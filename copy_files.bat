@echo off
set target_ip=yarik@192.168.0.%1
set workspace=/home/yarik/Documents/diploma
set password=yarik
set file=%2
set local_path=%3

if [%local_path%]==[] (pscp -r -pw %password% %target_ip%:%workspace%/%file% .) else (pscp -r -pw %password% %target_ip%:%workspace%/%file% %local_path%)

