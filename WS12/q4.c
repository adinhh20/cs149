/*
When this program runs, it will allocate memory for an integer using malloc(), assign the
value 42 to it, print the value, and then exit without freeing the memory. Using valgrind with
the --leak-check=yes flag, we can check for memory leaks in this program.

As a result, valgrind reports that there is a memory leak of 4 bytes, which corresponds to the
memory allocated by malloc(). Valgrind also provides the line number where the allocation
occurred/*. Therefore, when this program runs without freeing the allocated memory, it will
cause a memory leak. Valgrind can be used to detect this and report the location of the leak.
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int* ptr = (int*) malloc(sizeof(int));
    *ptr = 42;
    printf("Value: %d\n", *ptr);
    return 0;
}
