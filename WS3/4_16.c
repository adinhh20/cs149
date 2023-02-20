#include <stdio.h>

int main(void) {
    int input = 0;
    float count = 0;
    int max = -1;
    int total = 0;

    scanf("%d", &input);
    while (input >= 0) {
        count++;
        total += input;
        if (input > max) max = input;
        scanf("%d", &input);
    }

    printf("%d " , max);
    printf("%0.2lf\n", total/count);
}