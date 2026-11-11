#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void error(const char *message)
{
    perror(message);
    exit(1);
}

int read_chunk(int fd, char *buffer, int size)
{
    int count = 0;
    while (count < size) {
        ssize_t n = read(fd, buffer + count, size - count);
        if (n == -1) error("read");
        if (n == 0) break;
        count += n;
    }
    return count;
}

int main(void)
{
    char path1[1024], path2[1024], a[1024], b[1024];
    long long position = 0, difference = -1;

    printf("First file path: ");
    if (fflush(stdout) == EOF) error("flush stdout");
    if (fgets(path1, sizeof path1, stdin) == NULL) {
        fprintf(stderr, "Cannot read file path\n");
        return 1;
    }
    if (strchr(path1, '\n') == NULL && !feof(stdin)) {
        fprintf(stderr, "File path is too long\n");
        return 1;
    }
    path1[strcspn(path1, "\n")] = '\0';
    printf("Second file path: ");
    if (fflush(stdout) == EOF) error("flush stdout");
    if (fgets(path2, sizeof path2, stdin) == NULL) {
        fprintf(stderr, "Cannot read file path\n");
        return 1;
    }
    if (strchr(path2, '\n') == NULL && !feof(stdin)) {
        fprintf(stderr, "File path is too long\n");
        return 1;
    }
    path2[strcspn(path2, "\n")] = '\0';

    int fd1 = open(path1, O_RDONLY);
    if (fd1 == -1) error("open first file");
    int fd2 = open(path2, O_RDONLY);
    if (fd2 == -1) error("open second file");

    while (1) {
        int n1 = read_chunk(fd1, a, sizeof a);
        int n2 = read_chunk(fd2, b, sizeof b);
        int common = n1 < n2 ? n1 : n2;

        for (int i = 0; i < common; i++) {
            if (a[i] != b[i]) {
                difference = position + i;
                break;
            }
        }
        if (difference != -1) break;
        if (n1 != n2) {
            difference = position + common;
            break;
        }
        if (n1 == 0) break;
        position += n1;
    }

    if (close(fd1) == -1) error("close first file");
    if (close(fd2) == -1) error("close second file");
    if (difference != -1) {
        printf("Files differ at byte %lld\n", difference);
        return 1;
    }
    printf("Files are identical\n");
    return 0;
}

