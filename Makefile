CC=gcc
LD=gcc
CFLAGS=-ggdb -Wall -pedantic -std=c99 -D_GNU_SOURCE -O3
LDFLAGS=

prog_1=matrix_mul
prog_2=matrix_trans

PROGS=$(prog_1) $(prog_2) 

all: $(PROGS)

part_C_1: $(prog_1)
	$(CC) -o $(prog_1) $(CFLAGS) $(prog_1).c
	./$(prog_1)

part_C_2: $(prog_2)
	$(CC) -o $(prog_2) $(CFLAGS) $(prog_2).c
	./$(prog_2)	

clean: 
	-rm -rf core *.o *~ "#"*"#" Makefile.bak $(PROGS) *.dSYM

