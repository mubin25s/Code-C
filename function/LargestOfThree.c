#include <stdio.h>

// Function declaration
double findLargest(double n1, double n2, double n3);

int main() {
    double n1, n2, n3;

    printf("Enter three base numbers: ");
    scanf("%lf %lf %lf", &n1, &n2, &n3);

    // Function call
    printf("%.2f is the largest number.", findLargest(n1, n2, n3));

    return 0;
}

// Function definition
double findLargest(double n1, double n2, double n3) {
    if (n1 >= n2 && n1 >= n3)
        return n1;
    else if (n2 >= n1 && n2 >= n3)
        return n2;
    else
        return n3;
}
