#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void calculateSSTF(int request[], int n, int head) {
    int i, count = 0;
    int total_seek_time = 0;
    int visited[n];
    
    // Initialize visited array
    for (i = 0; i < n; i++) {
        visited[i] = 0;
    }
    
    printf("Sequence of execution:\n");
    printf("%d", head);
    
    while (count < n) {
        int min_dist = 1000000; // Large number
        int index = -1;
        
        // Find closest unvisited track
        for (i = 0; i < n; i++) {
            if (!visited[i]) {
                int dist = abs(head - request[i]);
                if (dist < min_dist) {
                    min_dist = dist;
                    index = i;
                }
            }
        }
        
        // Process the closest request
        if (index != -1) {
            visited[index] = 1;
            total_seek_time += min_dist;
            head = request[index];
            printf(" -> %d", head);
            count++;
        }
    }
    
    printf("\n\nTotal Seek Time: %d\n", total_seek_time);
    printf("Average Seek Time: %.2f\n", (float)total_seek_time / n);
}

int main() {
    int request[] = {176, 79, 34, 60, 92, 11, 41, 114};
    int n = sizeof(request) / sizeof(request[0]);
    int initial_head = 50;
    
    printf("Initial Head Position: %d\n", initial_head);
    printf("Requests: ");
    for(int i=0; i<n; i++) printf("%d ", request[i]);
    printf("\n\n");

    calculateSSTF(request, n, initial_head);
    
    return 0;
}
