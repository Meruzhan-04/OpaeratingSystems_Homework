#include <stdio.h>
#include <stddef.h>

struct Original{
	char a;
	int b;
	double c;
};

struct Reordered{
	double a;
	int b;
	char c;
};

int main(void) {
    struct Original first;
    struct Reordered second;

    printf("Original struct size: %zu bytes\n", sizeof(struct Original));
    printf("Original struct address: %p\n", (void *)&first);
    printf("a address: %p, offset: %zu\n",
           (void *)&first.a, offsetof(struct Original, a));
    printf("b address: %p, offset: %zu\n",
           (void *)&first.b, offsetof(struct Original, b));
    printf("c address: %p, offset: %zu\n",
           (void *)&first.c, offsetof(struct Original, c));

    printf("\nReordered struct size: %zu bytes\n", sizeof(struct Reordered));
    printf("Reordered struct address: %p\n", (void *)&second);
    printf("c address: %p, offset: %zu\n",
           (void *)&second.c, offsetof(struct Reordered, c));
    printf("b address: %p, offset: %zu\n",
           (void *)&second.b, offsetof(struct Reordered, b));
    printf("a address: %p, offset: %zu\n",
           (void *)&second.a, offsetof(struct Reordered, a));

    return 0;
}
