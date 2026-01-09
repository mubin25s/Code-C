#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * Project: Grand Palace Hotel Management System
 * Description: Management of rooms, guests, room service, and check-out billing.
 * Estimated Lines: ~350-400
 */

// --------------------------------------------------------------------------
// DATA STRUCTURES
// --------------------------------------------------------------------------
typedef struct {
    int roomNo;
    char type[20]; // Single, Double, Deluxe, Suite
    int capacity;
    float pricePerNight;
    int isOccupied; // 0 for Free, 1 for Occupied
} Room;

typedef struct {
    int guestId;
    char name[50];
    char contact[15];
    int roomNo;
    char checkInDate[20];
    float additionalCharges; // Room service, laundry, etc.
} Guest;

typedef struct {
    char itemName[30];
    float price;
} MenuItem;

// --------------------------------------------------------------------------
// GLOBAL CONSTANTS & FILE NAMES
// --------------------------------------------------------------------------
#define ROOM_FILE "rooms.dat"
#define GUEST_FILE "guests.dat"
#define ADMIN_PASS "2850"

// --------------------------------------------------------------------------
// PROOTOTYPES
// --------------------------------------------------------------------------
void login();
void mainMenu();
void roomMenu();
void guestMenu();
void billingMenu();

// Room Functions
void addRoom();
void viewRooms();
void updateRoomStatus(int rNo, int status);
int isRoomAvailable(int rNo);
void searchRoom();

// Guest Functions
void checkIn();
void viewGuests();
void searchGuest();
void roomService();

// Support Functions
void checkOut();
void generateBill(Guest g, Room r, int days);
int getNextGuestId();
void clearBuffer();
void initializeFiles();

// --------------------------------------------------------------------------
// MAIN & INIT
// --------------------------------------------------------------------------
int main() {
    initializeFiles();
    login();
    mainMenu();
    return 0;
}

void initializeFiles() {
    FILE *f1 = fopen(ROOM_FILE, "ab"); fclose(f1);
    FILE *f2 = fopen(GUEST_FILE, "ab"); fclose(f2);
}

void login() {
    char pass[20];
    printf("\n******************************************************\n");
    printf("*        GRAND PALACE HOTEL MANAGEMENT SYSTEM        *\n");
    printf("******************************************************\n");
    while(1) {
        printf("\nEnter Management Password: ");
        scanf("%s", pass);
        if(strcmp(pass, ADMIN_PASS) == 0) {
            printf("Access Granted! Loading system...\n");
            break;
        } else {
            printf("Invalid Password! Try again.\n");
        }
    }
}

// --------------------------------------------------------------------------
// MENU SYSTEM
// --------------------------------------------------------------------------
void mainMenu() {
    int choice;
    while(1) {
        printf("\n--- [ HOTEL MAIN MENU ] ---\n");
        printf("1. Room Management\n");
        printf("2. Guest Check-In\n");
        printf("3. Room Service & Extras\n");
        printf("4. Check-Out & Billing\n");
        printf("5. View All Current Guests\n");
        printf("6. Exit System\n");
        printf("Selection: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: roomMenu(); break;
            case 2: checkIn(); break;
            case 3: roomService(); break;
            case 4: checkOut(); break;
            case 5: viewGuests(); break;
            case 6: printf("Goodbye!\n"); exit(0);
            default: printf("Invalid Selection.\n");
        }
    }
}

void roomMenu() {
    int choice;
    while(1) {
        printf("\n--- [ ROOM MANAGEMENT ] ---\n");
        printf("1. Add New Room\n");
        printf("2. View All Rooms\n");
        printf("3. Search Room Details\n");
        printf("4. Back to Main Menu\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addRoom(); break;
            case 2: viewRooms(); break;
            case 3: searchRoom(); break;
            case 4: return;
            default: printf("Invalid Choice.\n");
        }
    }
}

