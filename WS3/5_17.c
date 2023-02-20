#include <stdio.h>

int main(void) {
    const int NUM_ELEMENTS = 9;
    int userValues[NUM_ELEMENTS];    // Set of data specified by the user

    int i = 0;
    int input = 0;

    scanf("%d", &input);
    while(input>0){
        userValues[i++] = input;
        scanf("%d",&input);

    }
    if(i> NUM_ELEMENTS){
        printf("Too many numbers\n");
        return 0;
    }

    printf("Middle item: %d\n",userValues[i/2]);
    return 0;

}
