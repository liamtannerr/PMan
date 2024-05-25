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
     if (kill(pid, SIGTERM) == 0) {
        printf("Process %d terminated\n", pid);
        bg_list = deleteNode(bg_list, pid);
    } else {
        perror("Error terminating process");
    }
}

void bgstop(pid_t pid) {
    if (kill(pid, SIGSTOP) == 0) {
        printf("Process %d stopped\n", pid);
    } else {
        perror("Error stopping process");
    }
}

void bgstart(pid_t pid) {
    if (kill(pid, SIGCONT) == 0) {
        printf("Process %d started\n", pid);
    } else {
        perror("Error starting process");
    }
}

void pstat(pid_t pid) {
    char stat_path[256], status_path[256];
    FILE *stat_file, *status_file;
    char buffer[1024];
    char comm[256], state;
    long utime, stime;
    long rss;
    int voluntary_ctxt_switches = 0, nonvoluntary_ctxt_switches = 0;

    // Build file paths
    snprintf(stat_path, sizeof(stat_path), "/proc/%d/stat", pid);
    snprintf(status_path, sizeof(status_path), "/proc/%d/status", pid);

    // Open /proc/[pid]/stat
    stat_file = fopen(stat_path, "r");
    if (stat_file == NULL) {
        perror("Error opening stat file");
        printf("Error: Process %d does not exist\n", pid);
        return;
    }

    // Read required fields from /proc/[pid]/stat
    fscanf(stat_file, "%*d (%[^)]) %c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %*u %*u %ld %ld %*d %*d %*d %*d %ld", comm, &state, &utime, &stime, &rss);
    fclose(stat_file);

    // Open /proc/[pid]/status
    status_file = fopen(status_path, "r");
    if (status_file == NULL) {
        perror("Error opening status file");
        printf("Error: Process %d does not exist\n", pid);
        return;
    }

    // Read voluntary and nonvoluntary context switches from /proc/[pid]/status
    while (fgets(buffer, sizeof(buffer), status_file)) {
        if (sscanf(buffer, "voluntary_ctxt_switches: %d", &voluntary_ctxt_switches) == 1) {
            continue;
        }
        if (sscanf(buffer, "nonvoluntary_ctxt_switches: %d", &nonvoluntary_ctxt_switches) == 1) {
            continue;
        }
    }
    fclose(status_file);

    // Calculate utime and stime in seconds
    long ticks_per_second = sysconf(_SC_CLK_TCK);
    double utime_sec = (double)utime / ticks_per_second;
    double stime_sec = (double)stime / ticks_per_second;

    // Print the information
    printf("comm: (%s)\n", comm);
    printf("state: %c\n", state);
    printf("utime: %lf\n", utime_sec);
    printf("stime: %lf\n", stime_sec);
    printf("rss: %ld\n", rss);
    printf("voluntary ctxt switches: %d\n", voluntary_ctxt_switches);
    printf("nonvoluntary ctxt switches: %d\n", nonvoluntary_ctxt_switches);
}

