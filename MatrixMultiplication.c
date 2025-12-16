#include <stdio.h>

#define MAX 10

int main() {
    int first[MAX][MAX], second[MAX][MAX], result[MAX][MAX];
    int r1, c1, r2, c2;
    int i, j, k;

    printf("Enter rows and columns for the first matrix: ");
    scanf("%d %d", &r1, &c1);
    
    printf("Enter rows and columns for the second matrix: ");
    scanf("%d %d", &r2, &c2);

    while (c1 != r2) {
        printf("Error! column of first matrix not equal to row of second.\n");
        printf("Enter rows and columns for the first matrix: ");
        scanf("%d %d", &r1, &c1);
        printf("Enter rows and columns for the second matrix: ");
        scanf("%d %d", &r2, &c2);
    }

    printf("Enter elements of matrix A:\n");
    for (i = 0; i < r1; ++i) {
        for (j = 0; j < c1; ++j) {
            printf("Enter element A%d%d: ", i + 1, j + 1);
            scanf("%d", &first[i][j]);
        }
    }

    printf("Enter elements of matrix B:\n");
    for (i = 0; i < r2; ++i) {
        for (j = 0; j < c2; ++j) {
            printf("Enter element B%d%d: ", i + 1, j + 1);
            scanf("%d", &second[i][j]);
        }
    }

    for (i = 0; i < r1; ++i) {
        for (j = 0; j < c2; ++j) {
            result[i][j] = 0;
        }
    }

    for (i = 0; i < r1; ++i) {
        for (j = 0; j < c2; ++j) {
            for (k = 0; k < c1; ++k) {
                result[i][j] += first[i][k] * second[k][j];
            }
        }
    }

    printf("\nOutput Matrix:\n");
    for (i = 0; i < r1; ++i) {
        for (j = 0; j < c2; ++j) {
            printf("%d  ", result[i][j]);
            if (j == c2 - 1)
                printf("\n");
        }
    }

    return 0;
}
