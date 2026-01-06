#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold book information
struct Book {
    int id;
    char title[100];
    char author[100];
    char category[50];
    int quantity;
};

// Global file name
const char *FILENAME = "library_data.txt";

// Function prototypes
void addBook();
void viewBooks();
void searchBook();
void deleteBook();
void menu();

int main() {
    menu();
    return 0;
}

void menu() {
    int choice;
    while(1) {
        printf("\n=== Library Management System ===\n");
        printf("1. Add Book\n");
        printf("2. View All Books\n");
        printf("3. Search Book\n");
        printf("4. Delete Book\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            // clear input buffer if non-integer is entered
            while(getchar() != '\n');
            choice = 0; 
        }
        
        // consume newline character left by scanf
        getchar(); 

        switch(choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: 
                printf("Exiting... Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void addBook() {
    struct Book b;
    FILE *fp = fopen(FILENAME, "ab"); // Append mode (binary)
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Book ID: ");
    scanf("%d", &b.id);
    getchar(); // Consume newline

    printf("Enter Book Title: ");
    fgets(b.title, sizeof(b.title), stdin);
    b.title[strcspn(b.title, "\n")] = 0; // Remove newline

    printf("Enter Author Name: ");
    fgets(b.author, sizeof(b.author), stdin);
    b.author[strcspn(b.author, "\n")] = 0;

    printf("Enter Category: ");
    fgets(b.category, sizeof(b.category), stdin);
    b.category[strcspn(b.category, "\n")] = 0;

    printf("Enter Quantity: ");
    scanf("%d", &b.quantity);

    fwrite(&b, sizeof(struct Book), 1, fp);
    printf("Book added successfully!\n");

    fclose(fp);
}

void viewBooks() {
    struct Book b;
    FILE *fp = fopen(FILENAME, "rb"); // Read mode (binary)
    if (fp == NULL) {
        printf("\nNo records found (File doesn't exist yet).\n");
        return;
    }

    printf("\n%-5s %-30s %-20s %-15s %s\n", "ID", "Title", "Author", "Category", "Qty");
    printf("--------------------------------------------------------------------------------\n");

    while(fread(&b, sizeof(struct Book), 1, fp)) {
        printf("%-5d %-30s %-20s %-15s %d\n", b.id, b.title, b.author, b.category, b.quantity);
    }

    fclose(fp);
}

void searchBook() {
    struct Book b;
    FILE *fp = fopen(FILENAME, "rb");
    int id, found = 0;
    
    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    printf("\nEnter Book ID to search: ");
    scanf("%d", &id);

    while(fread(&b, sizeof(struct Book), 1, fp)) {
        if(b.id == id) {
            printf("\nBook Found!\n");
            printf("ID: %d\n", b.id);
            printf("Title: %s\n", b.title);
            printf("Author: %s\n", b.author);
            printf("Category: %s\n", b.category);
            printf("Quantity: %d\n", b.quantity);
            found = 1;
            break;
        }
    }
    
    if(!found) {
        printf("\nBook not found with ID %d\n", id);
    }

    fclose(fp);
}

void deleteBook() {
    struct Book b;
    FILE *fp = fopen(FILENAME, "rb");
    FILE *tempFp = fopen("temp.txt", "wb");
    int id, found = 0;

    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    if (tempFp == NULL) {
        printf("\nError creating temporary file.\n");
        fclose(fp);
        return;
    }

    printf("\nEnter Book ID to delete: ");
    scanf("%d", &id);

    while(fread(&b, sizeof(struct Book), 1, fp)) {
        if(b.id == id) {
            found = 1; // Book found, skip writing it to temp file
        } else {
            fwrite(&b, sizeof(struct Book), 1, tempFp); // Write other books
        }
    }

    fclose(fp);
    fclose(tempFp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if(found) {
        printf("\nBook deleted successfully.\n");
    } else {
        printf("\nBook not found with ID %d.\n", id);
    }
}
