
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define COUNT 1000

double get_time()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    return ts.tv_sec + ts.tv_nsec / 1000000000.0;
}

int main()
{
    pid_t pids[COUNT];
    int created = 0;

    double start = get_time();

    for (int i = 0; i < COUNT; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            break;
        }

        if (pid == 0) {
            _exit(0);
        }

        pids[created++] = pid;
    }

    for (int i = 0; i < created; i++) {
        int status;
        if (waitpid(pids[i], &status, 0) < 0) {
            perror("waitpid");
            return 1;
        }
    }

    double end = get_time();

    printf("Processes successfully created: %d\n", created);
    printf("Total elapsed time: %.6f seconds\n", end - start);

    if (created != COUNT) {
        printf("The benchmark did not reach the target of %d processes.\n", COUNT);
        return 1;
    }

    return 0;
}
