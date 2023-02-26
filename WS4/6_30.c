#include <stdio.h>

//function MaxNumber takes 4 ints and returns max of the four
int MaxNumber(int number1, int number2, int number3, int number4);
//function MinNumber takes 4 ints and returns min of the four
int MinNumber(int num1, int num2, int num3, int num4);
int main(void) {

    /* Type your code here. Your code must call the function.  */
    int num1,num2,num3,num4;
    scanf("%d %d %d %d", &num1, &num2, &num3, &num4);
    printf("Maximum is %d\n", MaxNumber(num1, num2, num3, num4));
    printf("Minimum is %d\n", MinNumber(num1, num2, num3, num4));


    return 0;
}
int MaxNumber(int number1, int number2, int number3, int number4){
    int max = number1;
    if(number2 > max){
        max = number2;
    }
    if(number3 > max){
        max = number3;
    }
    if(number4 > max){
        max = number4;
    }
    return max;
}

//Min
int MinNumber(int number1, int number2, int number3, int number4){
    int min = number1;
    if(number2 < min){
        min = number2;
    }
    if(number3 < min){
        min = number3;
    }
    if(number4 < min){
        min = number4;
    }
    return min;
}

