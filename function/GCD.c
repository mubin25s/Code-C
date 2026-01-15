#include <stdio.h>

int findGCD(int n1, int n2);

int main() {
    int n1, n2;
    printf("Enter two positive integers: ");
    scanf("%d %d", &n1, &n2);
    printf("G.C.D of %d and %d is %d.\n", n1, n2, findGCD(n1, n2));
    return 0;
}

int findGCD(int n1, int n2) {
    while (n1 != n2) {
        if (n1 > n2)
            n1 -= n2;
        else
            n2 -= n1;
    }
    return n1;
}
