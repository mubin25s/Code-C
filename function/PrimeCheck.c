#include <stdio.h>

// Function declaration
int isPrime(int n);

int main() {
    int n;
    
    printf("Enter a positive integer: ");
    scanf("%d", &n);

    // Function call
    if (isPrime(n))
        printf("%d is a prime number.\n", n);
    else
        printf("%d is not a prime number.\n", n);

    return 0;
}

// Function definition
int isPrime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i <= n / 2; ++i) {
        if (n % i == 0) return 0;
    }
    return 1;
}
