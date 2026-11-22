#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { THREAD_COUNT = 2 };

struct ArraySlice {
    const int *values;
    size_t begin;
    size_t end;
    int id;
};

static void *sum_slice(void *argument)
{
    const struct ArraySlice *slice = argument;
    long long sum = 0;

    for (size_t i = slice->begin; i < slice->end; ++i) {
        sum += slice->values[i];
    }

    printf("Thread %d (indices %zu-%zu): partial sum = %lld\n",
           slice->id, slice->begin, slice->end - 1, sum);
    return NULL;
}

int main(void)
{
    const int values[] = {2, 4, 6, 8, 10, 12};
    const size_t length = sizeof values / sizeof values[0];
    const size_t midpoint = length / 2;
    struct ArraySlice slices[THREAD_COUNT] = {
        {values, 0, midpoint, 1},
        {values, midpoint, length, 2}
    };
    pthread_t threads[THREAD_COUNT];
    int started = 0;
    int status = EXIT_SUCCESS;
    for (; started < THREAD_COUNT; ++started) {
        int error = pthread_create(&threads[started], NULL, sum_slice,  &slices[started]);
        if (error != 0) {
            fprintf(stderr, "pthread_create: %s\n", strerror(error));
            status = EXIT_FAILURE;
            break;
        }
    }
    for (int i = 0; i < started; ++i) {
        int error = pthread_join(threads[i], NULL);
        if (error != 0) {
            fprintf(stderr, "pthread_join: %s\n", strerror(error));
            status = EXIT_FAILURE;
        }
    }

    return status;
}

