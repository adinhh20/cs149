#include <stdio.h>
#include <string.h>

int main(void) {

   /* Type your code here. */
   char input[50], newStr[50];
   int i, j, err = 0;
   fgets(input,sizeof(input),stdin);

   int len = strlen(input);

   for (i = 0, j = 0; i < len; i++) {
      if (input[i] != ' ') {
         newStr[j++] = input[i];
      }
   }
   newStr[j] = '\0';
   len = strlen(newStr);

   for (int i = 0; i < len/2; i++) {
      if (newStr[i] != newStr[len-i-1]) {
         err = 1;
         break;
      }
   }

   if (err == 1) printf("not a palindrome: %s\n", input);
   else printf("palindrome: %s\n", input);

   return 0;
}