// --------------------------------------------------------------------------
// ROOM LOGIC
// --------------------------------------------------------------------------
void addRoom() {
    Room r;
    printf("\nEnter Room Number: ");
    scanf("%d", &r.roomNo);
    
    // Check if room exists
    FILE *f = fopen(ROOM_FILE, "rb");
    if(f) {
        Room temp;
        while(fread(&temp, sizeof(Room), 1, f)) {
            if(temp.roomNo == r.roomNo) {
                printf("Error: Room number already exists!\n");
                fclose(f); return;
            }
        }
        fclose(f);
    }

    printf("Room Type (Single/Double/Deluxe/Suite): ");
    scanf("%s", r.type);
    printf("Capacity (Persons): ");
    scanf("%d", &r.capacity);
    printf("Price Per Night: $");
    scanf("%f", &r.pricePerNight);
    r.isOccupied = 0;

    FILE *wf = fopen(ROOM_FILE, "ab");
    fwrite(&r, sizeof(Room), 1, wf);
    fclose(wf);
    printf("Success: Room %d added to inventory.\n", r.roomNo);
}

void viewRooms() {
    FILE *f = fopen(ROOM_FILE, "rb");
    if(!f) return;
    Room r;
    printf("\n%-8s %-12s %-10s %-10s %-10s\n", "RoomNo", "Type", "Capacity", "Price", "Status");
    printf("------------------------------------------------------------\n");
    while(fread(&r, sizeof(Room), 1, f)) {
        printf("%-8d %-12s %-10d $%-9.2f %-10s\n", 
               r.roomNo, r.type, r.capacity, r.pricePerNight, 
               r.isOccupied ? "Occupied" : "Available");
    }
    fclose(f);
}

void searchRoom() {
    int rNo;
    printf("Enter Room No: ");
    scanf("%d", &rNo);
    FILE *f = fopen(ROOM_FILE, "rb");
    Room r;
    int found = 0;
    while(fread(&r, sizeof(Room), 1, f)) {
        if(r.roomNo == rNo) {
            printf("\nRoom Info: %d (%s) | Price: $%.2f | Status: %s\n", 
                   r.roomNo, r.type, r.pricePerNight, r.isOccupied ? "Occupied" : "Free");
            found = 1; break;
        }
    }
    if(!found) printf("Room not found.\n");
    fclose(f);
}

// --------------------------------------------------------------------------
// GUEST LOGIC
// --------------------------------------------------------------------------
void checkIn() {
    Guest g;
    int rNo;
    printf("\n--- GUEST CHECK-IN ---\n");
    printf("Enter Room Number requested: ");
    scanf("%d", &rNo);

    FILE *rf = fopen(ROOM_FILE, "rb");
    Room r;
    int valid = 0;
    while(fread(&r, sizeof(Room), 1, rf)) {
        if(r.roomNo == rNo && r.isOccupied == 0) {
            valid = 1; break;
        }
    }
    fclose(rf);

    if(!valid) {
        printf("Error: Room is either occupied or doesn't exist.\n");
        return;
    }

    g.guestId = getNextGuestId();
    g.roomNo = rNo;
    printf("Guest Name: ");
    clearBuffer();
    fgets(g.name, 50, stdin); g.name[strcspn(g.name, "\n")] = 0;
    printf("Contact Number: ");
    scanf("%s", g.contact);
    
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(g.checkInDate, 20, "%Y-%m-%d %H:%M", tm_info);
    
    g.additionalCharges = 0;

    // Save Guest
    FILE *gf = fopen(GUEST_FILE, "ab");
    fwrite(&g, sizeof(Guest), 1, gf);
    fclose(gf);

    // Update Room Status
    updateRoomStatus(rNo, 1);
    printf("Success: %s check-in complete. ID: %d\n", g.name, g.guestId);
}

void viewGuests() {
    FILE *f = fopen(GUEST_FILE, "rb");
    if(!f) { printf("No active guests.\n"); return; }
    Guest g;
    printf("\n%-5s %-20s %-10s %-8s %-18s\n", "ID", "Name", "Room", "Charges", "Check-In");
    printf("--------------------------------------------------------------------------\n");
    while(fread(&g, sizeof(Guest), 1, f)) {
        printf("%-5d %-20s %-10d $%-7.2f %-18s\n", 
               g.guestId, g.name, g.roomNo, g.additionalCharges, g.checkInDate);
    }
    fclose(f);
}

