<<<<<<< HEAD
#include <stdio.h>

int main() {
    int n, i;
    unsigned long long factorial = 1;
    
    printf("Enter an integer: ");
    scanf("%d", &n);
    
    // show error if the user enters a negative integer
    if (n < 0)
        printf("Error! Factorial of a negative number doesn't exist.");
    else {
        for (i = 1; i <= n; ++i) {
            factorial *= i;
        }
        printf("Factorial of %d = %llu\n", n, factorial);
    }
    
    return 0;
}
=======
#include <stdio.h>

int main() {
    int n, i;
    unsigned long long factorial = 1;
    
    printf("Enter an integer: ");
    scanf("%d", &n);
    
    // show error if the user enters a negative integer
    if (n < 0)
        printf("Error! Factorial of a negative number doesn't exist.");
    else {
        for (i = 1; i <= n; ++i) {
            factorial *= i;
        }
        printf("Factorial of %d = %llu\n", n, factorial);
    }
    
    return 0;
}
>>>>>>> d7eb2636aed7dfa5b0b36ab38f4c73756a198456
