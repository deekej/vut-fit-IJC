# MAKEFILE for IJC course, 1st homework
########################################
# Author:		David Kaspar (aka Dee'Kej)
#						FIT VUT Brno, 1BIT
# E-mail:		xkaspa34@stud.fit.vutbr.cz
# Date:			17-03-2012
########################################


# Compiler.
CC=gcc

# Parameters of compilation.
CFLAGS=-std=c99 -pedantic -W -Wall -Wextra -O2 -lm

# Default rule for creating all required files:
all: prvocisla prvocisla-inline steg-decode

########################################

# Dependencies for prvocisla:
prvocisla: prvocisla.o eratosthenes.o error.o
	$(CC) prvocisla.o eratosthenes.o error.o -lm -o $@

prvocisla.o: prvocisla.c eratosthenes.h bit-array.h
	$(CC) $(CFLAGS) -c prvocisla.c -o $@

eratosthenes.o:	eratosthenes.c eratosthenes.h bit-array.h
	$(CC) $(CFLAGS) -c eratosthenes.c -o $@

########################################

# Dependencies for prvocisla-inline:
prvocisla-inline:	prvocisla-inline.o eratosthenes-inline.o error.o
	$(CC) prvocisla-inline.o eratosthenes-inline.o error.o -lm -o $@

prvocisla-inline.o: prvocisla.c eratosthenes.h bit-array.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c prvocisla.c -o $@

eratosthenes-inline.o:	eratosthenes.c eratosthenes.h bit-array.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c eratosthenes.c -o $@

########################################

# Dependencies for shared modules within
# the whole project. Also eratosthenes.c
# module above is shared, but not listed
# here.

bit-array.h: error.o

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o $@

########################################

# Dependencies for steg-decode:
steg-decode: steg-decode.o eratosthenes.o error.o ppm.o
	$(CC) steg-decode.o eratosthenes.o error.o ppm.o -lm -o $@

steg-decode.o: steg-decode.c eratosthenes.h ppm.h bit-array.h
	$(CC) $(CFLAGS) -c steg-decode.c -o $@

ppm.o: ppm.c ppm.h error.h
	$(CC) $(CFLAGS) -c ppm.c -o $@

########################################
# Other useful stuff:
########################################

#Rule to mark "false-positive" targets in project folder.
.PHONY: clean clean-all

#Remove object files generated during compiling.
clean:
	rm -f *.o

# Remove all files generated during compiling.
clean-all:
	rm -f *.o prvocisla prvocisla-inline steg-decode

	
