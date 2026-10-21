#include <stdio.h>

int main(void){
	int number = 67;
	char character = 'B';
	double decimal = 6.7;
	short karch = 6;

	printf("Sizes:\n");
    	printf("int: %zu bytes, alignment: %zu\n", sizeof(int), _Alignof(int));
    	printf("char: %zu byte, alignment: %zu\n", sizeof(char), _Alignof(char));
    	printf("double: %zu bytes, alignment: %zu\n", sizeof(double), _Alignof(double));
    	printf("short: %zu bytes, alignment: %zu\n", sizeof(short), _Alignof(short));

    	printf("\nAddresses:\n");
    	printf("int: %p\n", (void *)&number);
    	printf("char: %p\n", (void *)&character);
    	printf("double: %p\n", (void *)&decimal);
    	printf("short: %p\n", (void *)&karch);

    	return 0;
}
