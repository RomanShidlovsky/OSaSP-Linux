#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>


long procMax = 0, procRun = 0;

long validateNum(char *str)
{
    char *endptr;
    errno = 0;    /* To distinguish success/failure after call */
    long val = strtol(str, &endptr, 10);

    /* Check for various possible errors */

    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
            || (errno != 0 && val == 0)) 
    {
        perror("strtol");
        return -1;
    }

    if (endptr == str) 
    {
        fprintf(stderr, "No digits were found\n");
        return -1;
    }

    return val;
}

char* getFullName(char *path, char *name)
{
    char *buff;
    buff = (char*)malloc(NAME_MAX*sizeof(char));
    if (buff == NULL)
    {
        perror("Allocation error");
        return NULL;
    }

    strcpy(buff, path);
    strcat(buff,"/");
    strcat(buff, name);
    return buff;
}

void fileCopy(char *srcFileName,char *destFileName)
{
    if (procRun >= procMax)
    {
        if (wait(NULL) == -1)
        {
            perror("Wait for process error");
            return;
        }
        procRun--;
    }
    procRun++;

    pid_t pid;
    if ((pid = fork()) == -1)
    {
        perror("Can't create child process");
    }
    else if (pid == 0)
    {
        if (execlp("./filecopy","filecopy",srcFileName, destFileName, NULL) == -1)
        {
            perror("Can't copy file");
        }
        procRun--;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        fprintf(stderr, "Usage: %s <source directory> <destination directory> <number of processes>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    procMax = validateNum(argv[3]);
    if (procMax == -1 || procMax < 1)
    {
        fprintf(stderr, "Number of processes should have numeric value >0\n");
        exit(EXIT_FAILURE);
    }

    DIR *srcDir, *destDir;

    srcDir = opendir(argv[1]);
    if (srcDir == NULL)
    {
        perror("Can't open source directory");
        exit(EXIT_FAILURE);
    }

    int exitCode = 0;
    destDir = opendir(argv[2]);
    if (destDir == NULL)
    {
        perror("Can't open dest directory");
        exitCode = 1;
        goto srcDirClose;
    }

    char srcPath[PATH_MAX], destPath[PATH_MAX];

    strcpy(srcPath, argv[1]);
    strcpy(destPath, argv[2]);

    struct dirent *srcDirent, *destDirent;

    while (( srcDirent = readdir((srcDir) )) != NULL)
    {
        if (srcDirent->d_type == DT_REG)
        {
            int found = 0;
            while (( destDirent = readdir(destDir) ) != NULL)
            {
                if (destDirent->d_type == DT_REG)
                {
                    found = !strcmp(srcDirent->d_name, destDirent->d_name);
                    if (found)
                        break;
                }
            }
            if (!found)
            {
                char *srcFileName = getFullName(srcPath, srcDirent->d_name);
                char *destFileName = getFullName(destPath, srcDirent->d_name);

                fileCopy(srcFileName, destFileName);
                free(srcFileName);
                free(destFileName);
            }
            rewinddir(destDir);
        }
    }

    for (int i = 0; i < procRun; i++)
    {
        if (wait(NULL) == -1)
            perror("Wait for process error");
    }

    if (closedir(destDir) == -1)
    {
        perror("Can't close dest dir");
        exitCode = 1;
    }
srcDirClose:
    if (closedir(srcDir) == -1)
    {
        perror("Can't close source dir");
        exitCode = 1;
    }

    return exitCode;
}
