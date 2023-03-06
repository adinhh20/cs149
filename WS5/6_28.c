#include <stdio.h>
#include <string.h>
#include <ctype.h>
//functon takes 2 strings as parameters and assigns userStringAlphaOnly without any non-alphabet char. can use isalpha() function
void RemoveNonAlpha(char userString[], char userStringAlphaOnly[]) {
   int pos = -1;

    for(int i = 0; userString[i] != '\0'; ++i) {
        if(!isalpha(userString[i])) {continue;}
        userStringAlphaOnly[++pos] = userString[i];
    }
    userStringAlphaOnly[++pos] = '\0';
}

int main(void) {

   char line[50];
   char alphaOnly[50];

   fgets(line, sizeof(line), stdin);
   RemoveNonAlpha(line, alphaOnly);

   printf("%s\n", alphaOnly);

   return 0;
}
