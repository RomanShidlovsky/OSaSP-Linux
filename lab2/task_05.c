#include <stdio.h>
#include <sys/stat.h>
int closeFiles(FILE* file1, FILE* file2)
{
    int nError = 0;
    if (fclose(file1) == EOF){
        perror("Error while closing file1");
        nError = -6;
    }
    if (fclose(file2) == EOF){
        perror("Error while closing file2");
        nError = -7;
    }
    return nError;
}

int main(int argc, char *argv[])
{
    if (argc<3){
        fprintf(stderr, "Not enough parameters\nExample: %s <input_file> <output_file>\n", argv[0]);
        return -1;
    }

    char* inpFileName = argv[1];
    char* outFileName = argv[2];


    FILE* inpFile = fopen(inpFileName,"r");
    if (inpFile == NULL){
        fprintf(stderr, "Error while opening %s file\n",inpFileName);
        return -2;
    }

    FILE* outFile= fopen(outFileName,"w");
    if (outFile == NULL){
        fprintf(stderr, "Error while opening %s file\n",outFileName);
        fclose(inpFile);
        return -3;
    }

    char symbol;
    while ((symbol = fgetc(inpFile)) != EOF){
        if ( fputc(symbol, outFile) == EOF){
            perror("Error while writing in file");
            break;
        }
    }

    struct stat fileStat;
    if (stat(inpFileName,&fileStat) == -1){
        perror("Error while geting information about inputfile");
        closeFiles(inpFile,outFile);
        return -4;
    }

    if (chmod(outFileName, fileStat.st_mode) == -1){
        perror("Error while setting rights");
        closeFiles(inpFile,outFile);
        return -5;
    }

    return closeFiles(inpFile,outFile);
}
