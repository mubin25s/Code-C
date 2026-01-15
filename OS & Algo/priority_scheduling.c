#include <stdio.h>

struct Process {
    int pid;      // Process ID
    int bt;       // Burst Time
    int priority; // Priority
};

void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform Priority Scheduling
void priorityScheduling(struct Process proc[], int n) {
    // Sort processes by priority (higher number = higher priority assumption usually varies, here we assume lower number = higher priority for standard sorting, 
    // but typical OS problems often imply higher number = high priority. Let's stick to simple "sort by priority value" where smaller value is executed first typically, 
    // or we can comment. Let's assume smaller integer = higher priority (1 is first)). 
    // Actually, often in OS, larger number is higher priority. 
    // I will stick to "Ascending order of priority value" -> Process check with Priority 1 runs before Priority 2.
    
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (proc[j].priority > proc[j + 1].priority) {
                swap(&proc[j], &proc[j + 1]);
            }
        }
    }

    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    // Waiting time for first process is 0
    wt[0] = 0;

    // Calculate waiting time
    for (i = 1; i < n; i++) {
        wt[i] = proc[i - 1].bt + wt[i - 1]; // This logic assumes sequential execution after sorting (Non-preemptive based on priority arrival at 0)
    }

    // Calculate turnaround time
    for (i = 0; i < n; i++) {
        tat[i] = proc[i].bt + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("Processes   Priority   Burst time   Waiting time   Turn around time\n");
    for (i = 0; i < n; i++) {
        printf(" %d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].priority, proc[i].bt, wt[i], tat[i]);
    }

    printf("\nAverage waiting time = %f", (float)total_wt / n);
    printf("\nAverage turn around time = %f\n", (float)total_tat / n);
}

int main() {
    struct Process proc[] = {{1, 10, 2}, {2, 5, 0}, {3, 8, 1}};
    int n = sizeof(proc) / sizeof(proc[0]);

    priorityScheduling(proc, n);
    return 0;
}
