#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static void *square_number(void *argument)
{
    const int number = *(const int *)argument;
    const long long square = (long long)number * number;
    printf("Squareof %d is %lld\n",number, square);
    return NULL;
}
int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5};
    enum { THREAD_COUNT = sizeof numbers / sizeof numbers[0] };
    pthread_t threads[THREAD_COUNT];
    int started = 0;
    int status = EXIT_SUCCESS;
    for (; started < THREAD_COUNT; ++started) {
        int error = pthread_create(&threads[started], NULL, square_number, &numbers[started]);
        if (error != 0) {
            fprintf(stderr, "thread_create: %s\n", strerror(error));
            status = EXIT_FAILURE;
            break;
        }
    }
    for (int i = 0; i < started; ++i) {
        int error = pthread_join(threads[i], NULL);
        if (error != 0) {
            fprintf(stderr, "thread_join: %s\n", strerror(error));
            status = EXIT_FAILURE;
        }
    }

    return status;



}

