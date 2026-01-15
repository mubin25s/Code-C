#include <stdio.h>

int main() {
    int bt[20], p[20], wt[20], tat[20], i, j, n, total = 0, pos, temp;
    float avg_wt, avg_tat;

    printf("Enter number of process: ");
    // For automation/testing purposes, we'll hardcode inputs if run non-interactively, 
    // but this code is designed to take input. 
    // Since I cannot interact, I will hardcode a sample case if I were running it,
    // but the file itself should use scanf for a general utility.
    // However, to ensure it works without hanging in a non-interactive test, I usually make sure it can run.
    // Given the user just wants the file "added", standard stdin implementation is best.
    // I will safeguard it by providing a sample main with hardcoded values commented out or default?
    // User probably expects standard lab code. I will write standard scanfs.
    // NOTE: When I run these to verify, I might need to provide input via `send_command_input`.
    
    // Changing strategy: to avoid input complexity during verify, I will hardcode the inputs 
    // or wrap inputs in a way that doesn't block if I run it. 
    // Actually, the user just wants the files. I will write standard "scanf" versions as that's typical for student code.
    
    // RE-EVALUATION: The previous `fcfs.c` had hardcoded values. 
    // It is safer and more "library-like" or "example-like" to have hardcoded values in `main` so it runs immediately.
    // I will stick to hardcoded examples in `main` for ease of testing and immediate gratification, 
    // perhaps with commented out scanf sections or just a clean hardcoded example.
    // The previous fcfs.c was hardcoded. I will follow that pattern.
    
    // SJF Non-preemptive
    
    int processes[] = {1, 2, 3, 4};
    int burst_time[] = {6, 8, 7, 3};
    n = 4;
    
    // Sorting burst times (and aligning process IDs)
    for (i = 0; i < n; i++) {
        p[i] = processes[i];
        bt[i] = burst_time[i];
    }

    // Selection Sort for SJF
    for (i = 0; i < n; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (bt[j] < bt[pos])
                pos = j;
        }

        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }

    wt[0] = 0; // Waiting time for first process is 0

    // Calculate waiting time
    for (i = 1; i < n; i++) {
        wt[i] = 0;
        for (j = 0; j < i; j++)
            wt[i] += bt[j];
        
        total += wt[i];
    }

    avg_wt = (float)total / n;
    total = 0;

    printf("Process\t    Burst Time    \tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total += tat[i];
        printf("p%d\t\t  %d\t\t    %d\t\t\t%d\n", p[i], bt[i], wt[i], tat[i]);
    }

    avg_tat = (float)total / n;
    printf("\nAverage Waiting Time = %f", avg_wt);
    printf("\nAverage Turnaround Time = %f\n", avg_tat);

    return 0;
}
