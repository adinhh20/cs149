#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_LOG_FILE_NAME_LENGTH 30

typedef struct Node {
    char *line;
    int index;
    struct Node *next;
} Node;

void printNodes(Node *head) {
    if (head == NULL) {
        return;
    }

    printf("%d: %s\n", head->index, head->line);
    printNodes(head->next);
}

void push(char *function, int line) {
    printf("Allocating memory in %s (line %d)\n", function, line);
}

void pop(char *function, int line) {
    printf("Freeing memory in %s (line %d)\n", function, line);
}

void *custom_malloc(size_t size, char *function, int line) {
    push(function, line);
    return malloc(size);
}

void *custom_realloc(void *ptr, size_t size, char *function, int line) {
    push(function, line);
    return realloc(ptr, size);
}

void custom_free(void *ptr, char *function, int line) {
    pop(function, line);
    free(ptr);
}

int main() {
    // Redirect stdout to memtrace.out
    int memtrace_fd = open("memtrace.out", O_RDWR | O_CREAT | O_TRUNC, 0777);
    dup2(memtrace_fd, STDOUT_FILENO);

    char **commands = custom_malloc(10 * sizeof(char *), __func__, __LINE__);
    int command_count = 0;
    int command_capacity = 10;

    Node *head = NULL;
    Node *tail = NULL;

    char command[MAX_COMMAND_LENGTH];
    while (fgets(command, MAX_COMMAND_LENGTH, stdin) != NULL) {
        command[strcspn(command, "\n")] = '\0'; // remove trailing newline

        if (command_count >= command_capacity) {
            commands = custom_realloc(commands, command_capacity * 2 * sizeof(char *), __func__, __LINE__);
            command_capacity *= 2;
        }

        commands[command_count] = custom_malloc(strlen(command) + 1, __func__, __LINE__);
        strcpy(commands[command_count], command);

        Node *node = custom_malloc(sizeof(Node), __func__, __LINE__);
        node->line = commands[command_count];
        node->index = command_count + 1;
        node->next = NULL;

        if (tail == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }

        command_count++;
    }

    // Print the content of the linked list
    printNodes(head);

    // Free the memory used by the linked list
    Node *curr = head;
    while (curr != NULL) {
        Node *next = curr->next;
        custom_free(curr, __func__, __LINE__);
        curr = next;
    }

    // Free the memory used by the array of commands
    for (int i = 0; i < command_count; i++) {
        custom_free(commands[i], __func__, __LINE__);
    }
    custom_free(commands, __func__, __LINE__);

    // Close the memtrace.out file
    close(memtrace_fd);

    return 0;
}
