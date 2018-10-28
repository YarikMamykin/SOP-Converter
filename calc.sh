#! /bin/bash

proc_count=$(cat /proc/cpuinfo | grep processor | wc -l)
trap "exit 2" SIGINT,SIGTERM
export GZIP=-9; 

function execute_icoFoam() {	
	if [ $proc_count -gt 1 ]; then
		decomposePar;
		mpirun -np $proc_count icoFoam -parallel;	
		reconstructPar;
		rm -fr processor*;
	else 	
		icoFoam;
	fi
}

for u in 1 2 3 4 5; do
	mkdir V_$u; 
	if [ $u -ne 1 ]; then
		sed -i "s/0.0$((u - 1))/0.0${u}/" 0/U;
	fi

	execute_icoFoam;
	
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
