#include <stdio.h>

void swap(int *a, int *b);

int main() {
    int n1, n2;
    printf("Enter two integers: ");
    scanf("%d %d", &n1, &n2);

    printf("Before swapping: n1 = %d, n2 = %d\n", n1, n2);
    swap(&n1, &n2);
    printf("After swapping: n1 = %d, n2 = %d\n", n1, n2);

    return 0;
}

void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
