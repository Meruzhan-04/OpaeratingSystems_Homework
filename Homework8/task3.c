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
    char path[1024], byte;
    printf("File path: ");
    if (fflush(stdout) == EOF) error("flush stdout");
    if (fgets(path, sizeof path, stdin) == NULL) {
        fprintf(stderr, "Cannot read file path\n");
        return 1;
    }
    if (strchr(path, '\n') == NULL && !feof(stdin)) {
        fprintf(stderr, "File path is too long\n");
        return 1;
    }
    path[strcspn(path, "\n")] = '\0';
    if (fflush(stdout) == EOF) error("flush stdout");

    int fd = open(path, O_RDONLY);
    if (fd == -1) error("open");
    off_t size = lseek(fd, 0, SEEK_END);
    if (size == -1) error("lseek");

    for (off_t position = size; position > 0; ) {
        position--;
        if (lseek(fd, position, SEEK_SET) == -1) error("lseek");
        ssize_t n = read(fd, &byte, 1);
        if (n == -1) error("read");
        if (n == 0) {
            fprintf(stderr, "Unexpected end of file\n");
            return 1;
        }
        write_all(1, &byte, 1);
    }
    write_all(1, "\n", 1);
    if (close(fd) == -1) error("close");
    return 0;
}

