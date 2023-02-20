#include <stdio.h>

int main(void) {
   const int NUM_ELEMENTS = 20;         // Number of input integers
   int userVals[NUM_ELEMENTS];          // Array to hold the user's input integers

   /* Type your code here. */
   int len = 0;
   scanf("%d", &len);
   for (int i = 0; i < len; i++){
    scanf("%d", &userVals[i]);
  }
  for (int i = len - 1; i >= 0; i--){
    printf("%d,", userVals[i]);
  }
   printf("\n");
   return 0;
}
