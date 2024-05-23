#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <sys/types.h>

// Define the structure for the linked list node
typedef struct Node {
    pid_t pid;
    char command[256];
    struct Node *next;
} Node;

// Function prototypes
Node* add_newNode(Node* head, pid_t new_pid, char *new_path);
Node* deleteNode(Node* head, pid_t pid);
void printList(Node *node);
int PifExist(Node *node, pid_t pid);

#endif

