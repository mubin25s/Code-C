#include <stdio.h>
#include <math.h>

int main() {
    int start, end, i, num, originalNum, remainder, n, result;

    printf("Enter start and end of interval: ");
    if (scanf("%d %d", &start, &end) != 2) {
         printf("Invalid input.\n");
         return 1;
    }

    printf("Armstrong numbers between %d and %d are: ", start, end);

    for (i = start; i <= end; ++i) {
        originalNum = i;
        
        n = 0;
        int temp = i;
        while (temp != 0) {
            temp /= 10;
            ++n;
        }

        originalNum = i;
        result = 0;

        while (originalNum != 0) {
            remainder = originalNum % 10;
            
            int power_val = 1;
            for(int k=0; k<n; k++) power_val *= remainder;
            
            result += power_val;
            originalNum /= 10;
        }

        if (result == i) {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}
