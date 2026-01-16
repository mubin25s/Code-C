#include <stdio.h>
#define MAX 100

int heap[MAX];
int size = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insert(int value) {
    if (size == MAX) {
        printf("Queue Overflow\n");
        return;
    }
    heap[size] = value;
    int i = size;
    size++;

    while (i != 0 && heap[(i - 1) / 2] < heap[i]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void heapify(int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left] > heap[largest])
        largest = left;
    if (right < size && heap[right] > heap[largest])
        largest = right;

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        heapify(largest);
    }
}

int extractMax() {
    if (size <= 0) return -1;
    if (size == 1) {
        size--;
        return heap[0];
    }

    int root = heap[0];
    heap[0] = heap[size - 1];
    size--;
    heapify(0);

    return root;
}

int main() {
    insert(10);
    insert(30);
    insert(20);
    insert(5);
    insert(40);

    printf("Extracted Max: %d\n", extractMax());
    printf("Extracted Max: %d\n", extractMax());

    return 0;
}
