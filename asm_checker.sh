#!/bin/bash

S_FILES=./checker/tests/asm/error/
MY_ASM=./asm
OG_ASM=./vm_champs/asm
GREEN="\e[32m"
RED="\e[31m"
YELLOW="\e[1;33m"
EOC="\e[0m"

for s in ${S_FILES}*.s ; do
	${MY_ASM} $s >/dev/null
	COR="${s%".s"}.cor"
	if [[ -e ${COR} ]] ; then
		mv ${COR} my_champ
	fi
	${OG_ASM} $s >/dev/null
	if [[ -e ${COR} ]] ; then
		mv ${COR} og_champ
	fi
	if [[ -e my_champ ]] && [[ -e og_champ ]] ; then
		if [[ $( diff "my_champ" "og_champ" ) ]]
			then printf "${RED}KO${EOC} ${COR}\n"
			else printf "${GREEN}OK${EOC} ${COR}\n"
		fi
		rm my_champ
		rm og_champ
	elif [[ -e my_champ ]] ; then
		printf "${YELLOW}ERROR${EOC} og_champ was not created, but my_champ was ${s}\n"
		rm my_champ ;
	elif [[ -e og_champ ]] ; then
		printf "${YELLOW}ERROR${EOC} my_champ was not created, but og_champ was ${s}\n"
		rm og_champ
	else
		printf "${YELLOW}ERROR${EOC} incorrect file ${s}\n"
	fi
done
