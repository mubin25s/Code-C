#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, j, t;
    
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size.\n");
        return 1;
    }

    int *arr = (int*) malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", arr + i);
    }

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (*(arr + j) < *(arr + i)) {
                t = *(arr + i);
                *(arr + i) = *(arr + j);
                *(arr + j) = t;
            }
        }
    }

    printf("Sorted list in ascending order:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");

    free(arr);
    return 0;
}
