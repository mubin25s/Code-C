<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pet {
    int id;
    char name[50];
    char breed[50];
    int age;
    float price;
};

const char *PET_FILENAME = "pet_shop_data.txt";

void addPet();
void displayPets();
void buyPet();
void petMenu();

int main() {
    petMenu();
    return 0;
}

void petMenu() {
    int choice;
    while(1) {
        printf("\n=== Pet Shop Management System ===\n");
        printf("1. Add New Pet\n");
        printf("2. Display All Pets\n");
        printf("3. Buy a Pet\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            choice = 0;
        }
        getchar();

        switch(choice) {
            case 1: addPet(); break;
            case 2: displayPets(); break;
            case 3: buyPet(); break;
            case 4: 
                printf("Exiting Pet Shop... Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void addPet() {
    struct Pet p;
    FILE *fp = fopen(PET_FILENAME, "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Pet ID: ");
    scanf("%d", &p.id);
    getchar();

    printf("Enter Pet Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0;

    printf("Enter Breed: ");
    fgets(p.breed, sizeof(p.breed), stdin);
    p.breed[strcspn(p.breed, "\n")] = 0;

    printf("Enter Age: ");
    scanf("%d", &p.age);

    printf("Enter Price: ");
    scanf("%f", &p.price);

    fwrite(&p, sizeof(struct Pet), 1, fp);
    printf("Pet added successfully!\n");

    fclose(fp);
}

void displayPets() {
    struct Pet p;
    FILE *fp = fopen(PET_FILENAME, "rb");
    if (fp == NULL) {
        printf("\nNo pets available yet.\n");
        return;
    }

    printf("\n%-5s %-20s %-20s %-5s %s\n", "ID", "Name", "Breed", "Age", "Price");
    printf("----------------------------------------------------------------\n");

    while(fread(&p, sizeof(struct Pet), 1, fp)) {
        printf("%-5d %-20s %-20s %-5d %.2f\n", p.id, p.name, p.breed, p.age, p.price);
    }

    fclose(fp);
}

void buyPet() {
    struct Pet p;
    FILE *fp = fopen(PET_FILENAME, "rb");
    FILE *tempFp = fopen("temp_pets.txt", "wb");
    int id, found = 0;

    if (fp == NULL) {
        printf("\nNo pets available to buy.\n");
        return;
    }
    if (tempFp == NULL) {
        printf("\nError processing purchase.\n");
        fclose(fp);
        return;
    }

    printf("\nEnter Pet ID to buy: ");
    scanf("%d", &id);

    while(fread(&p, sizeof(struct Pet), 1, fp)) {
        if(p.id == id) {
            found = 1;
            printf("\nCongratulations! You bought %s (%s) for $%.2f\n", p.name, p.breed, p.price);
        } else {
            fwrite(&p, sizeof(struct Pet), 1, tempFp);
        }
    }

    fclose(fp);
    fclose(tempFp);

    remove(PET_FILENAME);
    rename("temp_pets.txt", PET_FILENAME);

    if(!found) {
        printf("\nPet not found with ID %d.\n", id);
    }
}
=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pet {
    int id;
    char name[50];
    char breed[50];
    int age;
    float price;
};

const char *PET_FILENAME = "pet_shop_data.txt";

void addPet();
void displayPets();
void buyPet();
void petMenu();

int main() {
    petMenu();
    return 0;
}

void petMenu() {
    int choice;
    while(1) {
        printf("\n=== Pet Shop Management System ===\n");
        printf("1. Add New Pet\n");
        printf("2. Display All Pets\n");
        printf("3. Buy a Pet\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            choice = 0;
        }
        getchar();

        switch(choice) {
            case 1: addPet(); break;
            case 2: displayPets(); break;
            case 3: buyPet(); break;
            case 4: 
                printf("Exiting Pet Shop... Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void addPet() {
    struct Pet p;
    FILE *fp = fopen(PET_FILENAME, "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Pet ID: ");
    scanf("%d", &p.id);
    getchar();

    printf("Enter Pet Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0;

    printf("Enter Breed: ");
    fgets(p.breed, sizeof(p.breed), stdin);
    p.breed[strcspn(p.breed, "\n")] = 0;

    printf("Enter Age: ");
    scanf("%d", &p.age);

    printf("Enter Price: ");
    scanf("%f", &p.price);

    fwrite(&p, sizeof(struct Pet), 1, fp);
    printf("Pet added successfully!\n");

    fclose(fp);
}

void displayPets() {
    struct Pet p;
    FILE *fp = fopen(PET_FILENAME, "rb");
    if (fp == NULL) {
        printf("\nNo pets available yet.\n");
        return;
    }

    printf("\n%-5s %-20s %-20s %-5s %s\n", "ID", "Name", "Breed", "Age", "Price");
    printf("----------------------------------------------------------------\n");

    while(fread(&p, sizeof(struct Pet), 1, fp)) {
        printf("%-5d %-20s %-20s %-5d %.2f\n", p.id, p.name, p.breed, p.age, p.price);
    }

    fclose(fp);
}

void buyPet() {
    struct Pet p;
    FILE *fp = fopen(PET_FILENAME, "rb");
    FILE *tempFp = fopen("temp_pets.txt", "wb");
    int id, found = 0;

    if (fp == NULL) {
        printf("\nNo pets available to buy.\n");
        return;
    }
    if (tempFp == NULL) {
        printf("\nError processing purchase.\n");
        fclose(fp);
        return;
    }

    printf("\nEnter Pet ID to buy: ");
    scanf("%d", &id);

    while(fread(&p, sizeof(struct Pet), 1, fp)) {
        if(p.id == id) {
            found = 1;
            printf("\nCongratulations! You bought %s (%s) for $%.2f\n", p.name, p.breed, p.price);
        } else {
            fwrite(&p, sizeof(struct Pet), 1, tempFp);
        }
    }

    fclose(fp);
    fclose(tempFp);

    remove(PET_FILENAME);
    rename("temp_pets.txt", PET_FILENAME);

    if(!found) {
        printf("\nPet not found with ID %d.\n", id);
    }
}
>>>>>>> da39c685085797a14e004aa3c962df02b596d6ae
