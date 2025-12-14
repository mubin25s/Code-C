#include<stdio.h>
void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int temp = arr[i];
        int j = i - 1;
   while (arr[j] < temp && j >= 0)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}
int main (){
 int n;
 printf("Enter Size Of the Array:");
 scanf("%d", &n);
 int arr[n];

 for (int i=0; i<n; i++){

 printf("A[%d]: ", i);
        scanf("%d", &arr[i]);
    }

 printf("Original Array:");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

   insertionSort(arr, n);
    printf("\nSorted Array in ascending:");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

}
