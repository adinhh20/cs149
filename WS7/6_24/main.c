/**
 * Author: Vivian Letran & Anh Dinh
 * Email: vivian.letran@sjsu.edu & anh.dinh@sjsu.edu
 * Date Created 03/15/23
 * Last Modified Date 03/15/23
 **/
#include <stdio.h>

void SwapValues(int* userVal1, int* userVal2, int* userVal3, int* userVal4);

int main(void) {
   int val1,val2,val3,val4;
   scanf("%d %d %d %d", &val1, &val2, &val3, &val4);
   SwapValues(&val1,&val2,&val3, &val4);
   printf("%d %d %d %d\n", val1, val2,val3,val4);

   return 0;
}
void SwapValues(int* userVal1, int* userVal2, int* userVal3, int* userVal4){
   int temp = *userVal1;
   *userVal1 = *userVal2;
   *userVal2 = temp;
   int temp2 = *userVal3;
   *userVal3 = *userVal4;
   *userVal4 = temp2;
   }