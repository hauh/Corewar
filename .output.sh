#!/bin/bash

if [ -x "$(command -v figlet)" ]; then
	figlet -k -w 50 Virtual Machine is ready
else
	printf "Virtual Machine is ready\n"
fi
