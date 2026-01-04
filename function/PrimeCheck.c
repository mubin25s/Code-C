#include <stdio.h>

int checkPrime(int n);

int main() {
    int n, flag;
    printf("Enter a positive integer: ");
    scanf("%d", &n);

    // checkPrime() returns 1 if n is prime, 0 otherwise
    flag = checkPrime(n);

    if (flag == 1)
        printf("%d is a prime number.\n", n);
    else
        printf("%d is not a prime number.\n", n);

    return 0;
}

int checkPrime(int n) {
    int i;
    if (n == 0 || n == 1)
        return 0;
    
    for (i = 2; i <= n / 2; ++i) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}
