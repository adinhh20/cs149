#include <stdio.h>
#include <string.h>

/* Define your function here */
int CalcNumCharacters(char* userString, char userChar) {
    int count = 0;
    for(int i = 0; i < strlen(userString); i++) {
        if(userString[i] == userChar) {
            count++;
        }
    }
    return count;
}

int main(void) {

    /* Type your code here. */
    char ch, str[50];
    int count;

    //printf("Enter a character and a string: ");
    scanf("%c %s", &ch, str);

    count = CalcNumCharacters(str, ch);

    if(count == 1) {
        printf("%d %c\n", count, ch);
    } else {
        printf("%d %c's\n", count, ch);
    }

    return 0;
}
