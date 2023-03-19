// C program to read nth byte of a file and
// copy it to another file using lseek
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

void func(char arr[], int n)
{
    // Open the file for READ only.
    int f_read = open("start.txt", O_RDONLY);

    // Open the file for WRITE and READ only.
    int f_write = open("end.txt", O_WRONLY | O_CREAT, 0777);

    /*char line[100];
    read(f_read, line, 100);
    int i = 0;
    while(line[i] != '\0') {
        if (i % (n+2) == 0) {
            write(f_write, &line[i], 1);
        }
        i++;
    }*/

    int count = 0;

    // Write the first character of the line to the output file
    if (read(f_read, arr, 1)) {
        write(f_write, arr, 1);
        count++;
    }

    while (read(f_read, arr, 1))
    {
        // Skip the next 2 characters
        if(count % 2 == 1) {
            lseek(f_read, 1, SEEK_CUR);
        }
        // Write the current character to the output file
        else {
            write(f_write, arr, 1);
        }
        count++;
    }
    close(f_write);
    close(f_read);
}

// Driver code
int main()
{
    char arr[100];
    int n;
    //n = 5;
    n = 2;
    // Calling for the function
    func(arr, n);
    return 0;
}
