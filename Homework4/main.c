#include <stdio.h>
#include "math_utils.h"

int main(void)
{
    int number = 5;
    int result = square(number);

    printf("The square of %d is %d\n", number, result);

    return 0;
}
