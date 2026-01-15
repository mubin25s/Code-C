#include <stdio.h>

int sumOfDigits(int n);

int main() {
    int num;
    printf("Enter an integer: ");
    scanf("%d", &num);
    printf("Sum of digits of %d is %d\n", num, sumOfDigits(num));
    return 0;
}

int sumOfDigits(int n) {
    int sum = 0;
    if (n < 0) n = -n; 
    
    while (n != 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}
