#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Flight {
    int id;
    char airline[50];
    char origin[50];
    char destination[50];
    int seats;
    float price;
};

const char *FLIGHT_FILENAME = "flight_data.txt";

void addFlight();
void displayFlights();
void bookFlight();
void cancelFlight();
void flightMenu();

int main() {
    flightMenu();
    return 0;
}

void flightMenu() {
    int choice;
    while(1) {
        printf("\n=== Flight Management System ===\n");
        printf("1. Add Flight\n");
        printf("2. Display All Flights\n");
        printf("3. Book a Flight\n");
        printf("4. Cancel Flight Booking\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            choice = 0;
        }
        getchar();

        switch(choice) {
            case 1: addFlight(); break;
            case 2: displayFlights(); break;
            case 3: bookFlight(); break;
            case 4: cancelFlight(); break;
            case 5: 
                printf("Exiting Flight Management System... Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void addFlight() {
    struct Flight f;
    FILE *fp = fopen(FLIGHT_FILENAME, "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Flight ID: ");
    scanf("%d", &f.id);
    getchar();

    printf("Enter Airline Name: ");
    fgets(f.airline, sizeof(f.airline), stdin);
    f.airline[strcspn(f.airline, "\n")] = 0;

    printf("Enter Origin: ");
    fgets(f.origin, sizeof(f.origin), stdin);
    f.origin[strcspn(f.origin, "\n")] = 0;

    printf("Enter Destination: ");
    fgets(f.destination, sizeof(f.destination), stdin);
    f.destination[strcspn(f.destination, "\n")] = 0;

    printf("Enter Total Seats: ");
    scanf("%d", &f.seats);

    printf("Enter Ticket Price: ");
    scanf("%f", &f.price);

    fwrite(&f, sizeof(struct Flight), 1, fp);
    printf("Flight added successfully!\n");

    fclose(fp);
}

void displayFlights() {
    struct Flight f;
    FILE *fp = fopen(FLIGHT_FILENAME, "rb");
    if (fp == NULL) {
        printf("\nNo flights available yet.\n");
        return;
    }

    printf("\n%-5s %-20s %-15s %-15s %-5s %s\n", "ID", "Airline", "Origin", "Destination", "Seats", "Price");
    printf("--------------------------------------------------------------------------------\n");

    while(fread(&f, sizeof(struct Flight), 1, fp)) {
        printf("%-5d %-20s %-15s %-15s %-5d %.2f\n", f.id, f.airline, f.origin, f.destination, f.seats, f.price);
    }

    fclose(fp);
}

void bookFlight() {
    struct Flight f;
    FILE *fp = fopen(FLIGHT_FILENAME, "rb");
    FILE *tempFp = fopen("temp_flights.txt", "wb");
    int id, found = 0;

    if (fp == NULL) {
        printf("\nNo flights available to book.\n");
        return;
    }
    if (tempFp == NULL) {
        printf("\nError processing booking.\n");
        fclose(fp);
        return;
    }

    printf("\nEnter Flight ID to book: ");
    scanf("%d", &id);

    while(fread(&f, sizeof(struct Flight), 1, fp)) {
        if(f.id == id) {
            found = 1;
            if (f.seats > 0) {
                f.seats--;
                printf("\nBooking successful for Flight %d (%s to %s)!\n", f.id, f.origin, f.destination);
                fwrite(&f, sizeof(struct Flight), 1, tempFp);
            } else {
                printf("\nSorry, flight is fully booked!\n");
                fwrite(&f, sizeof(struct Flight), 1, tempFp); // Still write it back
            }
        } else {
            fwrite(&f, sizeof(struct Flight), 1, tempFp);
        }
    }

    fclose(fp);
    fclose(tempFp);

    remove(FLIGHT_FILENAME);
    rename("temp_flights.txt", FLIGHT_FILENAME);

    if(!found) {
        printf("\nFlight not found with ID %d.\n", id);
    }
}

void cancelFlight() {
    struct Flight f;
    FILE *fp = fopen(FLIGHT_FILENAME, "rb");
    FILE *tempFp = fopen("temp_flights.txt", "wb");
    int id, found = 0;

    if (fp == NULL) {
        printf("\nNo flights available.\n");
        return;
    }
    if (tempFp == NULL) {
        printf("\nError processing cancellation.\n");
        fclose(fp);
        return;
    }

    printf("\nEnter Flight ID to cancel booking for: ");
    scanf("%d", &id);

    while(fread(&f, sizeof(struct Flight), 1, fp)) {
        if(f.id == id) {
            found = 1;
            f.seats++;
            printf("\nCancellation successful! Seat restored for Flight %d.\n", f.id);
            fwrite(&f, sizeof(struct Flight), 1, tempFp);
        } else {
            fwrite(&f, sizeof(struct Flight), 1, tempFp);
        }
    }

    fclose(fp);
    fclose(tempFp);

    remove(FLIGHT_FILENAME);
    rename("temp_flights.txt", FLIGHT_FILENAME);

    if(!found) {
        printf("\nFlight not found with ID %d.\n", id);
    }
}
