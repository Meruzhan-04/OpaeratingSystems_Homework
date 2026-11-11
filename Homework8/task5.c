#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
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
    int fd = open("sparse.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) error("open");
    write_all(fd, "START", 5);
    if (lseek(fd, 1024 * 1024, SEEK_CUR) == -1) error("lseek");
    write_all(fd, "END", 3);
    if (close(fd) == -1) error("close");

    fd = open("sparse.bin", O_RDONLY);
    if (fd == -1) error("open");
    off_t size = lseek(fd, 0, SEEK_END);
    if (size == -1) error("lseek");
    printf("File size are: %lld bytes\n", (long long)size);

    if (close(fd) == -1) error("close");
    return 0;
}

