#include <stdio.h>

double power(double base, int exponent);

int main() {
    double base, result;
    int exponent;
    printf("Enter base: ");
    scanf("%lf", &base);
    printf("Enter exponent: ");
    scanf("%d", &exponent);
    
    result = power(base, exponent);
    printf("%.2lf^%d = %.2lf", base, exponent, result);
    return 0;
}

double power(double base, int exponent) {
    if (exponent == 0)
        return 1;
    if (exponent > 0)
        return base * power(base, exponent - 1);
    else
        return 1 / power(base, -exponent);
}
