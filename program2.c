#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fifo_fd;
    char read_msg[100];

    // Open the named pipe for reading
    fifo_fd = open("/tmp/my_fifo", O_RDONLY);
    if (fifo_fd == -1) {
        perror("Failed to open FIFO for reading");
        return 1;
    }

    // Read message from the FIFO
    read(fifo_fd, read_msg, sizeof(read_msg));
    printf("Program 2 received: %s\n", read_msg);
    close(fifo_fd);

    return 0;
}

