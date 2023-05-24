#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(void) {
    char command[BUFFER_SIZE];

    while (1) {
        printf("#cisfun$ ");
        if (fgets(command, BUFFER_SIZE, stdin) == NULL) {
            printf("\n");
            break;
        }

        // Remove the trailing newline character
        command[strcspn(command, "\n")] = '\0';

        pid_t pid = fork();
        if (pid == -1) {
            perror("Fork error");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            if (execve(command, NULL, NULL) == -1) {
                perror("Execve error");
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            wait(NULL);
        }
    }

    return EXIT_SUCCESS;
}
