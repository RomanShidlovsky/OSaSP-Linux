#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

int main(int argc, char *argv[]){

    if (argc < 3)
    {
        fprintf(stderr,"Not enough parameters\nExample: %s <file_name> <number of lines in group>\n",argv[0]);
        return -1;
    }

    char *file_name = argv[1];
    char *n_arg = argv[2];

    char* endptr;
    int n =strtol(n_arg, &endptr, 10);
    if (endptr[0]!='\0')
    {
        perror("Last paramater should have int value\n");
        return -2;
    }

    FILE* file = fopen(file_name,"r");

    if (file == NULL)
    {
        fprintf(stderr,"Error while opening %s file\n",file_name);
        return -3;
    }

    int lines_printed = 0;
    char symbol;
    while((symbol = fgetc(file))!=EOF){
        if (symbol=='\n')
            lines_printed++;

        putc(symbol, stdout);

        if (lines_printed==n && n!=0)
        {
            lines_printed = 0;
            printf("\nPress any key...\n");
            getc(stdin);
        }
    }

    if (fclose(file) == EOF){
        perror("Error while closing file\n");
        return -4;
    }
    return 0;

}

