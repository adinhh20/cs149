#include <stdio.h>
#include <string.h>

int main(void) {
  const int NUM_ELEMENTS = 20;
  char userValue[NUM_ELEMENTS][20];
  char searchCharacter;

  int len;
  scanf("%d", &len);

  for (int i = 0; i < len; i++){
    scanf("%s", userValue[i]);
  }

  scanf(" %c", &searchCharacter);

  for (int i = 0; i < len; i++){
    if (strchr(userValue[i], searchCharacter) != NULL){
      printf("%s,", userValue[i]);
    }
  }
  printf("\n");
  return 0;
}