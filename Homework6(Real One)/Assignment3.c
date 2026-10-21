#include <stdio.h>
#include <stddef.h>

struct NormalStruct {
    char a;
    int b;
    double c;
};

#pragma pack(push, 1)
struct Packed1 {
    char a;
    int b;
    double c;
};
#pragma pack(pop)

#pragma pack(push, 2)
struct Packed2 {
    char a;
    int b;
    double c;
};
#pragma pack(pop)

#pragma pack(push, 4)
struct Packed4 {
    char a;
    int b;
    double c;
};
#pragma pack(pop)

int main(void) {
    struct NormalStruct normal;
    struct Packed1 packed1;
    struct Packed2 packed2;
    struct Packed4 packed4;

    printf("NormalStruct size: %zu bytes\n", sizeof(normal));
    printf("a: %p, offset: %zu\n",
           (void *)&normal.a, offsetof(struct NormalStruct, a));
    printf("b: %p, offset: %zu\n",
           (void *)&normal.b, offsetof(struct NormalStruct, b));
    printf("c: %p, offset: %zu\n\n",
           (void *)&normal.c, offsetof(struct NormalStruct, c));

    printf("Packed1 size: %zu bytes\n", sizeof(packed1));
    printf("a: %p, offset: %zu\n",
           (void *)&packed1.a, offsetof(struct Packed1, a));
    printf("b: %p, offset: %zu\n",
           (void *)&packed1.b, offsetof(struct Packed1, b));
    printf("c: %p, offset: %zu\n\n",
           (void *)&packed1.c, offsetof(struct Packed1, c));

    printf("Packed2 size: %zu bytes\n", sizeof(packed2));
    printf("a: %p, offset: %zu\n",
           (void *)&packed2.a, offsetof(struct Packed2, a));
    printf("b: %p, offset: %zu\n",
           (void *)&packed2.b, offsetof(struct Packed2, b));
    printf("c: %p, offset: %zu\n\n",
           (void *)&packed2.c, offsetof(struct Packed2, c));

    printf("Packed4 size: %zu bytes\n", sizeof(packed4));
    printf("a: %p, offset: %zu\n",
           (void *)&packed4.a, offsetof(struct Packed4, a));
    printf("b: %p, offset: %zu\n",
           (void *)&packed4.b, offsetof(struct Packed4, b));
    printf("c: %p, offset: %zu\n",
           (void *)&packed4.c, offsetof(struct Packed4, c));

    return 0;
}
