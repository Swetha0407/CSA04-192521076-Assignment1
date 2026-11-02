
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("Usage: %s <source> <destination> <buffer_size>\n", argv[0]);
        return 1;
    }

    int buffer_size = atoi(argv[3]);

    if (buffer_size <= 0) {
        printf("Invalid buffer size.\n");
        return 1;
    }

    int source = open(argv[1], O_RDONLY);
    if (source < 0) {
        perror("Source file");
        return 1;
    }

    int destination = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destination < 0) {
        perror("Destination file");
        close(source);
        return 1;
    }

    char *buffer = malloc((size_t)buffer_size);
    if (buffer == NULL) {
        perror("malloc");
        close(source);
        close(destination);
        return 1;
    }

    ssize_t bytes_read;
    long total_bytes = 0;

    while ((bytes_read = read(source, buffer, (size_t)buffer_size)) > 0) {
        total_bytes += bytes_read;

        ssize_t total_written = 0;

        while (total_written < bytes_read) {
            ssize_t bytes_written = write(
                destination,
                buffer + total_written,
                (size_t)(bytes_read - total_written)
            );

            if (bytes_written < 0) {
                if (errno == EINTR)
                    continue;
                perror("write");
                free(buffer);
                close(source);
                close(destination);
                return 1;
            }

            if (bytes_written == 0) {
                fprintf(stderr, "Write made no progress.\n");
                free(buffer);
                close(source);
                close(destination);
                return 1;
            }

            total_written += bytes_written;
        }
    }

    if (bytes_read < 0) {
        perror("read");
        free(buffer);
        close(source);
        close(destination);
        return 1;
    }

    printf("Buffer size : %d bytes\n", buffer_size);
    printf("Copied data : %ld bytes\n", total_bytes);
    printf("Copy completed successfully.\n");

    free(buffer);
    close(source);
    close(destination);

    return 0;
}
