#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

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
        printf("PMan: > ");
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
            printf("Error: No program specified for bg command\n");
        }
    } else if (strcmp(token, "bglist") == 0) {
        bglist();
    } else if (strcmp(token, "bgkill") == 0) {
        token = strtok(NULL, " ");
        if (token) {
            bgkill(atoi(token));
        } else {
            printf("Error: No pid specified for bgkill command\n");
        }
    } else if (strcmp(token, "bgstop") == 0) {
        token = strtok(NULL, " ");
        if (token) {
            bgstop(atoi(token));
        } else {
            printf("Error: No pid specified for bgstop command\n");
        }
    } else if (strcmp(token, "bgstart") == 0) {
        token = strtok(NULL, " ");
        if (token) {
            bgstart(atoi(token));
        } else {
            printf("Error: No pid specified for bgstart command\n");
        }
    } else if (strcmp(token, "pstat") == 0) {
        token = strtok(NULL, " ");
        if (token) {
            pstat(atoi(token));
        } else {
            printf("Error: No pid specified for pstat command\n");
        }
    } else {
        printf("Error: Command not found\n");
    }
}

void bg(char *program) {
    // Implementation of bg command
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

