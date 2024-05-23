#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "CommandHandler.h"
#include "linkedlist.h"

#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"
#define RED  "\x1b[31m"
#define GREEN "\x1b[32m"

// Function prototypes
void bg(char *program);
void bglist();
void bgkill(pid_t pid);
void bgstop(pid_t pid);
void bgstart(pid_t pid);
void pstat(pid_t pid);


Node *bg_list = NULL;

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
	bg_list = add_newNode(bg_list, pid, program);
    }
}

void bglist() {
	printList(bg_list);
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

