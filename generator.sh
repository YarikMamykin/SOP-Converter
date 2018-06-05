#!/bin/bash

#-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-#
#										          #
#                                    USAGE DESCRIPTION                                    #
#										          #
#-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-#
if [ "$1" = "help" ]
then echo ;

      echo "About $0 usage:" ; echo ;
      echo "Params:"
      echo "<param 1> - specifies path to mesh file. File must have name like <filename>.unv, where <filename> \
      can be any string e.g. Mesh_1.unv"
      echo "<param 2> - specifies path to basic source directories. See description for more details"
      
      
      echo ; echo "Description:"
      echo "This script generates openFoam source files for mesh file, listed in <param 1>"
      echo "By default, basic source directories with appropriate files such as \"0\" \
      \"constant\" and \"system\" can be found in:"
      echo "/opt/openfoam211/tutorials/incompressible/icoFoam/cavity"
      echo "This path can be changed accordingly to <param 2>."
      echo ;
      exit 1;
fi


#-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-#
#					PART 1						  #
#	                 LOAD source files and convert to foam				  #
#-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-#

#=========================================================================================#
# check mesh file
if [ -z $1 ] || ! [ -e "$1" ]
then 
      echo "No target file specified!" ; 
      echo "Type $0 help to get usage info";
      exit 1;
fi      

if ! [[ "$1" =~ ".unv" ]]
then 
    echo "Error: bad filename. Filename should be like <filename>.unv .";
    exit 1;
fi

work_dir="`dirname \"$1\"`"
work_file="`basename \"$1\"`"
if [ "$work_dir" = "." ]
then work_dir=$PWD
fi


#=========================================================================================#
# check source files/directories
echo "Working directory --> $work_dir"
echo "Working file --> $work_file"

if [ -z $3 ] || ! [ -d "$3" ]
then 
     src_dir_root="/opt/openfoam211/tutorials/incompressible/icoFoam/cavity"     
     if ! [ -d "$src_dir_root" ] 
     then echo "No $src_dir_root was found" ; exit 1 
     fi               
else src_dir_root=$3
fi

src_dir_list="$src_dir_root/0 $src_dir_root/constant $src_dir_root/system"

# check source subfiles/subdirectories
for src in $src_dir_list
do 
   if ! [ -d $src ] ; then echo "No $src was found" ; exit 1 ; fi       
done   


#=========================================================================================#
# clearing workplace
rm -fr $work_dir/0 $work_dir/system $work_dir/constant

#=========================================================================================#
# copying source dirs and files with check
for src in $src_dir_list
do
  if ! [ -d $work_dir/"`basename \"$src\"`" ]
  then cp -R $src $work_dir/"`basename \"$src\"`"
  fi
  
  if [ -d $work_dir/"`basename \"$src\"`" ]
  then echo $work_dir/"`basename \"$src\"`"" copied successfully"
  fi  
done

#=========================================================================================#
# converting mesh file
echo "Converting $work_dir/$work_file to Foam format..."
cd $work_dir ; ideasUnvToFoam $work_file

#=========================================================================================#
# check convertion
if [ -e "constant/polyMesh/blockMeshDict" ] &&\
   [ -e "constant/polyMesh/boundary" ] &&\
   [ -e "constant/polyMesh/points" ] &&\
   [ -e "constant/polyMesh/neighbour" ] &&\
   [ -e "constant/polyMesh/owner" ] &&\
   [ -e "constant/polyMesh/faces" ] 
then echo "convertion is OK"
else echo "conversion is BAD"
fi 

#-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-#
#					PART 2						  #
#                     Parse boundary file, get patch names and types			  #
#-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-#

boundary_path="constant/polyMesh/boundary"

#=========================================================================================#
# parse boundary
IFS=$'\n'
patch_counter=0
read_patch_name=0

