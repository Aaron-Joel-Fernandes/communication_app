#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define SERVER_ADDR "127.0.0.1"
#define PORT 8080

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char *message = "Hello from TCP client";

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_ADDR, &server_addr.sin_addr);

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connect failed");
        return 1;
    }

    write(sock, message, strlen(message) + 1);
    printf("Client sent: %s\n", message);

    close(sock);

    return 0;
}

