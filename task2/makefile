# MAKEFILE for IJC course, 2nd homework
################################################################################
# Author:				David Kaspar (aka Dee'Kej)
#								FIT VUT Brno, 1BIT
# E-mail:				xkaspa34@stud.fit.vutbr.cz
# Date:					03-04-2012
# Last update:	24-04-2012
################################################################################


# Compiler.
CC = gcc

# Parameters of compilation for C.
CFLAGS = -std=c99 -pedantic -W -Wall -Wextra -O2

# Parametrs of compilation for C++.
CXXFLAGS = -std=c++98 -pedantic -W -Wall -Wextra -O2


# Name of directory with regression tests:
regresst_dir = regression_tests

# Names of compiled files to be removed with clean-all rule:
all_files = tail getline check-getline


# Names of programs to be created by default.
PROGS = tail wordcount wordcount-dynamic

# Default rule for creating all required files:
all: $(PROGS)

################################################################################
# Dependencies of default files:
################################################################################

tail: tail.o getline.o
	$(CC) tail.o getline.o -o $@

tail.o: tail.c getline.h
	$(CC) $(CFLAGS) -c tail.c -o $@

getline.o: getline.c getline.h
	$(CC) $(CFLAGS) -c getline.c -o $@

# Just getline module alone:
getline: getline.c getline.h
	$(CC) $(CFLAGS) -DGETLINE_DEBUG getline.c -o $@

################################################################################
################################################################################

wordcount: wordcount.o io.o libhtable.a
	$(CC) -static wordcount.o io.o libhtable.a -o $@

wordcount.o: wordcount.c io.h htable.h
	$(CC) $(CFLAGS) -c wordcount.c -o $@

io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.c -o $@

LIBHTABLE_MODULES = hash_function.o htable_clear.o htable_foreach.o \
htable_free.o htable_init.o htable_lookup.o htable_remove.o

libhtable.a: $(LIBHTABLE_MODULES) htable.h
	ar crs $@ $(LIBHTABLE_MODULES)

#######################################

hash_function.o: hash_function.c htable.h
	$(CC) $(CFLAGS) -c hash_function.c -o $@

htable_clear.o: htable_clear.c htable.h
	$(CC) $(CFLAGS) -c htable_clear.c -o $@

htable_foreach.o: htable_foreach.c htable.h
	$(CC) $(CFLAGS) -c htable_foreach.c -o $@

htable_free.o: htable_free.c htable.h
	$(CC) $(CFLAGS) -c htable_free.c -o $@

htable_init.o: htable_init.c htable.h
	$(CC) $(CFLAGS) -c htable_init.c -o $@

htable_lookup.o: htable_lookup.c htable.h
	$(CC) $(CFLAGS) -c htable_lookup.c -o $@

htable_remove.o: htable_remove.c htable.h
	$(CC) $(CFLAGS) -c htable_remove.c -o $@

################################################################################
################################################################################

wordcount-dynamic: wordcount.o io.o libhtable.so
	$(CC) -dynamic wordcount.o io.o libhtable.so -o $@

LIBHTABLE_MODULES_DYN = hash_function-PIC.o htable_clear-PIC.o \
htable_foreach-PIC.o htable_free-PIC.o htable_init-PIC.o htable_lookup-PIC.o \
htable_remove-PIC.o

libhtable.so: $(LIBHTABLE_MODULES_DYN) htable.h
	$(CC) -shared -fPIC $(LIBHTABLE_MODULES_DYN) -o libhtable.so

#######################################

hash_function-PIC.o: hash_function.c htable.h
	$(CC) $(CFLAGS) -c -fPIC hash_function.c -o $@

htable_clear-PIC.o: htable_clear.c htable.h
	$(CC) $(CFLAGS) -c -fPIC htable_clear.c -o $@

htable_foreach-PIC.o: htable_foreach.c htable.h
	$(CC) $(CFLAGS) -c -fPIC htable_foreach.c -o $@

htable_free-PIC.o: htable_free.c htable.h
	$(CC) $(CFLAGS) -c -fPIC htable_free.c -o $@

htable_init-PIC.o: htable_init.c htable.h
	$(CC) $(CFLAGS) -c -fPIC htable_init.c -o $@

htable_lookup-PIC.o: htable_lookup.c htable.h
	$(CC) $(CFLAGS) -c -fPIC htable_lookup.c -o $@

htable_remove-PIC.o: htable_remove.c htable.h
	$(CC) $(CFLAGS) -c -fPIC htable_remove.c -o $@

################################################################################

io: io.c io.h
	$(CC) $(CFLAGS) -DIO_DEBUG io.c -o $@

################################################################################
# Regression tests:
################################################################################

# Rule to mark "false-positive" targets of regression tests in project folder:
.PHONY: check-getline check-getline-clean check-tail check-tail-clean

# Module compilation and tests running:
check-getline: getline
	@echo "Regression testing in progress:"
	@echo "-------------------------------"
	@regresst -vt $(regresst_dir) $@

# Cleaning inside the regression tests tree and removing the compiled module:
check-getline-clean:
	@regresst -c $(regresst_dir) check-getline
	@rm -f getline

# Taill compilation and tests running:
check-tail: tail
	@echo "Regression testing in progress:"
	@echo "-------------------------------"
	@regresst -vt $(regresst_dir) $@

# Cleaning inside the regression tests tree and removing files of compilation:
check-tail-clean:
	@regresst -c $(regresst_dir) check-tail
	@rm -f tail tail.o getline.o


################################################################################
# Other useful stuff:
################################################################################

#Rule to mark "false-positive" targets of commands below in project folder.
.PHONY: clean clean-all

#Remove object files generated during compiling.
clean:
	@rm -f *.o *.a *.so

# Remove all files generated during compiling.
clean-all:
	@rm -f *.o *.a *.so $(all_files)

	
