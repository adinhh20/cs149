#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 100

int main(int argc, char *argv[]) {
    int num_files = argc - 1;
    FILE *files[num_files];
    pid_t pid[num_files];

    // Open all files
    for (int i = 1; i <= num_files; i++) {
        files[i-1] = fopen(argv[i], "r");
        if (files[i-1] == NULL) {
            printf("Error: Cannot open file %s\n", argv[i]);
            exit(1);
        }
    }

    // Fork a child process for each file
    for (int j = 0; j < num_files; j++) {
        pid[j] = fork();

        if (pid[j] == 0) {  // Child process
            char line[MAX_LINE_LENGTH];
            char duplicates[MAX_LINE_LENGTH][MAX_LINE_LENGTH];
            int num_duplicates = 0;

            // Read lines from file
            while (fgets(line, MAX_LINE_LENGTH, files[j]) != NULL) {
                // Check for duplicates
                for (int k = 0; k < num_duplicates; k++) {
                    if (strcmp(line, duplicates[k]) == 0) {
                        printf("Duplicate line found in %s: %s", argv[j+1], line);
                        break;
                    }
                }

                // Add line to duplicates array
                strcpy(duplicates[num_duplicates], line);
                num_duplicates++;
            }



            // Close file and exit child process
            fclose(files[j]);
            exit(0);
        }
    }

    // Wait for all child processes to complete
    for (int a = 0; a < num_files; a++) {
        waitpid(pid[a], NULL, 0);
    }

    return 0;
}
