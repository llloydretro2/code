# Makefile for HW4 Part3, ecs36b, f2020
#

CC = g++ -std=c++14
CFLAGS = -g -I/usr/include/jsoncpp

# CFLAGS = -g -D_ECS35B_DEBUG_ -I/usr/include/jsoncpp
# CFLAGS = -g -Wall -Wstrict-prototypes
# CFLAGS = -O3

LDFLAGS = 	-ljsoncpp -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server	\
		-lcurl -ljsonrpccpp-client

CORE_INCS =	Core.h Person.h Comment.h Reaction.h	\
		Message.h JvTime.h
CORE_OBJS =	Core.o Person.o Comment.o Reaction.o	\
	 	JvTime.o

# rules.
all: 	hw4part3dumpJ

#
#

hw4part3dumpJ.o:	hw4part3dumpJ.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) hw4part3dumpJ.cpp

Core.o:			Core.cpp Core.h
	$(CC) -c $(CFLAGS) Core.cpp

Person.o:		Person.cpp Person.h Core.h
	$(CC) -c $(CFLAGS) Person.cpp

Comment.o:		Comment.cpp Comment.h
	$(CC) -c $(CFLAGS) Comment.cpp

Reaction.o:		Reaction.cpp Reaction.h
	$(CC) -c $(CFLAGS) Reaction.cpp

JvTime.o:		JvTime.cpp JvTime.h
	$(CC) -c $(CFLAGS) JvTime.cpp

hw4part3dumpJ:		$(CORE_OBJS) hw4part3dumpJ.o
	$(CC) -o hw4part3dumpJ $(CORE_OBJS) hw4part3dumpJ.o $(LDFLAGS)

clean:
	rm -f	*.o *~ core hw4part3dumpJ


