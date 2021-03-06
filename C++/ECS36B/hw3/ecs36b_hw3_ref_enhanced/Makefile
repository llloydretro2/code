# Makefile for HW3, ecs36b, s2020
#

CC = g++ -std=c++17
CFLAGS = -g

# CFLAGS = -g -Wall -Wstrict-prototypes
# CFLAGS = -O3

CORE_INCS =	Core.h Transaction.h Person.h
CORE_OBJS =	Core.o Transaction.o Person.o
SHADOW_INCS = Shadow_Flight.h Shadow_Person.h
SHADOW_OBJS = Shadow_Flight.o Shadow_Person.o

LDFLAGS_SV = -ljsoncpp -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server
LDFLAGS_CL = -ljsoncpp -lcurl -ljsonrpccpp-common -ljsonrpccpp-client

# rules.
all: 	hw3client hw3server hw3another

#
#

hw3client.h:		ecs36b_hw3.json
	jsonrpcstub ecs36b_hw3.json --cpp-server=hw3Server --cpp-client=hw3Client

hw3server.h:		ecs36b_hw3.json
	jsonrpcstub ecs36b_hw3.json --cpp-server=hw3Server --cpp-client=hw3Client

Core.o:			Core.cpp Core.h
	$(CC) -c $(CFLAGS) Core.cpp

Shadow_Person.o:	Shadow_Person.cpp Shadow_Person.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Shadow_Person.cpp

Person.o:		Person.cpp Person.h Core.h
	$(CC) -c $(CFLAGS) Person.cpp

Transaction.o:		Transaction.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) Transaction.cpp

Shadow_Flight.o:	Shadow_Flight.cpp Shadow_Flight.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Shadow_Flight.cpp

hw3client.o:		hw3client.cpp Shadow_Flight.h $(CORE_INCS) hw3client.h
	$(CC) -c $(CFLAGS) hw3client.cpp

hw3server.o:		hw3server.cpp $(CORE_INCS) hw3server.h
	$(CC) -c $(CFLAGS) hw3server.cpp

hw3server:		$(CORE_OBJS) hw3server.o
	$(CC) -o hw3server $(CORE_OBJS) hw3server.o Shadow_Flight.o $(LDFLAGS_SV) $(LDFLAGS_CL)

hw3another.o:		hw3another.cpp $(CORE_INCS) hw3server.h
	$(CC) -c $(CFLAGS) hw3another.cpp

hw3another:		$(CORE_OBJS) hw3another.o
	$(CC) -o hw3another $(CORE_OBJS) hw3another.o $(LDFLAGS_SV) $(LDFLAGS_CL)

hw3client:		$(CORE_OBJS) hw3client.o Shadow_Flight.o Shadow_Person.o
	$(CC) -o hw3client $(CORE_OBJS) hw3client.o Shadow_Flight.o Shadow_Person.o $(LDFLAGS_CL)

clean:
	rm -f *.o *~ core hw3client hw3server hw3another hw3client.h hw3server.h

