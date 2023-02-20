#include <stdio.h>

int main(void) {

    /* Type your code here. */
    int num1, num2, num3, min;

    scanf("%d", &num1);
    scanf("%d", &num2);
    scanf("%d", &num3);
    if ((num1 < num2) && (num1 < num3)) min = num1;
    else if ((num1 > num2) && (num2 < num3)) min = num2;
    else if ((num3 < num2) && (num1 > num3)) min = num3;
    else if ((num1 = num2) && (num1 < num3)) min = num1;
    else if ((num1 = num3) && (num1 < num2)) min = num1;
    else min = num1;

    printf("%d\n", min);

    return 0;
}
