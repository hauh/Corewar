#!/bin/bash

OG_COREWAR="../vm_champs/corewar"
MY_COREWAR="../corewar"

if [ -z "$1" ] ;
	then echo "Usage: corewar_checker.sh filename"
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

CYCLE=1
STEP=1000

while [ 1 ]; do
	printf "\rCurrent cycle: $CYCLE"
	${OG_COREWAR} -d $CYCLE $1 >og_dump
	${MY_COREWAR} -d $CYCLE $1 >my_dump
	if ! diff -q og_dump my_dump &>/dev/null; then
		if [ $STEP == 1 ]; then
			printf "\rDifferent output at cycle $CYCLE\n"
			exit 0
		else
			CYCLE=$((CYCLE - $STEP))
			STEP=$((STEP / 10))
		fi
	elif [ $( tail -n 1 og_dump | cut -d " " -f1 ) == "Contestant" ]; then
		if [ $STEP == 1 ]; then
			printf "\rGood job, no difference at last cycle $CYCLE!\n"
			exit 0
		else
			CYCLE=$((CYCLE - $STEP))
			STEP=$((STEP / 10))
		fi
	fi
	CYCLE=$((CYCLE + $STEP))
done
