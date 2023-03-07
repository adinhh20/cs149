/**
 * Description: This is for CS 149 Assignment 2.
 * Author name: Anh Dinh
 * Author email: anh.dinh@sjsu.edu
 * Last modified date: 3-6-2023
 * Creation date: 3-5-2023
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 256

struct linecount {
    char *line;
    int count;
};

int main(int argc, char *argv[]) {
    int num_files = argc - 1;
    int linecount_size = 0;
    struct linecount *linecounts = NULL;

    // Create pipes for each child process
    int **pipes = malloc(sizeof(int *) * num_files);
    for (int i = 0; i < num_files; i++) {
        pipes[i] = malloc(sizeof(int) * 2);
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(1);
        }
    }

    // Create child processes to count lines in each file
    for (int i = 0; i < num_files; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            // Child process
            close(pipes[i][0]);  // Close read end of pipe

            FILE *fp = fopen(argv[i+1], "r");
            if (fp == NULL) {
                perror("fopen");
                exit(1);
            }

            char line[MAX_LINE_LENGTH];
            while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
                write(pipes[i][1], line, strlen(line));  // Write line to pipe
            }

            fclose(fp);
            close(pipes[i][1]);  // Close write end of pipe
            exit(0);
        } else {
            // Parent process
            close(pipes[i][1]);  // Close write end of pipe

            // Count lines from pipe
            char line[MAX_LINE_LENGTH];
            while (read(pipes[i][0], line, MAX_LINE_LENGTH) > 0) {
                int found = 0;
                for (int j = 0; j < linecount_size; j++) {
                    if (strcmp(line, linecounts[j].line) == 0) {
                        linecounts[j].count++;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    linecount_size++;
                    linecounts = realloc(linecounts, sizeof(struct linecount) * linecount_size);
                    linecounts[linecount_size-1].line = strdup(line);
                    linecounts[linecount_size-1].count = 1;
                }
            }

            close(pipes[i][0]);  // Close read end of pipe
            wait(NULL);  // Wait for child process to finish
        }
    }

    // Print line counts
    printf("Line counts:\n");
    for (int i = 0; i < linecount_size; i++) {
        printf("%d %s", linecounts[i].count, linecounts[i].line);
        free(linecounts[i].line);
    }

    free(linecounts);
    for (int i = 0; i < num_files; i++) {
        free(pipes[i]);
    }
    free(pipes);

    return 0;
}


