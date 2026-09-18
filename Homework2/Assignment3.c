#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid1;
    pid_t pid2;
    pid1 = fork();

    if (pid1 < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (pid1 == 0)
    {
        execl("/bin/ls", "ls", (char *)NULL);
        perror("execl");
        exit(1);
    }
    if (waitpid(pid1, NULL, 0) < 0)
    {
        perror("waitpid");
        exit(1);
    }
    pid2 = fork();
    if (pid2 < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (pid2 == 0)
    {
        execl("/bin/date","date", (char*)NULL);
        perror("execl");
        exit(1);
    }

    if (waitpid(pid2, NULL, 0) < 0)
    {
        perror("waitpd");
        exit(1);
    }

    printf("Parent process done");

    return 0;
}
