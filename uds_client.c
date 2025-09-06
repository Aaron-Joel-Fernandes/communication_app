#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCK_PATH "/tmp/uds_socket"

int main() {
    int sock;
    struct sockaddr_un server_addr;
    char *message = "Hello from client via UDS";

    // Create UDS socket
    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCK_PATH);

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        return 1;
    }

    write(sock, message, strlen(message) + 1);
    printf("Client sent: %s\n", message);

    close(sock);

    return 0;
}

