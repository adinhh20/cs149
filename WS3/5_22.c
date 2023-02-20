#include <stdio.h>
int main(void) {
  int arr[20];


  int length;
  scanf("%d", &length);
  for (int i = 0; i < length; i++){
    scanf("%d", &arr[i]);
  }

  int min;
  int max;
  scanf("%d %d", &min, &max);


  for (int i = 0; i < length; i++){
    // check if number is within range
    if (arr[i] <= max && arr[i] >= min) {
      printf("%d,", arr[i]);
    }
  }
  printf("\n");
  return 0;
}