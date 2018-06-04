#!/bin/bash
clear
echo ; echo


com=""
# # # # # # # # # # # # # 
if [ $# -eq 0 ]
then exit 127

else
for i in $*
do 
    # echo ${i}
    com="$com ${i}"
done 

fi
# # # # # # # # # # # # # 
IP="192.168.0.$1"
pscp -r -pw yarik@$IP:/home/yarik/Documents/diploma/* .
git add --all
git commit -m "$com"
git push diploma master


