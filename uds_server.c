#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCK_PATH "/tmp/uds_socket"

int main() {
    int server_fd, client_fd;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_len;
    char buffer[100];

    // Create UDS socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCK_PATH);
    unlink(SOCK_PATH);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        return 1;
    }

    listen(server_fd, 1);
    printf("Waiting for connection...\n");

    client_len = sizeof(client_addr);
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    if (client_fd == -1) {
        perror("Accept failed");
        return 1;
    }

    read(client_fd, buffer, sizeof(buffer));
    printf("Server received: %s\n", buffer);
    close(client_fd);
    close(server_fd);

    return 0;
}

