/**
 * Description: Zybooks 9.5 lab parsing string with comma through user input
 * Author Names: Anh Dinh & Vivian Letran
 * Authors Email: anh.dinh@sjsu.edu & vivian.letran@sjsu.edu
 * Date Created: 3/30/23
 * Date Modified: 3/30/23
 * */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    //defined two character array first word and second word to store extracted words
    char input[100];
    char first_word[50];
    char second_word[50];
    char* comma_pos;

    while (1) {
        //prompt user for input if input reads q then quit loop
        printf("Enter input string:\n");
        fgets(input, sizeof(input), stdin);

        if (input[0] == 'q' || input[0] == 'Q') {
            break;
        }
        //retrieves comma position and extract input from the two words given
        comma_pos = strchr(input, ',');
        if (comma_pos == NULL) {
            printf("Error: No comma in string.\n");
            printf("\n");
        } else {
            // Extract and remove spaces
            int i = 0;
            //skips leading spaces
            while (isspace(input[i])) {
                i++;
            }
            //skips trailing spaces
            int j = comma_pos - input - 1;
            while (isspace(input[j])) {
                j--;
            }
            //we use strncpy to extract and remove spaces
            strncpy(first_word, input + i, j - i + 1);
            first_word[j - i + 1] = '\0';
            i = comma_pos - input + 1;
            while (isspace(input[i])) {
                i++;
            }
            j = strlen(input) - 2;
            while (isspace(input[j])) {
                j--;
            }
            //repreat copy process to copy character between two point into second word array
            strncpy(second_word, input + i, j - i + 1);
            second_word[j - i + 1] = '\0';
            printf("First word: %s\n", first_word);
            printf("Second word: %s\n", second_word);
            printf("\n");
        }
    }

    return 0;
}
