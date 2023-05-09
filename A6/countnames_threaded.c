#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#define MAX_NAMES 100
#define MAX_NAME_LENGTH 30

typedef struct {
    int id;
    pthread_t tid;
} THREADDATA;

typedef struct {
    char names[MAX_NAMES][MAX_NAME_LENGTH+1];
    int counts[MAX_NAMES];
    int num_names;
} NAME_COUNTS;

pthread_mutex_t counts_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t p_mutex = PTHREAD_MUTEX_INITIALIZER;
int log_index = 0;
THREADDATA *p = NULL;

void logprint(char *message) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    pthread_mutex_lock(&log_mutex);
    printf("Logindex %d, thread %d, PID %d, %02d/%02d/%d %02d:%02d:%02d: %s\n", log_index, p->id, getpid(), t->tm_mday, t->tm_mon+1, t->tm_year+1900, t->tm_hour, t->tm_min, t->tm_sec, message);
    log_index++;
    pthread_mutex_unlock(&log_mutex);
}

void update_counts(char *name, NAME_COUNTS *counts) {
    int i;
    for (i = 0; i < counts->num_names; i++) {
        if (strcmp(name, counts->names[i]) == 0) {
            counts->counts[i]++;
            return;
        }
    }
    if (counts->num_names < MAX_NAMES) {
        strcpy(counts->names[counts->num_names], name);
        counts->counts[counts->num_names] = 1;
        counts->num_names++;
    }
}

void *count_names(void *arg) {
    THREADDATA *data = (THREADDATA *) arg;
    NAME_COUNTS *counts = (NAME_COUNTS *) malloc(sizeof(NAME_COUNTS));
    counts->num_names = 0;
    FILE *fp;
    char line[MAX_NAME_LENGTH+1];
    int i;

    pthread_mutex_lock(&p_mutex);
    if (p == NULL) {
        p = data;
    }
    pthread_mutex_unlock(&p_mutex);

    logprint("opening file");
    fp = fopen(data->id == 1 ? "names1.txt" : "names2.txt", "r");
    if (fp == NULL) {
        logprint("error opening file");
        exit(1);
    }

    while (fgets(line, MAX_NAME_LENGTH+1, fp) != NULL) {
        line[strcspn(line, "\n")] = 0;
        pthread_mutex_lock(&counts_mutex);
        update_counts(line, counts);
        pthread_mutex_unlock(&counts_mutex);
    }

    fclose(fp);
    logprint("closing file");

    pthread_mutex_lock(&p_mutex);
    if (p == data) {
        free(p);
        p = NULL;
    }
    pthread_mutex_unlock(&p_mutex);

    for (i = 0; i < counts->num_names; i++) {
        pthread_mutex_lock(&counts_mutex);
        printf("%s: %d\n", counts->names[i], counts->counts[i]);
        pthread_mutex_unlock(&counts_mutex);
    }

    free(counts);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s file1 file2\n", argv[0]);
        return 1;
    }

