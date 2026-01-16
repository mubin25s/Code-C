#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adj[MAX][MAX];
int visited[MAX];
int n;

void DFS(int v) {
    printf("%d ", v);
    visited[v] = 1;
    for (int i = 0; i < n; i++) {
        if (adj[v][i] == 1 && !visited[i]) {
            DFS(i);
        }
    }
}

int main() {
    n = 4; // Number of vertices
    adj[0][1] = 1; adj[0][2] = 1;
    adj[1][2] = 1;
    adj[2][0] = 1; adj[2][3] = 1;
    adj[3][3] = 1;

    printf("DFS starting from vertex 2:\n");
    DFS(2);
    return 0;
}
