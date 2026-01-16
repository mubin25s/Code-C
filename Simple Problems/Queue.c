#include <stdio.h>
#define MAX 10

int queue[MAX];
int front = 0, rear = -1;

void enqueue(int data) {
    if (rear == MAX - 1) printf("Queue Overflow\n");
    else queue[++rear] = data;
}

int dequeue() {
    if (front > rear) return -1;
    return queue[front++];
}

void display() {
    for (int i = front; i <= rear; i++) printf("%d ", queue[i]);
    printf("\n");
}

int main() {
    enqueue(1); enqueue(2); enqueue(3);
    printf("Queue: "); display();
    printf("Dequeued: %d\n", dequeue());
    return 0;
}
