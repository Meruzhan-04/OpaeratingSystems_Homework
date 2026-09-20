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
        printf("Child PID: %d\n", getpid());
        exit(0);
    }
    else
    {
        printf("Parent PID: %d\n", getpid());
    }

    return 0;
}
