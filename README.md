# Corewar

Last project of the first part of algorithmic branch at School 42.

Project's objective is to create an analog of an old programing game called [Core Wars](https://en.wikipedia.org/wiki/Core_War), where programs fights in memory.

The project consists of two parts: assembler 'asm' and virtual machine 'corewar'.

### The Assembler

The programm 'asm' takes any amount of champion code files ("\*.s"), translates their code, written in pseudo-assembly language to bytecode, and saves that code to "\*.cor" files. These champion files are ready for battle in corewar program.

With -f flag it will save them into current directory instead.

With -d flag it can disassemble champions back from bytecode to their assembly code.

### The Virtual Machine

The program 'corewar' loads up to 4 player files ("\*.cor"), stores them in memory and executes their code. Every few cycles it checks if they are still alive, until only one alive left.

### Installing

The project was written and tested on macOS Sierra with 'ncurses' library for visualization.

```
git clone --recursive https://github.com/hauh/Corewar.git corewar && cd corewar && make
```

### Usage

```
-a       : Prints output from "aff" (Default is to hide it)
-t       : TIMELINE AVL TREE execution model (Faster with MANY carriages)
##### TEXT OUTPUT MODE #########################################################
   -dump N   : Dumps memory after N cycles then exits
   -s N      : Runs N cycles, dumps memory, pauses, then repeats
   -v N      : Verbosity levels, can be added together to enable several
   	  - 1 : Show lives
	  - 2 : Show cycles
	  - 4 : Show deaths
##### NCURSES OUTPUT MODE ######################################################
   -g        : Ncurses output mode
   --stealth : Hides the real contents of the memory
   --sellout : Add some fun ad to game process XD
   --mini    : Enable mini version for smaller screens
```

### Authors

Project was made in collaboration with [Rustam 'vrichese'](https://github.com/AloySobek) and [Alexander 'dbrady'](https://github.com/hardworkingcomma).

### Grade

125/125
