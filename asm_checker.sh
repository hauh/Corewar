#!/bin/bash

S_DIR=./vm_champs/champs/championships/*/*/
MY_ASM=./asm
OG_ASM=./vm_champs/asm
GREEN="\e[32m"
RED="\e[31m"
YELLOW="\e[1;33m"
EOC="\e[0m"

for S_FILE in ${S_DIR}*.s ; do
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
