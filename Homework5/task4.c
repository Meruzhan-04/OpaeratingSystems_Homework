
int main() {
    char **strings = (char **)malloc(3 * sizeof(char *));

    if (strings == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        strings[i] = (char *)malloc(51 * sizeof(char));

        if (strings[i] == NULL) {
            printf("Memory allocation failed.\n");

            for (int j = 0; j < i; j++) {
                free(strings[j]);
            }

            free(strings);
            return 1;
        }
    }

    printf("Enter 3 strings: ");

    for (int i = 0; i < 3; i++) {
        scanf("%50s", strings[i]);
    }

    printf("First 3 strings: ");

    for (int i = 0; i < 3; i++) {
        printf("%s ", strings[i]);
    }

    printf("\n");

    char **temp = (char **)realloc(strings, 5 * sizeof(char *));

    if (temp == NULL) {
        printf("Memory reallocation failed.\n");

        for (int i = 0; i < 3; i++) {
            free(strings[i]);
        }

        free(strings);
        return 1;
    }

    strings = temp;

    for (int i = 3; i < 5; i++) {
        strings[i] = (char *)malloc(51 * sizeof(char));

        if (strings[i] == NULL) {
            printf("Memory allocation failed.\n");

            for (int j = 0; j < i; j++) {
                free(strings[j]);
            }

            free(strings);
            return 1;
        }
    }

    printf("Enter 2 more strings: ");

    for (int i = 3; i < 5; i++) {
        scanf("%50s", strings[i]);
    }

    printf("All strings: ");

    for (int i = 0; i < 5; i++) {
        printf("%s ", strings[i]);
    }

    printf("\n");

    for (int i = 0; i < 5; i++) {
        free(strings[i]);
    }

    free(strings);

    return 0;
}
