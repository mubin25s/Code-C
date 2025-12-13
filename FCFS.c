#include<stdio.h>
int main(){
    int n, at[10],bt[20], wt[20], tat[20], i,j;


         printf("Enter the number of process");
         scanf("%d", &n);
   printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(at[j] > at[j+1]) {

                temp = at[j];
                at[j] = at[j+1];
                at[j+1] = temp;

                temp = bt[j];
                bt[j] = bt[j+1];
                bt[j+1] = temp;


                temp = pid[j];
                pid[j] = pid[j+1];
                pid[j+1] = temp;
            }
        }
    }


printf("")










return 0;
}
