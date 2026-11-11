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
    char buffer[100];
    ssize_t n;
    off_t size;

    int fd = open("data.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) error("open");
    write_all(fd, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 26);
    if (close(fd) == -1) error("close");

    fd = open("data.txt", O_RDWR);
    if (fd == -1) error("open");
    size = lseek(fd, 0, SEEK_END);
    if (size == -1) error("lseek");
    printf("Original size are: %lld bytes\n", (long long)size);

    if (ftruncate(fd, 10) == -1) error("ftruncate");
    size = lseek(fd, 0, SEEK_END);
    if (size == -1) error("lseek");
    printf("New size: %lld bytes\n", (long long)size);
    if (fflush(stdout) == EOF) error("flush stdout");

    if (lseek(fd, 0, SEEK_SET) == -1) error("lseek");
    write_all(1, "Content: ", 9);
    while ((n = read(fd, buffer, sizeof buffer)) > 0)
        write_all(1, buffer, n);
    if (n == -1) error("read");
    write_all(1, "\n", 1);
    if (close(fd) == -1) error("close");
    return 0;
}

