#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>

#define MAX_PROCESSES 100
#define MAX_COMMAND_LENGTH 1024
#define MAX_PID_LENGTH 20

// Struct to store info on each process
struct process_info {
    pid_t pid;
    int index;
    char command[MAX_COMMAND_LENGTH];
    struct timeval start_time;
    struct timeval finish_time;
};

// Hash table to store info on each process
struct process_info* process_table[MAX_PROCESSES];

// Function to get current time
void get_time(struct timeval* tv) {
    gettimeofday(tv, NULL);
}

// Function to calculate the duration between two times in seconds
double get_duration(struct timeval* start_time, struct timeval* finish_time) {
    return (double) (finish_time->tv_sec - start_time->tv_sec) + (finish_time->tv_usec - start_time->tv_usec) / 1000000.0;
}

// Function to handle the SIGALRM signal
void handle_alarm(int signum) {
    // Do nothing, just interrupt system calls
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    char pid_str[MAX_PID_LENGTH];
    int process_count = 0;

    // Set up signal handler for SIGALRM
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_alarm;
    sigaction(SIGALRM, &sa, NULL);

    // Loop to read commands from stdin
    while (fgets(command, MAX_COMMAND_LENGTH, stdin)) {
        // Check if command is empty (i.e. just a newline)
        if (strlen(command) == 1) {
            continue;
        }
        // Remove newline character from command string
        command[strlen(command) - 1] = '\0';

        // Check if maximum number of processes has been reached
        if (process_count == MAX_PROCESSES) {
            fprintf(stderr, "Error: maximum number of processes reached\n");
            continue;
        }

        // Check if command is too long
        if (strlen(command) >= MAX_COMMAND_LENGTH) {
            fprintf(stderr, "Error: command is too long\n");
            continue;
        }

        // Create new process
        pid_t pid = fork();
        if (pid == -1) {
            fprintf(stderr, "Error: fork() failed\n");
            continue;
        } else if (pid == 0) {
            // Child process
            // Set up signal handler for SIGALRM
            struct sigaction sa_child;
            memset(&sa_child, 0, sizeof(sa_child));
            sa_child.sa_handler = handle_alarm;
            sigaction(SIGALRM, &sa_child, NULL);

            // Parse command string into arguments
            char *args[MAX_COMMAND_LENGTH];
            int arg_count = 0;
            args[arg_count++] = strtok(command, " ");
            while (args[arg_count - 1] != NULL && arg_count < MAX_COMMAND_LENGTH) {
                args[arg_count++] = strtok(NULL, " ");
            }
            // Set last argument to NULL as required by execvp()
            args[arg_count] = NULL;

            // Set timer for 2 seconds
            alarm(2);
            // Execute command
            execvp(args[0], args);
            // If we get here, execvp() failed
            fprintf(stderr, "Error: execvp() failed\n");
            exit(EXIT_FAILURE);
        }
    }
}