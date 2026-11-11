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
    char initial[] = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n";
    char tail[100], byte;
    int lines = 0, length = 0;
    off_t offset = 0;
    ssize_t n;

    int fd = open("numbers.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) error("open");
    write_all(fd, initial, strlen(initial));
    if (close(fd) == -1) error("close");

    fd = open("numbers.txt", O_RDWR);
    if (fd == -1) error("open");

    while (lines < 3) {
        n = read(fd, &byte, 1);
        if (n == -1) error("read");
        if (n == 0) {
            fprintf(stderr, "Unexpected end of file\n");
            return 1;
        }
        offset++;
        if (byte == '\n') lines++;
    }

    do {
        n = read(fd, &byte, 1);
        if (n == -1) error("read");
        if (n == 0) {
            fprintf(stderr, "Unexpected end of file\n");
            return 1;
        }
    } while (byte != '\n');

    while ((n = read(fd, &byte, 1)) > 0) {
        if (length == (int)sizeof tail) {
            fprintf(stderr, "Remainder is too large\n");
            return 1;
        }
        tail[length++] = byte;
    }
    if (n == -1) error("read");

    if (lseek(fd, offset, SEEK_SET) == -1) error("lseek");
    write_all(fd, "100\n", 4);
    write_all(fd, tail, length);

    if (lseek(fd, 0, SEEK_SET) == -1) error("lseek");
    while ((n = read(fd, &byte, 1)) > 0) write_all(1, &byte, 1);
    if (n == -1) error("read");
    if (close(fd) == -1) error("close");
    return 0;
}

