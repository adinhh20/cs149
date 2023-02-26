#include <stdio.h>

/* Define your function here */
double LapsToMiles(double userLaps) {
   double miles = 0.25;
   double lapsToMiles;

   lapsToMiles = userLaps * miles;
   return lapsToMiles;
}


int main(void) {

   /* Type your code here. Your code must call the function.  */
   double yourLaps;
   scanf("%lf", &yourLaps);
   double yourValue = LapsToMiles(yourLaps);
   printf("%0.2lf\n", yourValue);

   return 0;
}
