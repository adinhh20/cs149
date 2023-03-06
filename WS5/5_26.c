#include <stdio.h>
#include <string.h>

/*
function count all characters excluding spaces, periods, exclamation points, or commas
input will not exceed 50 char and returns an int
*/
int main(void) {

    char input[50];
    int counter = 0;

    fgets(input,sizeof(input),stdin);

    for(int i =0; i<strlen(input);i++){
        char ch=input[i];
        if (ch != ' ' && ch != '.' && ch != '!' && ch != ',') {
            counter++;
        }
    }

    printf("%d\n", counter);
    return 0;

}
