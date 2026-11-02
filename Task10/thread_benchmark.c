
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define COUNT 1000

double get_time()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    return ts.tv_sec + ts.tv_nsec / 1000000000.0;
}

void *thread_function(void *arg)
{
    return NULL;
}

int main()
{
    pthread_t threads[COUNT];
    int created = 0;

    double start = get_time();

    for (int i = 0; i < COUNT; i++) {
        int result = pthread_create(
            &threads[i],
            NULL,
            thread_function,
            NULL
        );

        if (result != 0) {
            printf("pthread_create failed at thread %d (error %d).\n",
                   i + 1, result);
            break;
        }

        created++;
    }

    for (int i = 0; i < created; i++) {
        int result = pthread_join(threads[i], NULL);

        if (result != 0) {
            printf("pthread_join failed (error %d).\n", result);
            return 1;
        }
    }

    double end = get_time();

    printf("Threads successfully created: %d\n", created);
    printf("Total elapsed time: %.6f seconds\n", end - start);

    if (created != COUNT) {
        printf("The benchmark did not reach the target of %d threads.\n", COUNT);
        return 1;
    }

    return 0;
}
