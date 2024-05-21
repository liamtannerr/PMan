#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"
#define RED  "\x1b[31m"
#define GREEN "\x1b[32m"

// Function prototypes
void handleCommand(char *command);
void bg(char *program);
void bglist();
void bgkill(pid_t pid);
void bgstop(pid_t pid);
void bgstart(pid_t pid);
void pstat(pid_t pid);

int main() {
    char command[256];

    while (1) {
        printf(BLUE "PMan: > " RESET);
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }

        // Remove newline character from the command
        command[strcspn(command, "\n")] = 0;

        handleCommand(command);
    }

    return 0;
}

void handleCommand(char *command) {
    char *token = strtok(command, " ");
    if (strcmp(token, "bg") == 0) {
        token = strtok(NULL, " ");
        if (token) {
            bg(token);
        } else {
            printf(RED "Error: No program specified for bg command\n" RESET);
        }
    } else if (strcmp(token, "bglist") == 0) {
        bglist();
    } else if (strcmp(token, "bgkill") == 0) {
        token = strtok(NULL, " ");
        if (token) {
            bgkill(atoi(token));
        } else {
            printf(RED "Error: No pid specified for bgkill command\n" RESET);
        }
    } else if (strcmp(token, "bgstop") == 0) {
        token = strtok(NULL, " ");
        if (token) {
            bgstop(atoi(token));
        } else {
            printf(RED "Error: No pid specified for bgstop command\n" RESET);
        }
    } else if (strcmp(token, "bgstart") == 0) {
        token = strtok(NULL, " ");
        if (token) {
            bgstart(atoi(token));
        } else {
            printf(RED "Error: No pid specified for bgstart command\n" RESET);
        }
    } else if (strcmp(token, "pstat") == 0) {
        token = strtok(NULL, " ");
        if (token) {
            pstat(atoi(token));
        } else {
            printf(RED "Error: No pid specified for pstat command\n" RESET);
        }
    } else {
        printf(RED "Error: Command not found\n" RESET);
    }
}

void bg(char *program) {
    pid_t pid = fork(); // Create a new process
    if (pid < 0) {
        // Fork failed
        perror(RED "fork" RESET);
        exit(1);
    } else if (pid == 0) {
        // Child process
        char *args[256];
        int i = 0;
        args[i++] = program;
        
        // Parse remaining arguments
        char *token = strtok(NULL, " ");
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // Null-terminate the arguments array

        if (execvp(args[0], args) < 0) {
            // execvp failed
            perror(RED "execvp" RESET);
            exit(1);
        }
    } else {
        // Parent process
        printf(GREEN "Started background process with PID %d\n" RESET, pid);
        // PMan continues running and accepting commands
    }
}

void bglist() {
    // Implementation of bglist command
}

void bgkill(pid_t pid) {
    // Implementation of bgkill command
}

void bgstop(pid_t pid) {
    // Implementation of bgstop command
}

void bgstart(pid_t pid) {
    // Implementation of bgstart command
}

void pstat(pid_t pid) {
    // Implementation of pstat command
}

