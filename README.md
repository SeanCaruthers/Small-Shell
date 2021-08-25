/*

Author       : Sean Caruthers
Date         : 10/25/20
Description  : A small shell emulator that includes:
                  - PID expansion using $$
				  - IO redirection using < and >
				  - foregrand and background process creation using &
				  - correct handling if SIGINT and SIGTSTP
				  - cd, exit and status as internal commands
				  - other commands via fork and exec

![example](https://user-images.githubusercontent.com/20529369/130861721-08f81ea7-4687-4c20-b7f0-46c1b1bc5793.gif)

Compilation  : 
	      A makefile is included for compiling the shell
*/
