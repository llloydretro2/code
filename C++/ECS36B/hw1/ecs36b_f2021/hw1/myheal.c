
// mybreak.c
// author: S. Felix Wu (wu@cs.ucdavis.edu)
// original: 06/21/2008 South Lake Tahoe
// updated:  06/25/2008 from IAD to SMF

// usage: $myheal <new file name created by myheal> <break_prefix> <size of each chunk in 1K> <number of chunks previously being divided into>
// to compile: $gcc -g -Wall myheal.c -o myheal

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/stat.h>
#define MAX_NAME 8192

int
main
(int argc, char *argv[])
{
  FILE *f = NULL;
  FILE *tf = NULL;
  int chunk_size = atoi(argv[3]);
  char *fname = NULL;
  int chunk_num = atoi(argv[4]);

  if (argc != 5)
    {
      printf("argc = %d => usage: myheal <source> <prefix> <chunk size (K)> <chunk number>\n", argc);
      exit(1);
    }

  chunk_size = 1024 * atoi(argv[3]); // size of chunks in bytes.
  if ((chunk_size <= 0) || (chunk_size > (1024 * 1024 * 1024)))
    {
      printf("chunk size error [%d]: size needs to be between 1 (1K) and %d (1G) \n",
	     atoi(argv[3]), 1024*1024);
      exit(1);
    }
	
  f = fopen(argv[1], "a");
  if (f != NULL)
    {
      // the file argv[1] has been successfully opened...
      int i,j;
      for (i = 0; i < chunk_num; i++)
	{
	  fname = malloc(MAX_NAME);
	  bzero((void *) fname, MAX_NAME);
	  sprintf(fname, "%s.%032d", argv[2], i);

	  tf = fopen(fname, "r");
	  
	  struct stat st;
	  stat(fname, &st);
	  int size = st.st_size;


	  if ((size != chunk_size) && (i != (chunk_num-1)))
	  	{
		  printf("Wrong chunk size, program will exit");
		  exit(1);
	  	}

	  if (tf != NULL)
	    {
	      printf(" putting %s\n", fname);
	    }
	  else
	    {
	      printf(" chunk missing, can not open %s\n", fname);
	      exit(1);
	    }

	  // now we have successfully open tf for writing!
	  // read from f, and write to tf
	  // each time 8 bytes.
	  for (j = 0; j < (chunk_size / 8); j++)
	    {
	      unsigned char ccc[8];
	      int cr, cw;

	      cr = fread(ccc, 1, 8, tf);
	      if (cr == 0)
		{
		  fclose(f);
		  fclose(tf);
		  free(fname);
		  printf("done... [%d] chunks produced for %s\n", (i+1), argv[1]);
		  exit(0);
		}

	      cw = fwrite(ccc, 1, cr, f);
	      if (cr != cw)
		{
		  printf("cr = %d, cw = %d\n", cr, cw);
		  exit(1);
		}
	    }
	  fclose(tf);
	  free(fname);
	  
	}
    }
  else
    {
      printf("file {%s} can not be open...\n", argv[1]);
      exit(1);
    }
  return 1;
}