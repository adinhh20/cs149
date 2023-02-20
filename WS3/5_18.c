#include <stdio.h>

int main(void) {
   const int NUM_ELEMENTS = 20;
   int userValues[NUM_ELEMENTS];    // Set of data specified by the user

   int length;
   scanf("%d",&length);
   for(int i = 0; i<length; i++){
      scanf("%d", &userValues[i]);
   }
   int max = 0;
   scanf("%d",&max);
   //int max = userValues[length-1]; //last value of array
   for(int i = 0; i<length; i++){
      if(userValues[i] < max){
         printf("%d,",userValues[i]);
         }
   }
   printf("\n");
   return 0;
}
