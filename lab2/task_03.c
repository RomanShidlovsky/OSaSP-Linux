#include <stdio.h>
#define EXIT_SYMBOL 6
int main(int argc, char *argv[])
{
        if (argc < 2){
                fprintf(stderr,"Not enough parameters\n Example: %s <file_name>\n", argv[0]);
                return -1;
        }

        FILE* file = fopen(argv[1], "w");

        if (file == NULL){
                perror("Error while opening file\n");
                return -2;
        }

        printf("Enter Ctrl+F to exit\n");

        char symbol;
        while ((symbol = getc(stdin)) != EXIT_SYMBOL){

            if (fputc(symbol, file) == EOF){
                perror("Error while writing to the file\n");
                break;
            }
        }

        if(fclose(file) == EOF){
                perror("Error while closing file(Data can be lost).\n");
                return -3;
        }
        return 0;
}
