# Makefile for Program submission
#

CC = g++ -std=c++17
CFLAGS = -g -I/usr/include/jsoncpp

# rules.
all: sp_client

#
#
sp_client.o:		sp_client.cpp
			$(CC) -c $(CFLAGS) sp_client.cpp

sp_client:		sp_client.o
			$(CC) -o sp_client sp_client.o -ljsoncpp

clean:
	rm -f *.o *~ core sp_client
