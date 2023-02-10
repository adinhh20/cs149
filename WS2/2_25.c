#include <stdio.h>

int main(void) {

   /* Type your code here. */
   int numInput1;
   int numInput2;
   int numOutput1;
   int numOutput2;
   int numOutput3;

   scanf("%d", &numInput1);
   scanf("%d", &numInput2);

   numOutput1 = numInput1 / numInput2;
   numOutput2 = numOutput1 / numInput2;
   numOutput3 = numOutput2 / numInput2;

   printf("%d %d %d\n", numOutput1, numOutput2, numOutput3);

   return 0;
}

