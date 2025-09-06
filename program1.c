#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fifo_fd;
    char write_msg[] = "Hello from program 1!";

    // Open the named pipe for writing
    fifo_fd = open("/tmp/my_fifo", O_WRONLY);
    if (fifo_fd == -1) {
        perror("Failed to open FIFO for writing");
        return 1;
    }

    // Write message to the FIFO
    write(fifo_fd, write_msg, strlen(write_msg) + 1);
    close(fifo_fd);

    return 0;
}

