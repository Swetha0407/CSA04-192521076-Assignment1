
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;
    int status;

    printf("shell: running job 1\n");
    fflush(stdout);                  /* empty the buffer before fork() */

    // TODO 1: Create a child with fork().
    // In the child, replace the program with expr using execlp().
    // If exec fails, terminate with exit(127).
    // In the parent, wait for the child and print its exit status.

    pid = fork();

    if (pid == 0)
    {
        execlp("expr", "expr", "6", "*", "7", (char *)NULL);
        perror("execlp");
        exit(127);
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        printf("job 1 exit status %d\n", WEXITSTATUS(status));
    }
    else
    {
        perror("fork");
        return 1;
    }

    printf("shell: running job 2\n");
    fflush(stdout);

    pid = fork();

    if (pid == 0)
        _exit(3);                  /* a child that fails with code 3 */

    waitpid(pid, &status, 0);
    printf("job 2 exit status %d\n", WEXITSTATUS(status));

    return 0;
}