for line in $(cat $boundary_path) 
do
    if [[ "$line" =~ ")" ]]
    then break;
    fi

    if [[ "$line" =~ "*" ]]
    then read_patch_name=0
    fi

    if [ $read_patch_name -eq 1 ]
    then
          line=${line// /};
	  array_of_patches[$patch_counter]=$line ; ((++patch_counter)) ;
          read_patch_name=0
    fi

    if [[ "$line" =~ "(" ]] || [[ "$line" =~ "}" ]]
    then read_patch_name=1 
    fi
done


#=========================================================================================#
# configure patch types
echo "Specify patch types: (ENTER=patch)"
IFS=$' '
for (( patch_type_counter=0 ; patch_type_counter < ${#array_of_patches[*]} ; patch_type_counter++))
do
     read -p "${array_of_patches[$patch_type_counter]}=" patch_type
     if ! [ ${#patch_type} -gt 0 ]
     then patch_type="patch"
     fi
     array_of_patch_types[$patch_type_counter]=$patch_type
done

#=========================================================================================#
# display result
echo
echo "Having next patches:"
for ((i = 0; i < ${#array_of_patches[*]}; i++))
do
    echo "${array_of_patches[$i]}=${array_of_patch_types[$i]}"
done

#=========================================================================================#
# copy boundary file to boundary.new
# and change old patch types to new (certanly saved)
new_boundary="$boundary_path.new"
rm -f $new_boundary
touch $new_boundary

i=0
IFS=$'\n'
for line in $(cat $boundary_path)
do
    if [[ "$line" =~ "type" ]]
    then
           IFS=$' '
           for patch_sub_type in ${array_of_patch_types[$i]}
	   do 	       
	       line="        type            $patch_sub_type;"
               ((++i))
	       break;
           done
    fi
    
    IFS=$'\n'
    echo $line >> $new_boundary
done


#-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-#
#					PART 3						  #
#                Configure files p and U accordingly to data of boundary file		  #
#-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-#

p_file="0/p"
rm -f "$p_file.new" ; touch "$p_file.new"
u_file="0/U"
rm -f "$u_file.new" ; touch "$u_file.new"

wait_for_opening_scope=0
write_down_patches=0



function process_p {
        
	type_counter=0
	for ((i = 0; i < ${#array_of_patches[*]} ; i++))
	    do
		echo "    ${array_of_patches[$i]}" >> "$each_file.new"
		echo "    {" >> "$each_file.new"
	
		IFS=$' '	
		type_counter=0				
		for each_patch_type in ${array_of_patch_types[$i]}
		do
		        if (( type_counter == 0 ))
			then (( ++type_counter )) ; continue ;
			fi
				
			IFS=$'\n'	
		        case $each_patch_type in 
			"out")
				      echo "        type            fixedValue;" >> "$each_file.new"
				      echo "	value		uniform 0;" >> "$each_file.new" ;;
			"in")						
				      echo "        type            zeroGradient;" >> "$each_file.new" ;;
			*)	      				    
				      echo "        type            $each_patch_type;" >> "$each_file.new" ;;				      				      
			esac
			type_counter=0					
			break;			
		done 
		
		if [ $type_counter -eq 1 ]
	        then echo "        type            zeroGradient;" >> "$each_file.new" ;
		fi	
		
		echo "    }" >> "$each_file.new"
	    done    
}

function process_u {
	for ((i = 0; i < ${#array_of_patches[*]} ; i++))
	    do
		echo "    ${array_of_patches[$i]}" >> "$each_file.new"
		echo "    {" >> "$each_file.new"
			
		if [[ "${array_of_patch_types[$i]}" =~ " in" ]]
		then 
		      echo "        type            fixedValue;" >> "$each_file.new"
		      echo "	value		uniform (0 0 0.01);" >> "$each_file.new"
		      echo "    }" >> "$each_file.new"
		      continue;
		fi
	
		if [[ "${array_of_patch_types[$i]}" =~ " out" ]]
		then  
		      echo "        type            zeroGradient;" >> "$each_file.new"
		else		      
		      echo "        type            fixedValue;" >> "$each_file.new"
		      echo "	value		uniform (0 0 0);" >> "$each_file.new"
		fi		      
        
		echo "    }" >> "$each_file.new"
	    done
}

IFS=$'\n'

for each_file in $p_file $u_file
do 
    wait_for_opening_scope=0
    write_down_patches=0
    
    for line in $(cat $each_file)
    do
        # copy file till word boundaryField
	# then write down all the patches     
	if [ $write_down_patches -eq 1 ]
	then break;
	fi
	
	if [ $wait_for_opening_scope -eq 1 ]
	then write_down_patches=1
	fi
	
	if [[ "$line" =~ "boundaryField" ]]
	then wait_for_opening_scope=1
	fi	
	
	echo $line >> "$each_file.new"
    done
    
    if [[ "$each_file" =~ "p" ]]
    then process_p	    
    fi
    
    if [[ "$each_file" =~ "U" ]]
    then process_u	    
    fi
    
    echo "}" >> "$each_file.new"
    echo "// ************************************************************************* //" >> "$each_file.new"
done 

rm -f "$boundary_path" "$p_file" "$u_file"
mv "$new_boundary" "$boundary_path"
mv "$p_file.new" "$p_file"
mv "$u_file.new" "$u_file"

echo "All files are generated!"
exit 0;


