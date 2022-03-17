#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
int total = 0;
int isNumber(char* str)
{
    for (int i = 0; str[i]!='\0';i++)
    {
        if (isdigit(str[i]) == 0)
            return 0;
    }
    return 1;
}

int findSize(char* fileName){
    struct stat st;

    if(stat(fileName, &st) == 0)
        return (st.st_size);
    else
        return -1;
}

int printDirContent(char * path, int min, int max, int outFile)
{
  DIR * d = opendir(path);
  if(d == NULL) {
      fprintf(stderr,"Error while opendir %s\n", path);
      return -4;
  }
  struct dirent * dir;
  while ((dir = readdir(d)) != NULL)
    {

      if(dir-> d_type != DT_DIR ){

          char d_path[255];
          sprintf(d_path, "%s/%s", path, dir->d_name);
          int size = findSize(d_path);
          if (size != -1)
          {
              total++;
              if (size >= min && size <= max)
              {
                  char full_name[255];
                  char* ptr;
                  ptr = realpath(d_path,full_name);

                  dprintf(outFile,"%s %d\n", ptr, size);
              }
          }
          else{
              fprintf(stderr,"Error while getting stat of %s",d_path);
              return -5;
          }
      }
      else
      if(dir -> d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 )
      {
        char d_path[255];
        sprintf(d_path, "%s/%s", path, dir->d_name);
        printDirContent(d_path, min, max, outFile);
      }
    }
    if (closedir(d) == -1){
        fprintf(stderr,"Error while closing %s", path);
        return -6;
    }

    return 0;
}

int main(int argc, char *argv[])
{
  if (argc<5){
    fprintf(stderr, "Not enough parameters\nExample: %s <dirictory_name> <min_size> <max_size> <output_file>\n",argv[0]);
    return -1;
  }

  int min;
  if (isNumber(argv[2]))
      min=(int) strtol(argv[2],NULL,10);
  else
  {
      perror("Second parameter should have int value\n");
      return -3;
  }

  int max;
  if (isNumber(argv[3]))
      max=(int) strtol(argv[3],NULL,10);
  else
  {
      perror("Third parameter should have int value\n");
      return -3;
  }

  char* outFileName = argv[4];
  int outFile = open(outFileName, O_CREAT|O_RDWR|O_TRUNC, 0666); //6 = rw
  if (outFile == -1){
      fprintf(stderr,"Error while opening %s\n", outFileName);
      return -2;
  }

  char* dirName = argv[1];


  int errorCode = printDirContent(dirName,min,max,outFile);
  printf("Files viewed: %d\n",total);
  return errorCode;

}

