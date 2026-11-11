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
    char entry[1200], byte;
    ssize_t n;
    int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) error("open");

    write_all(1, "Log entry: ", 11);
    int length = snprintf(entry, sizeof entry, "PID=%ld: ", (long)getpid());
    if (length < 0 || length >= (int)sizeof entry - 1) {
        fprintf(stderr, "Cannot format PID\n");
        return 1;
    }

    while ((n = read(0, &byte, 1)) > 0) {
        if (length >= (int)sizeof entry - 1) {
            fprintf(stderr, "Input line is too long\n");
            return 1;
        }
        entry[length++] = byte;
        if (byte == '\n') break;
    }
    if (n == -1) error("read");
    if (entry[length - 1] != '\n') entry[length++] = '\n';
    write_all(fd, entry, length);

    off_t position = lseek(fd, 0, SEEK_CUR);
    if (position == -1) error("lseek");
    printf("Final file offset are: %lld\n", (long long)position);
    if (close(fd) == -1) error("close");
    return 0;
}

