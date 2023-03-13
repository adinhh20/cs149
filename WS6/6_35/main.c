/*
**
 * Description: Worksheeet 6
 * Author name: Vivian Letran & Anh Dinh
 * Author email: vivian.letran@sjsu.edu & anh.dinh@sjsu.edu
 * Last modified date: 3-12-2023
 * Creation date: 3-11-2023
 **/

#include <stdio.h>

void SortArray(int sortingList[], int numVals);
void swap(int * i, int * y);

int main(void) {
   //array contains less that 20 character
   int arr[20];

   //scan input
   int length;
   scanf("%d",&length);
   for(int i =0;i<length;i++){
      scanf("%d",&arr[i]);
   }
   SortArray(arr,length);
   //print output
   for(int i =0;i<length;i++){
      printf("%d,",arr[i]);
   }
   printf("\n");
   return 0;
}
   //sort
   void SortArray(int sortingList[], int numVals){
      for(int i =0;i<numVals;i++){
          int min = i;
          for(int j = i+1; j<numVals; j++){
               if(sortingList[j] > sortingList[min]){
                     min = j;
                  }
               }
               swap(&sortingList[min],&sortingList[i]);
            }
         }
   //swap items in array
   void swap(int * x, int * y){
      int temp = *x;
      *x =*y;
      *y = temp;
   }


