#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid1;
    pid_t pid2;
    int status;
    pid1 = fork();
    if (pid1 < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (pid1 == 0)
    {
        printf("First child is running\n");
        exit(0);
    }

    pid2 = fork();
    if (pid2 < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (pid2 == 0)
    {
        printf("Second child is running\n");
        exit(5);
    }

    if (waitpid(pid1, &status, 0) < 0)
    {
        perror("waitpid");
        exit(1);
    }
    if (WIFEXITED(status))
    {
        int code = WEXITSTATUS(status);

        printf("First child exit status: %d\n", code);

        if (code == 0)
            printf("First child exited normally\n");
        else
            printf("First child exited with an error\n");
    }
    if (waitpid(pid2, &status, 0) < 0)
    {
        perror("waitpid");
        exit(1);
    }
    if (WIFEXITED(status))
    {
        int code = WEXITSTATUS(status);

        printf("Second child exit status: %d\n", code);
        if (code == 0)
            printf("Second child exited normally\n");
        else
            printf("Second child exted with an error\n");
    }
    return 0;
}
