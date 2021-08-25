COMPILER=gcc
FLAGS=-g -Wall
STD=c99
INFILES=./src/*.c
OUTFILE=smallsh

smallsh:$(INFILES)
	$(COMPILER) -std=$(STD) $(FLAGS) -o $(OUTFILE) $(INFILES)