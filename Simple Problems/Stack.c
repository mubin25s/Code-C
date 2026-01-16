#include <stdio.h>
#define MAX 10

int stack[MAX];
int top = -1;

void push(int data) {
    if (top == MAX - 1) printf("Stack Overflow\n");
    else stack[++top] = data;
}

int pop() {
    if (top == -1) return -1;
    return stack[top--];
}

void display() {
    for (int i = top; i >= 0; i--) printf("%d ", stack[i]);
    printf("\n");
}

int main() {
    push(1); push(2); push(3);
    printf("Stack: "); display();
    printf("Popped: %d\n", pop());
    return 0;
}
