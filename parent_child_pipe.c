#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t pid;
    char write_msg[] = "Hello from parent!";
    char read_msg[100];

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) {
        // Parent process: writes to the pipe
        close(pipe_fd[0]);  // Close the read end
        write(pipe_fd[1], write_msg, strlen(write_msg) + 1);
        close(pipe_fd[1]);
        wait(NULL);  // Wait for the child process
    } else {
        // Child process: reads from the pipe
        close(pipe_fd[1]);  // Close the write end
        read(pipe_fd[0], read_msg, sizeof(read_msg));
        printf("Child received: %s\n", read_msg);
        close(pipe_fd[0]);
    }

    return 0;
}
