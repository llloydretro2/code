# Makefile for HW2 part2, ecs36b, s2020
#

CC = g++ -std=c++17
CFLAGS = -g -Wall -Wstrict-prototypes

# CFLAGS = -O3

# rules.
all: ecs36b_hw2_testing

#
#
Person.o:		Person.cpp Person.h
	$(CC) -c $(CFLAGS) Person.cpp

Transaction.o:		Transaction.cpp Transaction.h
	$(CC) -c $(CFLAGS) Transaction.cpp

ecs36b_hw2_part2.o:	ecs36b_hw2_part2.cpp Transaction.h Person.h
	$(CC) -c $(CFLAGS) ecs36b_hw2_part2.cpp

ecs36b_hw2_testing:	Person.o Transaction.o ecs36b_hw2_part2.o
	$(CC) -o ecs36b_hw2_testing Person.o Transaction.o ecs36b_hw2_part2.o

clean:
	rm -f *.o *~ core ecs36b_hw2_testing
