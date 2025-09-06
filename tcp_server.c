#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define BACKLOG 10

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[100];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        return 1;
    }

    if (listen(server_fd, BACKLOG) == -1) {
        perror("Listen failed");
        return 1;
    }

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

