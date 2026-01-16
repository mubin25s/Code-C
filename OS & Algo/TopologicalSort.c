#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int adj[MAX][MAX];
int visited[MAX];
int stack[MAX];
int top = -1;
int n;

void addEdge(int u, int v) {
    adj[u][v] = 1;
}

void topologicalSortUtil(int v) {
    visited[v] = 1;
    for (int i = 0; i < n; i++) {
        if (adj[v][i] && !visited[i]) {
            topologicalSortUtil(i);
        }
    }
    stack[++top] = v;
}

void topologicalSort() {
    for (int i = 0; i < n; i++)
        if (!visited[i])
            topologicalSortUtil(i);

    while (top >= 0) {
        printf("%d ", stack[top--]);
    }
}

int main() {
    n = 6;
    addEdge(5, 2);
    addEdge(5, 0);
    addEdge(4, 0);
    addEdge(4, 1);
    addEdge(2, 3);
    addEdge(3, 1);

    printf("Topological Sort results: ");
    topologicalSort();
    return 0;
}
