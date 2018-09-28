#! /bin/bash

export GZIP=-9; 

for u in 1 2 3 4 5; do
	mkdir V_$u; 
	if [ $u -ne 1 ]; then
		sed -i "s/0.0$((u - 1))/0.0${u}/" 0/U
		icoFoam;
	else 
		icoFoam;
	fi;
	
	for item in $(ls); do 
		if ! [ -d "$item" ] || [ "$item" = "V_*" ]; then 
			continue; 
		fi; 
		if [ "$item" = "0" ] || [ "$item" = "constant" ] || [ "$item" = "system" ]; then 
			cp -r $item V_$u; 
		else 
			mv $item V_$u; 
		fi; 
	done; 
	
	tar -cvzf V_$u.tar V_$u;
	rm -fr V_$u;
done;
