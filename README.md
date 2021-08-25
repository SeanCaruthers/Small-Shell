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

![example](https://user-images.githubusercontent.com/20529369/130861586-e97dc7b4-3d3b-4805-9a62-bfcd614c2236.gif)

Compilation  : 
	      A makefile is included for compiling the shell
*/
