#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


#define TIMEZONE 3
#define NO_OPTIONS 0
void printTimeAndPid(char* processName)
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL) == -1)
    {
        perror("gettimeofday call error");
        return;
    }

    int msec = tv.tv_usec / 1000;
    int sec  = tv.tv_sec % 60;
    int min = (tv.tv_sec / 60) % 60;
    int hour = (tv.tv_sec / 3600 + TIMEZONE) % 24;

    printf("%s:\n\tPID : %d\n\tParents PID : %d\n\tTime : %02d:%02d:%02d:%03d\n",
           processName, getpid(), getppid(), hour, min, sec, msec);
}

void waitPid(pid_t pid)
{
    if (pid > 0)
    {
        if (waitpid(pid, NULL, NO_OPTIONS) == -1)
        {
           perror("waitpid call error");
        }
    }
}

int main()
{
    pid_t pid_c_1, pid_c_2;

    if ((( pid_c_1 = fork() ) > 0) && (( pid_c_2 = fork() ) > 0))
    {
        printTimeAndPid("Parent process");

        system("ps -x");

        waitPid(pid_c_1);
        waitPid(pid_c_2);
    }
    else if (pid_c_1 == 0)
    {
        printTimeAndPid("1st child process");
    }
    else if (pid_c_2 == 0)
    {
        printTimeAndPid("2nd child process");
    }
    else if (pid_c_2 < 0)
    {
        perror("2nd child create error");
        waitPid(pid_c_1);
    }
    else if (pid_c_1 < 0)
    {
        perror("1st child create error");
    }


    return 0;
}
