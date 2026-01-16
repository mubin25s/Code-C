#include <stdio.h>
#define MAX 100

int stack[MAX];
int top = -1;

void push(int x) {
    if (top >= MAX - 1) {
        printf("Stack Overflow\n");
    } else {
        stack[++top] = x;
        printf("%d pushed into stack\n", x);
    }
}

int pop() {
    if (top < 0) {
        printf("Stack Underflow\n");
        return 0;
    } else {
        return stack[top--];
    }
}

int peek() {
    if (top < 0) {
        printf("Stack is Empty\n");
        return 0;
    } else {
        return stack[top];
    }
}

int isEmpty() {
    return top < 0;
}

int main() {
    push(10);
    push(20);
    push(30);
    printf("%d popped from stack\n", pop());
    printf("Top element is %d\n", peek());
    printf("Stack is empty: %d\n", isEmpty());
    return 0;
}
