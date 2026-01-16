#include <stdio.h>
#define MAX 5

int deque[MAX];
int front = -1;
int rear = -1;

void insertFront(int key) {
    if ((front == 0 && rear == MAX - 1) || (front == rear + 1)) {
        printf("Overflow\n");
        return;
    }
    if (front == -1) {
        front = 0; rear = 0;
    } else if (front == 0)
        front = MAX - 1;
    else
        front = front - 1;
    deque[front] = key;
}

void insertRear(int key) {
    if ((front == 0 && rear == MAX - 1) || (front == rear + 1)) {
        printf("Overflow\n");
        return;
    }
    if (front == -1) {
        front = 0; rear = 0;
    } else if (rear == MAX - 1)
        rear = 0;
    else
        rear = rear + 1;
    deque[rear] = key;
}

void deleteFront() {
    if (front == -1) {
        printf("Underflow\n");
        return;
    }
    if (front == rear) {
        front = -1; rear = -1;
    } else if (front == MAX - 1)
        front = 0;
    else
        front = front + 1;
}

void deleteRear() {
    if (front == -1) {
        printf("Underflow\n");
        return;
    }
    if (front == rear) {
        front = -1; rear = -1;
    } else if (rear == 0)
        rear = MAX - 1;
    else
        rear = rear - 1;
}

int getFront() {
    if (front == -1) return -1;
    return deque[front];
}

int getRear() {
    if (front == -1 || rear == -1) return -1;
    return deque[rear];
}

int main() {
    insertRear(5);
    insertRear(10);
    insertFront(15);
    printf("Front: %d, Rear: %d\n", getFront(), getRear());
    deleteFront();
    printf("After delete front, Front: %d\n", getFront());
    return 0;
}
