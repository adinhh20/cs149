/**
 * Description: This is for CS 149 Assignment 1.
 * Author name: Anh Dinh
 * Author email: anh.dinh@sjsu.edu
 * Last modified date: 2-23-2023
 * Creation date: unsure
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// create each line's structure for counting duplicates
typedef struct {
    char str[MAX];
    int count;
} countString;

int main(int argc, char *argv[]) {
    FILE *fp = fopen(argv[1], "r");
    char str[MAX];
    countString *countNames;
    int i, numLines = 0, numCounts = 0;

    if (argc != 2) {
        printf("Error!\n");
        exit(1);
    }

    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    countNames = (countString *) malloc(sizeof(countString) * 1000);
    if (countNames == NULL) {
        printf("Error allocating memory.\n");
        exit(1);
    }

    while (fgets(str, sizeof(str), fp) != NULL) {
        str[strcspn(str, "\n")] = '\0';

        if (strlen(str) == 0) {
            printf("Warning - Line %d is empty.\n", numLines + 1);
            continue;   // skip so it does not count empty line as duplicated
        }

        // check if the line is a duplicate
        for (i = 0; i < numCounts; i++) {
            if (strcmp(str, countNames[i].str) == 0) {
                countNames[i].count++;
                break;
            }
        }

        // for the line that shows up once
        if (i == numCounts) {
            strcpy(countNames[numCounts].str, str);
            countNames[numCounts].count = 1;
            numCounts++;
        }

        numLines++;
    }
    for (i = 0; i < numCounts; i++) {
        printf("%s: %d\n", countNames[i].str, countNames[i].count);
    }

    // free the allocated memory
    free(countNames);

    fclose(fp);

    return 0;
}
