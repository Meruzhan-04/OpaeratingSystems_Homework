#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("Chld PID: %d\n", getpid());
        printf("Child is exiting\n");
        exit(0);
    }
    else
    {
        printf("Parent PID: %d\n", getpid());
        printf("Parent is sleeping for 30 seconds\n");
        sleep(30);
    }
    return 0;
}
