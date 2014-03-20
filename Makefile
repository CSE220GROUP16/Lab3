#!/bin/bash
# File: Makefile


lab3: print.o scanner.o
	gcc -o lab3 main.c common.h print.o scanner.o
print.o: print.c common.h print.h
	gcc -c print.c

scanner.o: scanner.c common.h scanner.h
	gcc -c scanner.c

#listner_other_function.o: listner_other_function.c globals.h listner_other_function.h
#	gcc -c listner_other_function.c


#listner_print.o: listner_print.c globals.h listner_print.h
#	gcc -c listner_print.c




# !!
# this make is expecting one main in all the .c files
