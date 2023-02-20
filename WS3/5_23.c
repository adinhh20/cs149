#include <stdio.h>
#include <limits.h>

int main(void) {
  int arr[20];
  int num1 = INT_MAX;
  int num2 = INT_MAX;

  int len;
  scanf("%d", &len);
  for (int i = 0; i < len; i++){
    scanf("%d", &arr[i]);
  }

  for (int i = 0; i < len; i++){

    if (arr[i] < num1){
      num2 = num1;
      num1 = arr[i];
    }else if (arr[i] < num2 && arr[i] != num1){
      num2 = arr[i];
    }
  }

  printf("%d and %d\n", num1, num2);

  return 0;
}