#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_MAX 80

/**
 * print usage
 * err - exit number, 0 for success and 1 for error
 */
void usage(int err) {
  printf("%s\n", "usage: cpfile [-i input_file] [-o output_file]");
  printf("%s\n", "              [-h usage]");
  exit(err);
}

/**
 * copy file
 * ivalue - input file location for reading
 * ovalue - output file location for writing
 */
void copy(char* ivalue, char* ovalue) {
  FILE *fp1, *fp2;
  int c;

  /* check read permissions of first file */
  if(access(ivalue, R_OK) == -1) {
    printf("%s\n", "Error opening file for reading, permission error");
    exit(1);
  }

  /* check for write permissions */
  if(access(ovalue, F_OK) != -1) {
    if(access(ovalue, W_OK) == -1) {
      printf("%s\n", "Could not open file for writing, permission error");
      exit(1);
    }
  }

  /* open file for reading */
  if((fp1 = fopen(ivalue, "r")) == NULL) {
    printf("%s\n", "Error opening file for reading, file does not exist");
    exit(1);
  }
  
  /* Open file for writing */
  if((fp2 = fopen(ovalue, "w")) == NULL) {
    printf("%s\n", "Could not open file for writing, not a correct filepath");
    exit(1);
  }

  /* read by byte */
  fp1 = fopen(ivalue, "r");
  fp2 = fopen(ovalue, "w");

  while(1) {
    c = fgetc(fp1);
    if(feof(fp1)) { break; }
    fprintf(fp2, "%c", c);
  }

  fclose(fp1);
  fclose(fp2);
}

/**
 * main method
 */
int main(int argc, char **argv)
{
  extern char *optarg;
  int c;
  int iflag = 0, oflag = 0;
  char *ivalue = NULL, *ovalue = NULL;
  int help = 1;

  while((c = getopt(argc, argv, "i:o:h")) != -1) {
    help = 0;
    switch(c) {
      case 'i':
        iflag = 1;
        ivalue = optarg;
        break;
      case 'o':
        oflag = 1;
        ovalue = optarg;
        break;
      case 'h':
        usage(0);
        break;
      default:
        usage(1);
    }
  }
  if(help)
    usage(0);

  /*arg debugging
  printf("iflag = %d, oflag = %d\n", iflag, oflag);
  printf("ivalue = %s, ovalue = %s\n", ivalue, ovalue);*/

  if(iflag && oflag)
    copy(ivalue, ovalue);
  else
    usage(0);

  return 0;
}
