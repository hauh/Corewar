#!/bin/bash

OG_COREWAR="./samples/corewar"
MY_COREWAR="./corewar"

if [ ! -f "$MY_COREWAR" ]; then
	echo "File $MY_COREWAR does not exist"
	exit 1
fi

if [ ! -f "$OG_COREWAR" ]; then
	echo "File $OG_COREWAR does not exist"
	exit 1
fi

if [ -z "$1" ]; then
	echo "Usage: vm_checker.sh filename [number of cycles (default: 1000)]"
	exit 1
fi

if [ -n "$2" ]; then
	CYCLES=$2
else
	CYCLES="1000"
fi

${OG_COREWAR} -d $CYCLES $1 >og_dump
${MY_COREWAR} -d $CYCLES $1 >my_dump
printf "\e[1;33mog_dump\n\e[0;m"
printf "\e[0;32mmy_dump\n\n\e[0;m"

diff -y --width=400 --suppress-common-lines og_dump my_dump | sed $'s/|\\\t/\\\n/g' | sed n\;G
