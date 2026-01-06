#include <stdio.h>

// Function declaration
void printFibonacci(int n);

int main() {
    int n;

    printf("Enter the number of terms: ");
    scanf("%d", &n);

    // Function call
    printFibonacci(n);

    return 0;
}

// Function definition
void printFibonacci(int n) {
    int t1 = 0, t2 = 1, nextTerm;

    printf("Fibonacci Series: ");
    for (int i = 1; i <= n; ++i) {
        printf("%d, ", t1);
        nextTerm = t1 + t2;
        t1 = t2;
        t2 = nextTerm;
    }
    printf("\n");
}
