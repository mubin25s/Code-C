#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int main() {
    struct Node* head = NULL;
    struct Node* newNode;
    struct Node* temp;
    struct Node* prev;
    int choice, val;

    while (1) {
        printf("\n1. Insert at End\n2. Delete Value\n3. Display\n4. Exit\nEnter choice: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                newNode = (struct Node*)malloc(sizeof(struct Node));
                newNode->data = val;
                newNode->next = NULL;

                if (head == NULL) {
                    head = newNode;
                } else {
                    temp = head;
                    while (temp->next != NULL) {
                        temp = temp->next;
                    }
                    temp->next = newNode;
                }
                printf("Inserted %d.\n", val);
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                temp = head;
                prev = NULL;

                if (temp != NULL && temp->data == val) {
                    head = temp->next;
                    free(temp);
                    printf("Deleted %d.\n", val);
                } else {
                    while (temp != NULL && temp->data != val) {
                        prev = temp;
                        temp = temp->next;
                    }
                    if (temp == NULL) {
                        printf("Element %d not found.\n", val);
                    } else {
                        prev->next = temp->next;
                        free(temp);
                        printf("Deleted %d.\n", val);
                    }
                }
                break;

            case 3:
                printf("List: ");
                temp = head;
                while (temp != NULL) {
                    printf("%d -> ", temp->data);
                    temp = temp->next;
                }
                printf("NULL\n");
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
