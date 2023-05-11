#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#define MAX_NAME_LENGTH 30
#define MAX_NAMES 100

pthread_mutex_t log_mutex;
pthread_mutex_t count_mutex;
pthread_mutex_t thread_data_mutex;

int log_index = 1;

typedef struct {
    pthread_t thread_id;
    int thread_num;
} THREADDATA;

typedef struct {
    char names[MAX_NAMES][MAX_NAME_LENGTH + 1];
    int counts[MAX_NAMES];
    int num_names;
} NAMECOUNTS;

void print_log_message(char* message) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char date_time[20];
    strftime(date_time, sizeof(date_time), "%d/%m/%Y %I:%M:%S %p", tm);
    pthread_mutex_lock(&log_mutex);
    printf("Logindex %d, thread %d, PID %d, %s: %s\n", log_index++, (int)pthread_self(), getpid(), date_time, message);
    pthread_mutex_unlock(&log_mutex);
}

void init_counts(NAMECOUNTS* nc) {
    memset(nc->names, 0, sizeof(nc->names));
    memset(nc->counts, 0, sizeof(nc->counts));
    nc->num_names = 0;
}

int find_name_index(char* name, NAMECOUNTS* nc) {
    for (int i = 0; i < nc->num_names; i++) {
        if (strcmp(name, nc->names[i]) == 0) {
            return i;
        }
    }
    return -1;
}

void add_name(char* name, NAMECOUNTS* nc) {
    int index = find_name_index(name, nc);
    if (index == -1) {
        index = nc->num_names++;
        strcpy(nc->names[index], name);
    }
    nc->counts[index]++;
}

void count_names(FILE* file, NAMECOUNTS* nc, int thread_num) {
    char name[MAX_NAME_LENGTH + 1];
    while (fscanf(file, "%s", name) == 1) {
        add_name(name, nc);
        char message[100];
        sprintf(message, "read name \"%s\" in file %d", name, thread_num);
        print_log_message(message);
    }
}

void* thread_func(void* arg) {
    THREADDATA* p = (THREADDATA*)arg;
    char* filename = (p->thread_num == 1) ? "./names1.txt" : "./names2.txt";
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: could not open file %s\n", filename);
        exit(1);
    }
    char message[100];
    sprintf(message, "opened file %s", filename);
    print_log_message(message);

    NAMECOUNTS* nc = malloc(sizeof(NAMECOUNTS));
    init_counts(nc);

    count_names(file, nc, p->thread_num);

    pthread_mutex_lock(&count_mutex);
    for (int i = 0; i < nc->num_names; i++) {
        char message[100];
        sprintf(message, "counted %d instances of name \"%s\"", nc->counts[i], nc->names[i]);
        print_log_message(message);
    }
    pthread_mutex_unlock(&count_mutex);

    pthread_mutex_lock(&thread_data_mutex);
    free(p);
    pthread_mutex_unlock(&thread_data_mutex);

    fclose(file);

    return NULL;
}

int main(int argc, char *argv[]) {
    // Initialize variables
    int i;
    pthread_t t1, t2;
    THREADDATA *p = NULL;
    COUNTS counts = {0};
    pthread_mutex_t count_lock, log_lock, data_lock;
    pthread_mutex_init(&count_lock, NULL);
    pthread_mutex_init(&log_lock, NULL);
    pthread_mutex_init(&data_lock, NULL);
    LogIndex = 0;

    // Ensure that the program is called with exactly 2 arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: ./countnames_threaded <file1> <file2>\n");
        exit(EXIT_FAILURE);
    }

    // Assign input files to threads
    int file1 = 1, file2 = 2;

    // Create THREADDATA object for thread 1
    pthread_mutex_lock(&data_lock);
    if (p == NULL) {
        p = (THREADDATA*) malloc(sizeof(THREADDATA));
    }
    p->threadID = 1;
    p->inputFile = argv[file1];
    p->counts = &counts;
    p->count_lock = &count_lock;
    p->log_lock = &log_lock;
    p->data_lock = &data_lock;
    pthread_mutex_unlock(&data_lock);

    // Create thread 1 and begin reading from input file
    pthread_create(&t1, NULL, read_names, p);
    pthread_join(t1, NULL);

    // Create THREADDATA object for thread 2
    pthread_mutex_lock(&data_lock);
    if (p == NULL) {
        p = (THREADDATA*) malloc(sizeof(THREADDATA));
    }
    p->threadID = 2;
    p->inputFile = argv[file2];
    p->counts = &counts;
    p->count_lock = &count_lock;
    p->log_lock = &log_lock;
    p->data_lock = &data_lock;
    pthread_mutex_unlock(&data_lock);

    // Create thread 2 and begin reading from input file
    pthread_create(&t2, NULL, read_names, p);
    pthread_join(t2, NULL);

    // Print the final counts of all names
    print_counts(&counts);

    // Deallocate THREADDATA object
    free(p);

    // Destroy mutex locks
    pthread_mutex_destroy(&count_lock);
    pthread_mutex_destroy(&log_lock);
    pthread_mutex_destroy(&data_lock);

    return 0;
}
