<<<<<<< HEAD
#include <stdio.h>

int findMax(int arr[], int n);

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n];
    
    printf("Enter %d integers: ", n);
    for(int i=0; i<n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Largest element is %d\n", findMax(arr, n));
    return 0;
}

int findMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}
=======
#include <stdio.h>

int findMax(int arr[], int n);

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n];
    
    printf("Enter %d integers: ", n);
    for(int i=0; i<n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Largest element is %d\n", findMax(arr, n));
    return 0;
}

int findMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}
>>>>>>> 87face3e14e39afd553f772cb15b80a79725efba
