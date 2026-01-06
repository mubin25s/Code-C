#include <stdio.h>

// Function declaration
unsigned long long factorial(int n);

int main() {
    int n;
    
    printf("Enter an integer: ");
    scanf("%d", &n);
    
    if (n < 0)
        printf("Error! Factorial of a negative number doesn't exist.");
    else {
        // Function call
        printf("Factorial of %d = %llu\n", n, factorial(n));
    }
    
    return 0;
}

// Function definition
unsigned long long factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}
