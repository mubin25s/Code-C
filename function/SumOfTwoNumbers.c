#include <stdio.h>

// Function declaration
int add(int a, int b);

int main() {
    int num1, num2, sum;
    
    printf("Enter first number: ");
    scanf("%d", &num1);
    
    printf("Enter second number: ");
    scanf("%d", &num2);
    
    // Function call
    sum = add(num1, num2);
    
    printf("Sum: %d\n", sum);
    
    return 0;
}

// Function definition
int add(int a, int b) {
    return a + b;
}
