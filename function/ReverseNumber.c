<<<<<<< HEAD
#include <stdio.h>

int reverseNumber(int n);

int main() {
    int n;
    printf("Enter an integer: ");
    scanf("%d", &n);
    printf("Reverse of %d is %d\n", n, reverseNumber(n));
    return 0;
}

int reverseNumber(int n) {
    int reverse = 0, remainder;
    while (n != 0) {
        remainder = n % 10;
        reverse = reverse * 10 + remainder;
        n /= 10;
    }
    return reverse;
}
=======
#include <stdio.h>

int reverseNumber(int n);

int main() {
    int n;
    printf("Enter an integer: ");
    scanf("%d", &n);
    printf("Reverse of %d is %d\n", n, reverseNumber(n));
    return 0;
}

int reverseNumber(int n) {
    int reverse = 0, remainder;
    while (n != 0) {
        remainder = n % 10;
        reverse = reverse * 10 + remainder;
        n /= 10;
    }
    return reverse;
}
>>>>>>> 87face3e14e39afd553f772cb15b80a79725efba
