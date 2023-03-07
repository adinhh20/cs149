#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    for (int i = 0; i < 4; i++) {
        int id = fork();
        printf("Hello world from PID %d\n", id);
    }
    return 0;
}
