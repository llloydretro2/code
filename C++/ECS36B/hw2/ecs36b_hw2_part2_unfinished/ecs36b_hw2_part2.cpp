
// ecs36b_hw2_part2.cpp (this file not to be modified for hw2 part2

// run      -- make
// then run -- ./ecs36b_hw2_testing 169.237.6.102 95837 <your vsID>

// socket stuff in C (for submitting the JSON to server)

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

#define MAX_BUF_SIZE 1024

int send_ecs36b_JSON
(char *server_ip, char *server_port, const char *json_string)
{
  int sockfd = 0, n = 0;
  char recvBuff[1024];
  struct sockaddr_in serv_addr; 

  memset(recvBuff, '0',sizeof(recvBuff));
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      printf("\n Error : Could not create socket \n");
      return 1;
    } 

  memset(&serv_addr, '0', sizeof(serv_addr)); 

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons((short) atoi(server_port)); 

  if(inet_pton(AF_INET, server_ip, &serv_addr.sin_addr)<=0)
    {
      printf("\n inet_pton error occured\n");
      return -1;
    } 

  if(connect(sockfd, (struct sockaddr *) (&serv_addr), sizeof(serv_addr)) < 0)
    {
      printf("\n Error : Connect Failed \n");
      return -2;
    } 

  while ((n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
    {
      recvBuff[n] = 0;
      if(fputs(recvBuff, stdout) == EOF)
        {
	  printf("\n Error : Fputs error\n");
        }
      char sendBuff[MAX_BUF_SIZE];
      bzero(sendBuff, MAX_BUF_SIZE);
      snprintf(sendBuff, sizeof(sendBuff), "%s", json_string);
      write(sockfd, sendBuff, strlen(sendBuff));

      if ((n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
	{
	  recvBuff[n] = 0;
	  if(fputs(recvBuff, stdout) == EOF)
	    {
	      printf("\n Error : Fputs error\n");
	    }
	  fflush(stdout);
	  printf("\n");
	}
      return 0;
    }

  if(n < 0)
    {
      printf("\n Read error \n");
    } 

  return 0;
}

// C++ stuff below for HW2 Part2

#include "Person.h"
#include "Transaction.h"
#include <time.h>

int
main(int argc, char *argv[])
{
  if (argc != 4)
    {
      std::cout << argv[0] << " <ip address> <port number> <your Virtual ID>" << std::endl;
      return -1;
    }
  std::string argv_string = argv[3];

  std::cout << "Hello, ecs36b f2021 Homework 2, part 2!" << std::endl;

  GPS_DD gps_Davis {38.5, -121.7};
  GPS_DD gps_NYC {40.7, -73.95};
  GPS_DD gps_Sydney {-33.87, 151.213};
  IP_Address IP_Davis {12345678};
  IP_Address IP_Sydney {12345678};
  IP_Address IP_NYC {12375678};

  Person p1 {"Lion King", "123456789123456789"};
  Transaction flight_one {TR_TYPE_FLIGHT, p1, p1, gps_Davis, gps_NYC, IP_Davis, IP_NYC, time(NULL)};
  std::string s_one = flight_one.description();
  std::cout << "Result = " << s_one << std::endl;

  Person p2 {"Nimo", "2234123456789123456789"};
  Transaction flight_two {TR_TYPE_FLIGHT, p1, p2, gps_NYC, gps_Sydney, IP_NYC, IP_Sydney, time(NULL)};
  std::string s_two = flight_two.description();
  std::cout << "Result = " << s_two << std::endl;

  Transaction flight_three {TR_TYPE_FLIGHT, p2, p2, gps_Sydney, gps_Davis, IP_Sydney, IP_Davis, time(NULL)};
  std::string s_three = flight_three.description();
  std::cout << "Result = " << s_three << std::endl;

  std::string json_input = "{\"action\": \"ecs36b_hw2_part2\", \"vsID\": \"" + argv_string
    + "\", \"distance\": \"" + std::to_string(flight_one.getDistance())
    + "\", \"distance\": \"" + std::to_string(flight_two.getDistance())
    + "\", \"distance\": \"" + std::to_string(flight_three.getDistance())
    + "\"}";
  std::cout << json_input  << std::endl;

  int rc = send_ecs36b_JSON(argv[1], argv[2], json_input.c_str());
  std::cout << "rc = " << std::to_string(rc) << std::endl;

  std::cout << "transaction object count = " << Transaction::transaction_count << std::endl;

  return 0;
}
