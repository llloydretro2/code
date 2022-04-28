# Makefile for HW5, ecs36b, s2020
#

CC = g++ -std=c++14
# CFLAGS = -g -I/usr/include/jsoncpp

CFLAGS = -g -D_ECS36B_HW7_ -I/usr/include/jsoncpp

# CFLAGS = -g -D_ECS36B_DEBUG_ -I/usr/include/jsoncpp
# CFLAGS = -g -Wall -Wstrict-prototypes
# CFLAGS = -O3

LDFLAGS = 	-ljsoncpp -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -lcurl -ljsonrpccpp-client

CORE_INCS =	Core.h Person.h Post.h Comment.h Reaction.h	\
		Action.h Link.h Message.h JvTime.h Tag.h OKey.h
CORE_OBJS =	Core.o Person.o Post.o Comment.o Reaction.o	\
	 	Action.o Link.o JvTime.o Tag.o

# rules.
all: 	hw7test hw7server hw7update hw7search

#
#

hw7client.h:		ecs36b_hw7_f2021.json
	jsonrpcstub ecs36b_hw7_f2021.json --cpp-server=hw7Server --cpp-client=hw7Client

hw7server.h:		ecs36b_hw7_f2021.json
	jsonrpcstub ecs36b_hw7_f2021.json --cpp-server=hw7Server --cpp-client=hw7Client

hw7update.o:		hw7client.h hw7update.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) hw7update.cpp

hw7search.o:		hw7client.h hw7search.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) hw7search.cpp

hw7server.o:		hw7server.h hw7server.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) hw7server.cpp

hw7server:		$(CORE_OBJS) hw7server.o
	$(CC) -o hw7server $(CORE_OBJS) hw7server.o $(LDFLAGS)

hw7update:		$(CORE_OBJS) hw7update.o
	$(CC) -o hw7update $(CORE_OBJS) hw7update.o $(LDFLAGS)

hw7search:		$(CORE_OBJS) hw7search.o
	$(CC) -o hw7search $(CORE_OBJS) hw7search.o $(LDFLAGS)

Core.o:			Core.cpp Core.h
	$(CC) -c $(CFLAGS) Core.cpp

Tag.o:			Tag.cpp Tag.h
	$(CC) -c $(CFLAGS) Tag.cpp

Person.o:		Person.cpp Person.h Core.h
	$(CC) -c $(CFLAGS) Person.cpp

Post.o:			Post.cpp Post.h
	$(CC) -c $(CFLAGS) Post.cpp

Comment.o:		Comment.cpp Comment.h
	$(CC) -c $(CFLAGS) Comment.cpp

Reaction.o:		Reaction.cpp Reaction.h
	$(CC) -c $(CFLAGS) Reaction.cpp

JvTime.o:		JvTime.cpp JvTime.h
	$(CC) -c $(CFLAGS) JvTime.cpp

Link.o:			Link.cpp Link.h
	$(CC) -c $(CFLAGS) Link.cpp

Action.o:		Action.cpp Action.h
	$(CC) -c $(CFLAGS) Action.cpp

hw7test.o:		hw7test.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) hw7test.cpp

hw7test:		$(CORE_OBJS) hw7test.o
	$(CC) -o hw7test $(CORE_OBJS) hw7test.o $(LDFLAGS)

clean:
	rm -f *.o *~ core hw7test hw7server hw7update hw7search hw7server.h hw7client.h
