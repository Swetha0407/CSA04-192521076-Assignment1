#include <stdio.h>
#include <unistd.h>

int main()
{
    char buffer[100];
    ssize_t bytes_read;

    printf("Enter a message: ");
    fflush(stdout);

    bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));

    if (bytes_read < 0)
    {
        perror("read");
        return 1;
    }

    if (write(STDOUT_FILENO, buffer, bytes_read) < 0)
    {
        perror("write");
        return 1;
    }

    return 0;
}