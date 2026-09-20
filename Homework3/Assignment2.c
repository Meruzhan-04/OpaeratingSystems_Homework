#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid1;
    pid_t pid2;
    pid_t finished_pid;
    int status;

    pid1 = fork();

    if (pid1 < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (pid1 == 0)
    {
        printf("First child PID: %d\n", getpid());
        exit(10);
    }

    pid2 = fork();

    if (pid2 < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (pid2 == 0)
    {
        printf("Second child PID: %d\n", getpid());
        exit(20);
    }

    if (waitpid(pid2, &status, 0) < 0)
    {
        perror("waitpid");
        exit(1);
    }

    if (WIFEXITED(status))
    {
        printf("Second child exit status: %d\n", WEXITSTATUS(status));
    }

    finished_pid = wait(&status);

    if (finished_pid < 0)
    {
        perror("wait");
        exit(1);
    }

    if (WIFEXITED(status))
    {
        printf("First child exit status: %d\n", WEXITSTATUS(status));
    }

    printf("Parent process done\n");

    return 0;
}
