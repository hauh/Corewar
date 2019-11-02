## Some useful scripts for 42 Corewar project

Paths to yours and original corewar and asm files are set in first two variables in scripts.
Corewar scripts assume that dump is created with "-d number_of_cycle" flag in your corewar (you can easily change the script if it's not the case), and output is in the same format as original corewar.

### asm_coparator.sh
The script will check directory passed as argument and all subdirectories for any "*.s" files and output "OK" if there is no difference between champion assembled with your asm and champion assembled with original asm, "KO" if champions are different and "ERROR" if one or both files were not created.

### corewar_checker.sh
The script takes any amount of "*.cor" files as arguments and compares dumps of your corewar and original at every cycle until the game is ended or there is a difference between dumps. In that case it will tell you the number of first different cycle.

### corewar_comparator.sh
The script takes any amount of "*.cor" files as arguments and will ask you to enter at which cycle you want to compare dumps. Then if there is a difference at that cycle the script will output comparison line by line of different lines.
