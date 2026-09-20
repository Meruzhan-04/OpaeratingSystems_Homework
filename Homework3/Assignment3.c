#include <stdio.h>
#include <stdlib.h>

void first_function()
{
    printf("First cleanup function\n");
}
void second_function()
{
    printf("Second cleanup function\n");
}
int main()
{
    if (atexit(first_function) != 0)
    {
        printf("Cannot register first function\n");
        return 1;
    }

    if (atexit(second_function) != 0)
    {
        printf("Cannot register second function\n");
        return 1;
    }

    printf("Program started\n");
    exit(0);
    printf("This message will not be printed\n");
    return 0;
}
