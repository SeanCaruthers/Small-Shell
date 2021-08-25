/*

Author       : Sean Caruthers
Class        : CS344 Operating Systems
Date         : 10/25/20
Description  : A small shell emulator that includes:
                  - PID expansion using $$
				  - IO redirection using < and >
				  - foregrand and background process creation using &
				  - correct handling if SIGINT and SIGTSTP
				  - cd, exit and status as internal commands
				  - other commands via fork and exec

Compilation  : 
	      A makefile is included for compiling the shell
*/
