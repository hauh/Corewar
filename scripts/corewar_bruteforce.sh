#!/bin/bash

OG_COREWAR="../vm_champs/corewar"
OG_ASM="../vm_champs/asm"
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

GREEN=""
MAGENTA="\e[35m"
EOC="\e[0m"

declare -a S_FILES_LIST=( $( find ${1} -type f -name "*.s" ) )

printf "${MAGENTA}Assembling champions:\n${EOC}"
for CHAMP in ${S_FILES_LIST[@]} ; do
	printf "$(basename ${CHAMP} )\e[K\r"
	${OG_ASM} ${CHAMP} &>/dev/null
done
printf "\e[Kdone!\n"

S_FILES_LIST=( $( find ${1} -type f -name "*.cor" ) )

printf "${MAGENTA}Fighting!\n${EOC}"
for COR_FILE_1 in ${S_FILES_LIST[@]} ; do
	for COR_FILE_2 in ${S_FILES_LIST[@]} ; do
		for COR_FILE_3 in ${S_FILES_LIST[@]} ; do
			for COR_FILE_4 in ${S_FILES_LIST[@]} ; do
				printf "$(basename ${COR_FILE_1}) $(basename ${COR_FILE_2}) $(basename ${COR_FILE_3}) $(basename ${COR_FILE_4})\e[K\r"
				./corewar_checker.sh ${COR_FILE_1} ${COR_FILE_2} ${COR_FILE_3} ${COR_FILE_4} &>/dev/null
			done
		done
	done
done
