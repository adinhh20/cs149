/*
When this program runs, it will allocate memory for an array of 100 integers using malloc(),
then set the 101st element of the array (data[100]) to zero. However, since the array only has
100 elements, setting data[100] is accessing memory outside the bounds of the array. This can
cause undefined behavior, which can manifest in various ways depending on the system and
compiler being used.

When we run this program using valgrind with the --leak-check=yes flag, valgrind reports that
there are no memory leaks, but it does not report the out-of-bounds access to data[100]. This
is because valgrind only detects memory errors that occur on the heap, while out-of-bounds
accesses to stack-allocated arrays may not be detected. Therefore, the program is not correct,
since it accesses memory outside the bounds of the allocated array. However, valgrind does not
detect this error, so it is important to be aware of potential memory errors and always make
sure to access memory within the bounds of allocated arrays.
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int* data = (int*) malloc(100 * sizeof(int));
    data[100] = 0;
    free(data);
    return 0;
}
