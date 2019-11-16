#!/bin/bash

OG_COREWAR="../vm_champs/corewar"
OG_ASM="../vm_champs/asm"
MY_COREWAR="../corewar"
CHECKER="./corewar_checker.sh"

if [ -z "$1" ]; then
	echo "Usage: corewar_arena.sh dirname [-u for different fighters only]"
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

if [ ! -f "$OG_ASM" ]; then
	echo "File $OG_ASM does not exist"
	exit 1
fi

if [ ! -f "$CHECKER" ]; then
	echo "File ${CHECKER} does not exist"
	exit 1
fi

RED="\e[31m"
GREEN="\e[32m"
YELLOW="\e[33m"
MAGENTA="\e[35m"
EOC="\e[0m"

declare -a CHAMPS_ARR=( $( find ${1} -type f -name "*.s" ) )

printf "${MAGENTA}Assembling champions:\n${EOC}"
for CHAMP in ${CHAMPS_ARR[@]} ; do
	printf "$(basename ${CHAMP} )\e[K\r"
	${OG_ASM} ${CHAMP} &>/dev/null
done
printf "\e[Kdone!\n"

CHAMPS_ARR=( $( find ${1} -type f -name "*.cor" ) )

if [ $# \> 1 ] && [ "$2" == "-u" ] ; then
	UNIQUE=true
else
	UNIQUE=false
fi

function fight
{
	if ${UNIQUE} ; then
		ARGV=( "$@" )
		for (( i = 0; i < $#; ++i )) ; do
			for (( j = i + 1; j < $#; ++j )) ; do
				if [ "${ARGV[i]}" == "${ARGV[j]}" ] ; then
					return ;
				fi
			done
		done
	fi
	for CHAMP in $@ ; do
		printf "$(basename ${CHAMP}) "
	done
	printf "\n"
	${CHECKER} $@
	CHECK=$?
	if [ ${CHECK} -eq 0 ] ; then
		printf "${GREEN}OK${EOC}\n"
	elif [ ${CHECK} -eq 1 ] ; then
		printf "${RED}KO${EOC}\n"
	elif [ ${CHECK} -eq 2 ] ; then
		printf "${YELLOW}ERR${EOC}\n"
		CHAMPS_ARR=( ${CHAMPS_ARR[@]/$@} )
	else
		printf "Error in $(basename ${CHECKER}) script\n"
		exit 1
	fi
}

printf "${MAGENTA}Checking fighters:\n${EOC}"
for CHAMP in ${CHAMPS_ARR[@]} ; do
	fight ${CHAMP}
done

printf "${MAGENTA}Fighting!\n${EOC}"
for CHAMP_1 in ${CHAMPS_ARR[@]} ; do
	for CHAMP_2 in ${CHAMPS_ARR[@]} ; do
		fight ${CHAMP_1} ${CHAMP_2}
		for CHAMP_3 in ${CHAMPS_ARR[@]} ; do
			fight ${CHAMP_1} ${CHAMP_2} ${CHAMP_3}
			for CHAMP_4 in ${CHAMPS_ARR[@]} ; do
				fight ${CHAMP_1} ${CHAMP_2} ${CHAMP_3} ${CHAMP_4}
			done
		done
	done
done
