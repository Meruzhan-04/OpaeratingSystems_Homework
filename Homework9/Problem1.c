#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { THREAD_COUNT = 3 };

static void *print_thread_message(void *argument)
{
    const int id = *(const int *)argument;
    printf("Thread %d is running\n", id);
    return NULL;
}

int main(void)
{
    pthread_t threads[THREAD_COUNT];
    int ids[THREAD_COUNT] = {1, 2, 3};
    int started = 0;
    int status = EXIT_SUCCESS;

    for (; started < THREAD_COUNT; ++started) {
        int error = pthread_create(&threads[started], NULL,print_thread_message, &ids[started]);
        if (error != 0){
            fprintf(stderr, "pthread_create: %s\n", strerror(error));
            status = EXIT_FAILURE;
            break;
        }}
    for (int i = 0; i < started; ++i) {
        int error = pthread_join(threads[i], NULL);
        if (error != 0) {
            fprintf(stderr, "pthread_jon: %s\n", strerror(error));
            status = EXIT_FAILURE;
        }
    }
    if (status == EXIT_SUCCESS) {
        puts("Main: all three threads have finished.");
    }
    return status;}

