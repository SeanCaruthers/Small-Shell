/*

Author       : Sean Caruthers
Class        : CS344 Operating Systems
Date         : 10/25/20
Description  : A small shell emulator that is correctly handles a subset of 
               common shell commands, executes linux commands and handles a few signals

Compilation  : 
	       You may compile the executeable with the below command.
	       
	       gcc -std=c99 -Wall -g -o smallsh main.c parse.c commands.c expand.c builtin.c paths.c forking.c redirect.c signals.c bgfg.c linked.c

	       Alternatively, I have included the executeable within the zipfile.  
	       Everything was written, tested and compile on os1, so there shouldn't be any issues if running on os1

*/
