#include <stdio.h>

int main() {
    unsigned char num;
    printf("Enter a number (0-255): ");
    scanf("%hhu", &num);

    printf("Original Number: %d\n", num);
    
    printf("Binary: ");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i == 4) printf(" ");
    }
    printf("\n");

    unsigned char swapped = ((num & 0x0F) << 4) | ((num & 0xF0) >> 4);

    printf("Swapped Number : %d\n", swapped);
    printf("Binary: ");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (swapped >> i) & 1);
        if (i == 4) printf(" ");
    }
    printf("\n");

    return 0;
}
