@echo off
set target_ip=target@192.168.0.%1
set workspace=/home/target/Desktop
set password=target
set file=%2

pscp -r -pw %password% %file% %target_ip%:%workspace%