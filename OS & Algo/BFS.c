#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adj[MAX][MAX];
int visited[MAX];
int queue[MAX];
int front = -1, rear = -1;
int n;

void enqueue(int item) {
    if (rear == MAX - 1) return;
    if (front == -1) front = 0;
    queue[++rear] = item;
}

int dequeue() {
    if (front == -1 || front > rear) return -1;
    return queue[front++];
}

void BFS(int start) {
    enqueue(start);
    visited[start] = 1;
    while (front <= rear && front != -1) {
        int v = dequeue();
        printf("%d ", v);
        for (int i = 0; i < n; i++) {
            if (adj[v][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
}

int main() {
    n = 4;
    adj[0][1] = 1; adj[0][2] = 1;
    adj[1][2] = 1;
    adj[2][0] = 1; adj[2][3] = 1;
    adj[3][3] = 1;

    printf("BFS starting from vertex 2:\n");
    BFS(2);
    return 0;
}
