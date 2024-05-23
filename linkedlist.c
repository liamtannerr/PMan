#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include "linkedlist.h"

 
Node * add_newNode(Node* head, pid_t new_pid, char * new_path){
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("malloc");
        exit(1);
    }
    new_node->pid = new_pid;
    strncpy(new_node->command, new_path, sizeof(new_node->command) - 1);
    new_node->command[sizeof(new_node->command) - 1] = '\0';
    new_node->next = head;
    return new_node;
}


Node * deleteNode(Node* head, pid_t pid){
    Node *temp = head, *prev = NULL;
    if (temp != NULL && temp->pid == pid) {
        head = temp->next;
        free(temp);
        return head;
    }
    while (temp != NULL && temp->pid != pid) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return head;
    prev->next = temp->next;
    free(temp);
    return head;
}

void printList(Node *node){
    int count = 0;
    while (node != NULL) {
        printf("%d: %s\n", node->pid, node->command);
        count++;
        node = node->next;
    }
    printf("Total background jobs: %d\n", count);
}


int PifExist(Node *node, pid_t pid){
    while (node != NULL) {
        if (node->pid == pid)
            return 1;
        node = node->next;
    }
    return 0;
}


