#include "CommandHandler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

// Function prototypes for the other commands
void bg(char *program);
void bglist();
void bgkill(pid_t pid);
void bgstop(pid_t pid);
void bgstart(pid_t pid);
void pstat(pid_t pid);

extern Node *bg_list;

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
