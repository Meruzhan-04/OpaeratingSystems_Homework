#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
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
        execl("/bin/grep", "grep", "main", "test.txt", (char *)NULL);
        perror("execl");
        exit(1);
    }
    else
    {
        if (waitpid(pid, NULL, 0) < 0)
        {
            perror("waitpid");
            exit(1);
        }

        printf("Cnoxi processy completed e\n");
    }

    return 0;
}
