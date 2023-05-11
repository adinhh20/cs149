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
    pthread_t t1, t2;
    THREADDATA *p = NULL;

    pthread_mutex_init(&count_mutex, NULL);
    pthread_mutex_init(&log_mutex, NULL);
    pthread_mutex_init(&thread_data_mutex, NULL);
    log_index = 0;

    // Ensure that the program is called with exactly 2 arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: ./countnames_threaded <file1> <file2>\n");
        exit(EXIT_FAILURE);
    }

    // Assign input files to threads
    int file1 = 1, file2 = 2;

    // Create THREADDATA object for thread 1
    pthread_mutex_lock(&thread_data_mutex);
    if (p == NULL) {
        p = (THREADDATA*) malloc(sizeof(THREADDATA));
    }
    p->thread_num = 1;
    pthread_mutex_unlock(&thread_data_mutex);

    // Create thread 1 and begin reading from input file
    pthread_create(&t1, NULL, thread_func, p);

    // Create THREADDATA object for thread 2
    pthread_mutex_lock(&thread_data_mutex);
    if (p == NULL) {
        p = (THREADDATA*) malloc(sizeof(THREADDATA));
    }
    p->thread_num = 2;
    pthread_mutex_unlock(&thread_data_mutex);

    // Create thread 2 and begin reading from input file
    pthread_create(&t2, NULL, thread_func, p);

    // Wait for both threads to complete
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
