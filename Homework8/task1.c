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
void write_all(int fd, const char *buffer, size_t count)
{
    size_t done = 0;
    while (done < count) {
        ssize_t n = write(fd, buffer + done, count - done);
        if (n == -1) error("write");
        if (n == 0) {
            fprintf(stderr, "write made no progress\n");
            exit(1);
        }
        done += n;
    }
}

int main(void)
{
    char source[1024], destination[1024], buffer[1024];
    ssize_t n;
    long long total = 0;

    printf("Source file path: ");
    if (fgets(source, sizeof source, stdin) == NULL) {
        fprintf(stderr, "Cannot read file path\n");
        return 1;
    }
    if (strchr(source, '\n') == NULL && !feof(stdin)) {
        fprintf(stderr, "File path is too long\n");
        return 1;
    }
    source[strcspn(source, "\n")] = '\0';
    printf("Destination file path: ");
    if (fgets(destination, sizeof destination, stdin) == NULL) {
        fprintf(stderr, "Cannot read file path\n");
        return 1;
    }
    if (strchr(destination, '\n') == NULL && !feof(stdin)) {
        fprintf(stderr, "File path is too long\n");
        return 1;
    }
    destination[strcspn(destination, "\n")] = '\0';

    if (strcmp(source, destination) == 0) {
        fprintf(stderr, "Choose two different files.\n");
        return 1;
    }
    int src = open(source, O_RDONLY);
    if (src == -1) error("open sorce");
    int dst = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst == -1) error("open destination");

    while ((n = read(src, buffer, sizeof buffer)) > 0) {
        write_all(dst, buffer, n);
        total += n;
    }
    if (n == -1) error("read");
    if (close(src) == -1) error("close source");
    if (close(dst) == -1) error("close destination");
    printf("Copied %lld bytes\n", total);
    return 0;
}

