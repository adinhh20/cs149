#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_LOG_FILE_NAME_LENGTH 30

int main() {
    char command[MAX_COMMAND_LENGTH];
    char out_file_name[MAX_LOG_FILE_NAME_LENGTH];
    char err_file_name[MAX_LOG_FILE_NAME_LENGTH];

    int line_count = 0;
    while (fgets(command, MAX_COMMAND_LENGTH, stdin) != NULL) {
        line_count++;
        command[strcspn(command, "\n")] = '\0'; // remove trailing newline

        int pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process

            // Generate log file names
            snprintf(out_file_name, MAX_LOG_FILE_NAME_LENGTH, "%d.out", getpid());
            snprintf(err_file_name, MAX_LOG_FILE_NAME_LENGTH, "%d.err", getpid());

            // Open log files
            int out_fd = open(out_file_name, O_RDWR | O_CREAT | O_APPEND, 0777);
            int err_fd = open(err_file_name, O_RDWR | O_CREAT | O_APPEND, 0777);

            // Redirect stdout and stderr to log files
            dup2(out_fd, STDOUT_FILENO);
            dup2(err_fd, STDERR_FILENO);

            // Execute command
            char *args[] = { "/bin/sh", "-c", command, NULL };
            execvp(args[0], args);

            // If execvp returns, it failed
            fprintf(stderr, "Failed to execute command: %s\n", command);
            exit(EXIT_FAILURE);
        } else {
            // Parent process

            // Wait for child process to finish
            int status;
            wait(&status);

            // Generate log file names
            snprintf(out_file_name, MAX_LOG_FILE_NAME_LENGTH, "%d.out", pid);
            snprintf(err_file_name, MAX_LOG_FILE_NAME_LENGTH, "%d.err", pid);

            // Open log files
            int out_fd = open(out_file_name, O_RDWR | O_CREAT | O_APPEND, 0777);
            int err_fd = open(err_file_name, O_RDWR | O_CREAT | O_APPEND, 0777);

            // Write log message
            dprintf(out_fd, "Finished child %d pid of parent %d\n", pid, getpid());
            dprintf(err_fd, "Exited with exitcode = %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}
