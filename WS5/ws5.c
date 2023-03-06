#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("Hello world from PID %d\n", (int) getpid());
    int id = fork();
    if (id == 0) {
        printf("Hello world from PID %d\n", getpid());
    } else {
        int w = wait(NULL);
        printf("Hello world from PID %d\n", id);
        printf("Hello world from PID %d\n", (int) getpid());
    }
    return 0;
}
