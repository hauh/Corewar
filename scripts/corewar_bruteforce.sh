#!/bin/bash

OG_COREWAR="../vm_champs/corewar"
MY_COREWAR="../corewar"

if [ -z "$1" ]; then
	echo "Usage: corewar_bruteforce.sh dirname"
	exit 1
fi

if [ ! -f "$MY_COREWAR" ]; then
	echo "File $MY_COREWAR does not exist"
	exit 1
fi

if [ ! -f "$OG_COREWAR" ]; then
	echo "File $OG_COREWAR does not exist"
	exit 1
fi

for COR_FILE_1 in $( find ${1} -type f -name "*.cor" ) ; do
	for COR_FILE_2 in $( find ${1} -type f -name "*.cor" ) ; do
		for COR_FILE_3 in $( find ${1} -type f -name "*.cor" ) ; do
			for COR_FILE_4 in $( find ${1} -type f -name "*.cor" ) ; do
				echo "${COR_FILE_1} ${COR_FILE_2} ${COR_FILE_3} ${COR_FILE_4}"
				./corewar_checker.sh ${COR_FILE_1} ${COR_FILE_2} ${COR_FILE_3} ${COR_FILE_4}
			done
		done
	done
done
