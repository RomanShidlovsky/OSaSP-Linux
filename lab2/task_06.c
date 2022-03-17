#include <stdio.h>
#include <dirent.h>

int printDir(const char* name)
{
    DIR* dir = opendir(name);
    if (dir == NULL){
        fprintf(stderr,"Error while opening %s directory\n", name);
        return -1;
    }

    struct dirent *d;
    while ((d = readdir(dir)) != NULL){
        printf("%s\n", d->d_name);
    }

    if (closedir(dir) == -1){
        fprintf(stderr,"Error while closing %s directory\n", name);
        return -2;
    }

    return 0;
}
int main()
{
    printf("Content of ./:\n");
    int errorCode = printDir("./");
    printf("\nContent of /:\n");
    errorCode |= printDir("/");
    return errorCode;
}