void roomService() {
    int id;
    printf("Enter Guest ID: ");
    scanf("%d", &id);
    FILE *f = fopen(GUEST_FILE, "rb+");
    if(!f) return;
    Guest g;
    int found = 0;
    while(fread(&g, sizeof(Guest), 1, f)) {
        if(g.guestId == id) {
            float amt;
            printf("Guest: %s (Room %d)\n", g.name, g.roomNo);
            printf("Enter Room Service/Laundry Charge to add: $");
            scanf("%f", &amt);
            g.additionalCharges += amt;
            fseek(f, -(long)sizeof(Guest), SEEK_CUR);
            fwrite(&g, sizeof(Guest), 1, f);
            printf("Success: Charges updated.\n");
            found = 1; break;
        }
    }
    if(!found) printf("Guest ID not found.\n");
    fclose(f);
}

// --------------------------------------------------------------------------
// BILLING & CHECK-OUT
// --------------------------------------------------------------------------
void checkOut() {
    int id;
    printf("Enter Guest ID for Check-Out: ");
    scanf("%d", &id);
    
    FILE *f = fopen(GUEST_FILE, "rb");
    FILE *temp = fopen("g_temp.dat", "wb");
    Guest g;
    int found = 0;
    
    while(fread(&g, sizeof(Guest), 1, f)) {
        if(g.guestId == id) {
            found = 1;
            int days;
            printf("Checking out %s (Room %d)\n", g.name, g.roomNo);
            printf("Enter number of days stayed: ");
            scanf("%d", &days);

            // Get room price
            FILE *rf = fopen(ROOM_FILE, "rb");
            Room r;
            while(fread(&r, sizeof(Room), 1, rf)) {
                if(r.roomNo == g.roomNo) {
                    generateBill(g, r, days);
                    break;
                }
            }
            fclose(rf);
            
            // Re-open room to free it
            updateRoomStatus(g.roomNo, 0);
        } else {
            fwrite(&g, sizeof(Guest), 1, temp);
        }
    }
    fclose(f);
    fclose(temp);
    remove(GUEST_FILE);
    rename("g_temp.dat", GUEST_FILE);
    
    if(!found) printf("Error: Guest record not found.\n");
}

void generateBill(Guest g, Room r, int days) {
    float roomTotal = days * r.pricePerNight;
    float grandTotal = roomTotal + g.additionalCharges;
    
    printf("\n************************************************\n");
    printf("           GRAND PALACE HOTEL - FINAL BILL      \n");
    printf("************************************************\n");
    printf("Guest Name: %-25s ID: %-5d\n", g.name, g.guestId);
    printf("Room: %-10d Type: %-15s\n", r.roomNo, r.type);
    printf("Check-In: %s\n", g.checkInDate);
    printf("------------------------------------------------\n");
    printf("Room Charges (%d days @ $%.2f):   $%10.2f\n", days, r.pricePerNight, roomTotal);
    printf("Room Service & Other Charges:       $%10.2f\n", g.additionalCharges);
    printf("------------------------------------------------\n");
    printf("GRAND TOTAL PAYABLE:                $%10.2f\n", grandTotal);
    printf("************************************************\n");
    printf("Payment Status: PAID - THANK YOU!\n\n");
}

// --------------------------------------------------------------------------
// HELPERS
// --------------------------------------------------------------------------
void updateRoomStatus(int rNo, int status) {
    FILE *f = fopen(ROOM_FILE, "rb+");
    Room r;
    while(fread(&r, sizeof(Room), 1, f)) {
        if(r.roomNo == rNo) {
            r.isOccupied = status;
            fseek(f, -(long)sizeof(Room), SEEK_CUR);
            fwrite(&r, sizeof(Room), 1, f);
            break;
        }
    }
    fclose(f);
}

int getNextGuestId() {
    FILE *f = fopen(GUEST_FILE, "rb");
    if(!f) return 101;
    fseek(f, 0, SEEK_END);
    int count = (ftell(f) / sizeof(Guest)) + 101;
    fclose(f);
    return count;
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
