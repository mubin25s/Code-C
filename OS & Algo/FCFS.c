#include<stdio.h>
int main()
{
    int n, i, j;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n];
    float totalTAT = 0, totalWT = 0;

    for(i=0; i<n; i++)
    {
        pid[i] = i+1;
        printf("Enter arrival time for process %d: ", i+1);
        scanf("%d", &at[i]);
        printf("Enter burst time for process %d: ", i+1);
        scanf("%d", &bt[i]);
    }

    for (i=0; i<n-1; i++)
    {
        for (j=0; j<n-i-1; j++)
        {
            if (at[j] > at[j+1])
            {
                int temp = at[j];
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

    int current_time = 0;
    for(i=0; i<n; i++)
    {
        if(current_time < at[i])
        {
            current_time = at[i];
        }
        ct[i] = current_time + bt[i];
        current_time = ct[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        totalTAT += tat[i];
        totalWT += wt[i];
    }

    printf("\nPID\tArrival\tBurst\tComplete\tTurnaround\tWaiting\n");
    for(i=0; i<n; i++)
    {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWT/n);
    printf("Average Turnaround Time = %.2f\n", totalTAT/n);

    return 0;
}
