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

#include <json/json.h>

#define MAX_BUF_SIZE 1024

int main(int argc, char *argv[])
{
  int sockfd = 0, n = 0;
  char recvBuff[1024];
  struct sockaddr_in serv_addr; 

  if((argc != 6) && (argc != 4))
    {
      printf("to request: %s <ip address> <port number> <vsID> \n",
	     argv[0]);
      printf("to submit:  %s <ip address> <port number> <vsID> <github_url> <output file> \n",
	     argv[0]);
      return -1;
    } 

  memset(recvBuff, '0',sizeof(recvBuff));
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      printf("\n Error : Could not create socket \n");
      return 1;
    } 

  memset(&serv_addr, '0', sizeof(serv_addr)); 

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons((short) atoi(argv[2])); 

  if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0)
    {
      printf("\n inet_pton error occured\n");
      return 1;
    } 

  if(connect(sockfd, (struct sockaddr *) (&serv_addr), sizeof(serv_addr)) < 0)
    {
      printf("\n Error : Connect Failed \n");
      return 1;
    } 

  while ((n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
    {
      recvBuff[n] = 0;
      if(fputs(recvBuff, stdout) == EOF)
        {
	  printf("\n Error : Fputs error\n");
        }

      char sendBuff[MAX_BUF_SIZE *16];
      bzero(sendBuff, MAX_BUF_SIZE *16);
      Json::Value p;

      if (argc == 4)
	{
	  /* request a new program */
	  p["action"] = "program_request";
	  p["vsID"] = argv[3];
	}
      else
	{
	  /* submitting the result */

	  /* construct the JSON into sendBuff */
	  /* action: program submission       */
	  /* vsID: ...              argv[3]   */
	  /* program_url: ...       argv[4]   */
	  /* output: ...                      */
	  char *program_output = NULL;
	  char output_filename_buf[256];

	  /* open the outputfile to get input */
	  FILE *pout_f;
	  pout_f = fopen(argv[5], "r");
	  if (pout_f == NULL)
	    {
	      fprintf(stderr, "output file %s not found\n", argv[5]);
	      exit(-5);
	    }

	  long lSize;
	  size_t lresult;
	  // obtain file size:
	  fseek(pout_f, 0 , SEEK_END);
	  lSize = ftell(pout_f);
	  rewind(pout_f);

	  // allocate memory to contain the whole file:
	  program_output = (char *) malloc(sizeof(char)*lSize);
	  // copy the file into the buffer:
	  lresult = fread(program_output, 1, lSize, pout_f);	  
	  if (lresult != lSize)
	    {
	      fputs("Reading error", stderr);
	      exit (-3);
	    }

	  p["action"] = "program_submission";
	  p["vsID"] = argv[3];
	  p["program_url"] = argv[4];
	  p["output"] = program_output;
	}

      fprintf(stdout, "%s\n", (p.toStyledString()).c_str());
      fflush(stdout);

      snprintf(sendBuff, sizeof(sendBuff), "%s", (p.toStyledString()).c_str());
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
      return(0);
    }

  if(n < 0)
    {
      printf("\n Read error \n");
    } 

  return 0;
}
