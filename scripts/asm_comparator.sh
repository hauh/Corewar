#!/bin/bash

OG_ASM="../vm_champs/asm"
MY_ASM="../asm"
GREEN="\e[32m"
RED="\e[31m"
YELLOW="\e[1;33m"
EOC="\e[0m"

if [ ! -f "$MY_ASM" ]; then
	echo "File $MY_ASM does not exist"
	exit 1
fi

if [ ! -f "$OG_ASM" ]; then
	echo "File $OG_ASM does not exist"
	exit 1
fi

if [ -z "$1" ] ; then
	echo "Usage: asm_comparator.sh dirname"
	exit 1
fi

for S_FILE in "${1}"*.s ; do
	${MY_ASM} ${S_FILE} >/dev/null
	COR="${S_FILE%".s"}.cor"
	if [[ -e ${COR} ]] ; then
		mv ${COR} my_champ.cor
	fi
	${OG_ASM} ${S_FILE} >/dev/null
	if [[ -e ${COR} ]] ; then
		mv ${COR} og_champ.cor
	fi
	if [[ -e my_champ.cor ]] && [[ -e og_champ.cor ]] ; then
		if [[ $( diff "my_champ.cor" "og_champ.cor" ) ]]
			then printf "${RED}KO${EOC} ${COR}\n"
			else printf "${GREEN}OK${EOC} ${COR}\n"
		fi
		rm my_champ.cor
		rm og_champ.cor
	elif [[ -e my_champ.cor ]] ; then
		printf "${YELLOW}ERROR${EOC} og_champ was not created, but my_champ was ${S_FILE}\n"
		rm my_champ.cor ;
	elif [[ -e og_champ.cor ]] ; then
		printf "${YELLOW}ERROR${EOC} my_champ was not created, but og_champ was ${S_FILE}\n"
		rm og_champ.cor
	else
		printf "${YELLOW}ERROR${EOC} incorrect file ${s}\n"
	fi
done
