#include <stdio.h>

int main(void) {
   int currentPrice;
   int lastMonthsPrice;

   scanf("%d", &currentPrice);
   scanf("%d", &lastMonthsPrice);

   /* Type your code here. */
   int dif = currentPrice - lastMonthsPrice;
   printf("This house is $%d. The change is $%d since last month.\n", currentPrice, dif);
   double mortgage = (currentPrice * 0.051) / 12;
   printf("The estimated monthly mortgage is $%lf.\n", mortgage);
   return 0;
}