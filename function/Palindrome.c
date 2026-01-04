#include <stdio.h>

int checkPalindrome(int number);

int main() {
    int number;
    printf("Enter a positive integer: ");
    scanf("%d", &number);

    if (checkPalindrome(number) == 1)
        printf("%d is a palindrome.\n", number);
    else
        printf("%d is not a palindrome.\n", number);

    return 0;
}

int checkPalindrome(int number) {
    int temp, remainder, sum = 0;
    temp = number;

    while (number != 0) {
        remainder = number % 10;
        sum = sum * 10 + remainder;
        number /= 10;
    }

    if (temp == sum)
        return 1;
    else
        return 0;
}
