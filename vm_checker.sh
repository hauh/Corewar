#!/bin/bash

MY_ASM="./corewar"
OG_ASM="./samples/corewar"

if [ -z "$1" ]
	then echo "Please specify filename"
	exit 1
fi

if [ -n "$2" ]
	then CYCLES=$2
	else CYCLES="1000"
fi


${OG_ASM} -d $CYCLES $1 >og_dump
${MY_ASM} -d $CYCLES $1 >my_dump
diff -y --width=400 --suppress-common-lines og_dump my_dump | sed $'s/|\\\t/\\\n/g'
