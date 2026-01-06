#include <stdio.h>

// Function declaration
int isPalindrome(int n);

int main() {
    int n;
    
    printf("Enter an integer: ");
    scanf("%d", &n);

    // Function call
    if (isPalindrome(n))
        printf("%d is a palindrome.\n", n);
    else
        printf("%d is not a palindrome.\n", n);

    return 0;
}

// Function definition
int isPalindrome(int n) {
    int reversed = 0, remainder, original = n;
    
    while (n != 0) {
        remainder = n % 10;
        reversed = reversed * 10 + remainder;
        n /= 10;
    }
    
    return (original == reversed);
}
