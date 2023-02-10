#include <stdio.h>

int main(void) {
    double x;
    double y;
    double z;

    /* Type your code here. Note: Include the math library above first. */
    scanf("%lf", &x);
    scanf("%lf", &y);
    scanf("%lf", &z);

    double value = pow(x, z);
    printf("%0.2lf ", value);
    value = pow(x, (pow(y, 2)));
    printf("%0.2lf ", value);
    value = fabs(y);
    printf("%0.2lf ", value);
    value = sqrt(pow((x*y), z));
    printf("%0.2lf\n", value);

    return 0;
}

