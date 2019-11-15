#!/bin/bash

OG_COREWAR="../vm_champs/corewar"
MY_COREWAR="../corewar"

if [ -z "$1" ]; then
	echo "Usage: corewar_comparator.sh filenames ..."
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

read -p "Cycle to check: " CYCLE

if [[ ! "$CYCLE" =~ ^[0-9]+$ ]]; then
	echo "Incorrect number"
	exit 1
fi

${OG_COREWAR} -d $CYCLE $@ &>og_dump
${MY_COREWAR} -d $CYCLE $@ &>my_dump

if diff og_dump my_dump &>/dev/null; then
	echo "No difference at cycle $CYCLE"
	rm og_dump
	rm my_dump
	exit 0;
fi

printf "\e[1;33mog_dump\n\e[0;m"
printf "\e[0;32mmy_dump\n\n\e[0;m"
diff -y --width=400 --suppress-common-lines og_dump my_dump | sed $'s/|\\\t/\\\n/g' | sed n\;G
rm og_dump
rm my_dump
