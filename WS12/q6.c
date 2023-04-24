/*
When this program runs, it will allocate memory for an array of 100 integers using malloc(),
then free that memory using free(). Finally, it will try to print the value of data[0], which
is undefined behavior since the memory has been freed.

When we run this program using valgrind with the --leak-check=yes, valgrind reports an invalid
read of size 4, since the program is trying to read from memory that has been freed. This is a
common error that can lead to crashes or other undefined behavior.

Therefore, the program does run, but it exhibits undefined behavior by trying to access memory
that has been freed. Valgrind reports an error for this program, which can be helpful in
detecting memory errors. It's important to always access memory within the bounds of allocated
arrays and to free memory only when it is no longer needed.
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int* data = (int*) malloc(100 * sizeof(int));
    free(data);
    printf("%d\n", data[0]);
    return 0;
}
