#include <stdio.h>

int findLCM(int n1, int n2);

int main() {
    int n1, n2;
    printf("Enter two positive integers: ");
    scanf("%d %d", &n1, &n2);
    printf("LCM of %d and %d is %d.\n", n1, n2, findLCM(n1, n2));
    return 0;
}

int findLCM(int n1, int n2) {
    int max;
    max = (n1 > n2) ? n1 : n2;

    while (1) {
        if (max % n1 == 0 && max % n2 == 0) {
            return max;
        }
        ++max;
    }
}
