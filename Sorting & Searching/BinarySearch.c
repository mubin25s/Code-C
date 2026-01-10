#include <stdio.h>

int main() {
    int n, x, l, r, m, found = -1;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers in SORTED order:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        if(i > 0 && arr[i] < arr[i-1]) {
             printf("Warning: Not sorted! Binary search might fail.\n");
        }
    }

    printf("Enter element to search: ");
    scanf("%d", &x);

    l = 0;
    r = n - 1;
    
    while (l <= r) {
        m = l + (r - l) / 2;

        if (arr[m] == x) {
            found = m;
            break;
        }

        if (arr[m] < x)
            l = m + 1;
        else
            r = m - 1;
    }

    if (found == -1)
        printf("Element is not present in array.\n");
    else
        printf("Element is present at index %d.\n", found);

    return 0;
}
