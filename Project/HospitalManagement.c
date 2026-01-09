#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * Project: Hospital Management System
 * Description: A comprehensive system to manage patients, doctors, and appointments with file persistence.
 * Estimated Lines: ~350-400
 */

// --------------------------------------------------------------------------
// STRUCTURE DEFINITIONS
// --------------------------------------------------------------------------
typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[50];
    int roomNumber;
    char admissionDate[20];
    float medicineCharges;
    float roomCharges;
    float docFees;
} Patient;

typedef struct {
    int id;
    char name[50];
    char specialty[50];
    char city[50];
    char contact[15];
} Doctor;

typedef struct {
    int patientId;
    int doctorId;
    char date[20];
    char time[10];
    char status[20]; // Scheduled, Completed, Cancelled
} Appointment;

// --------------------------------------------------------------------------
// FUNCTION PROTOTYPES
// --------------------------------------------------------------------------
void mainMenu();
void patientMenu();
void doctorMenu();
void appointmentMenu();
void billingMenu();

void addPatient();
void viewPatients();
void searchPatient();
void updatePatient();
void sortPatientsByName();
void dischargePatient();

void addDoctor();
void viewDoctors();
void searchDoctorBySpecialty();
void updateDoctor();

void scheduleAppointment();
void viewAppointments();
void cancelAppointment();

void generateInvoice(int patientId);
void login();

// Helper Prototypes
void savePatient(Patient p);
void saveDoctor(Doctor d);
void saveAppointment(Appointment a);
int getNextPatientId();
int getNextDoctorId();
void clearBuffer();

// File Names
#define PATIENT_FILE "patients.dat"
#define DOCTOR_FILE "doctors.dat"
#define APPOINTMENT_FILE "appointments.dat"

// --------------------------------------------------------------------------
// MAIN & AUTHENTICATION
// --------------------------------------------------------------------------
int main() {
    login();
    mainMenu();
    return 0;
}

void login() {
    char username[20], password[20];
    printf("\n======================================================\n");
    printf("       CITY METRO HOSPITAL MANAGEMENT SYSTEM          \n");
    printf("======================================================\n");
    while(1) {
        printf("\nUsername (hint: admin): ");
        scanf("%s", username);
        printf("Password (hint: 2850): ");
        scanf("%s", password);
        
        if(strcmp(username, "admin") == 0 && strcmp(password, "2850") == 0) {
            printf("\nLogin Successful! Accessing secure system...\n");
            break;
        } else {
            printf("\nError: Invalid Credentials! Access Denied.\n");
        }
    }
}

// --------------------------------------------------------------------------
// MENU SYSTEM
// --------------------------------------------------------------------------
void mainMenu() {
    int choice;
    while(1) {
        printf("\n====================================\n");
        printf("            MAIN MENU               \n");
        printf("====================================\n");
        printf("1. Patient Management\n");
        printf("2. Doctor Management\n");
        printf("3. Appointment Scheduling\n");
        printf("4. Billing & Invoices\n");
        printf("5. Exit System\n");
        printf("------------------------------------\n");
        printf("Select Option: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: patientMenu(); break;
            case 2: doctorMenu(); break;
            case 3: appointmentMenu(); break;
            case 4: billingMenu(); break;
            case 5: printf("\nSigning off... Have a great day!\n"); exit(0);
            default: printf("Error: Invalid selection. Try again.\n");
        }
    }
}

void patientMenu() {
    int choice;
    while(1) {
        printf("\n--- [ PATIENT MANAGEMENT ] ---\n");
        printf("1. Register New Patient\n");
        printf("2. View All In-Patients\n");
        printf("3. Search Patient by ID\n");
        printf("4. Update Patient Diagnosis\n");
        printf("5. Sort Patients by Name\n");
        printf("6. Back to Main Menu\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: searchPatient(); break;
            case 4: updatePatient(); break;
            case 5: sortPatientsByName(); break;
            case 6: return;
            default: printf("Error: Invalid option.\n");
        }
    }
}

void doctorMenu() {
    int choice;
    while(1) {
        printf("\n--- [ DOCTOR MANAGEMENT ] ---\n");
        printf("1. Add New Staff (Doctor)\n");
        printf("2. View Hospital Staff List\n");
        printf("3. Search Doctor by Specialty\n");
        printf("4. Update Contact Information\n");
        printf("5. Back to Main Menu\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addDoctor(); break;
            case 2: viewDoctors(); break;
            case 3: searchDoctorBySpecialty(); break;
            case 4: updateDoctor(); break;
            case 5: return;
            default: printf("Error: Invalid choice.\n");
        }
    }
}

// --------------------------------------------------------------------------
// PATIENT LOGIC
// --------------------------------------------------------------------------
void addPatient() {
    Patient p;
    p.id = getNextPatientId();
    
    printf("\n--- REGISTER PATIENT (ID: %d) ---\n", p.id);
    printf("Full Name: ");
    clearBuffer();
    fgets(p.name, 50, stdin); p.name[strcspn(p.name, "\n")] = 0;
    
    printf("Age: ");
    scanf("%d", &p.age);
    printf("Gender (M/F/O): ");
    scanf("%s", p.gender);
    
    printf("Initial Diagnosis (Disease): ");
    clearBuffer();
    fgets(p.disease, 50, stdin); p.disease[strcspn(p.disease, "\n")] = 0;
    
    printf("Allocated Room Number: ");
    scanf("%d", &p.roomNumber);
    
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(p.admissionDate, sizeof(p.admissionDate), "%Y-%m-%d %H:%M", tm);
    
    p.medicineCharges = 0;
    p.roomCharges = 0;
    p.docFees = 0;

    savePatient(p);
    printf("\nSuccess: Patient admitted on %s\n", p.admissionDate);
}

void viewPatients() {
    FILE *file = fopen(PATIENT_FILE, "rb");
    if(!file) { printf("Info: Patient database is empty.\n"); return; }
    Patient p;
    printf("\n%-4s %-20s %-4s %-8s %-15s %-6s %-18s\n", "ID", "Name", "Age", "Gend", "Disease", "Room", "Admission Date");
    printf("-----------------------------------------------------------------------------------------\n");
    while(fread(&p, sizeof(Patient), 1, file)) {
        printf("%-4d %-20s %-4d %-8s %-15s %-6d %-18s\n", p.id, p.name, p.age, p.gender, p.disease, p.roomNumber, p.admissionDate);
    }
    fclose(file);
}

void searchPatient() {
    int id;
    printf("Enter Patient ID to retrieve record: ");
    scanf("%d", &id);
    
    FILE *file = fopen(PATIENT_FILE, "rb");
    if(!file) return;
    Patient p;
    int found = 0;
    while(fread(&p, sizeof(Patient), 1, file)) {
        if(p.id == id) {
            printf("\n--- PATIENT RECORD FOUND ---\n");
            printf("ID: %d | Name: %s\nAge: %d | Gender: %s\nDisease: %s\nRoom: %d | Admitted: %s\n", 
                    p.id, p.name, p.age, p.gender, p.disease, p.roomNumber, p.admissionDate);
            found = 1;
            break;
        }
    }
    if(!found) printf("Error: No record found for ID %d.\n", id);
    fclose(file);
}

void updatePatient() {
    int id;
    printf("Enter Patient ID for update: ");
    scanf("%d", &id);
    
    FILE *file = fopen(PATIENT_FILE, "rb+");
    if(!file) return;
    Patient p;
    while(fread(&p, sizeof(Patient), 1, file)) {
        if(p.id == id) {
            printf("Modifying Diagnosis for %s\nNew Diagnosis: ", p.name);
            clearBuffer();
            fgets(p.disease, 50, stdin); p.disease[strcspn(p.disease, "\n")] = 0;
            printf("Update Room Number: ");
            scanf("%d", &p.roomNumber);
            
            fseek(file, -(long)sizeof(Patient), SEEK_CUR);
            fwrite(&p, sizeof(Patient), 1, file);
            printf("Success: Records updated successfully.\n");
            fclose(file);
            return;
        }
    }
    printf("Error: ID not found.\n");
    fclose(file);
}

void sortPatientsByName() {
    FILE *file = fopen(PATIENT_FILE, "rb");
    if(!file) return;
    fseek(file, 0, SEEK_END);
    int count = ftell(file) / sizeof(Patient);
    if(count == 0) { fclose(file); return; }
    rewind(file);
    
    Patient *arr = (Patient*)malloc(count * sizeof(Patient));
    for(int i=0; i<count; i++) fread(&arr[i], sizeof(Patient), 1, file);
    fclose(file);
    
    // Bubble Sort
    for(int i=0; i<count-1; i++) {
        for(int j=0; j<count-i-1; j++) {
            if(strcmp(arr[j].name, arr[j+1].name) > 0) {
                Patient temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    
    printf("\n--- PATIENTS SORTED BY NAME ---\n");
    for(int i=0; i<count; i++)
        printf("ID: %-4d | Name: %-20s | Disease: %s\n", arr[i].id, arr[i].name, arr[i].disease);
    free(arr);
}

// --------------------------------------------------------------------------
// DOCTOR LOGIC
// --------------------------------------------------------------------------
void addDoctor() {
    Doctor d;
    d.id = getNextDoctorId();
    printf("\n--- ADD STAFF DOCTOR (ID: %d) ---\n", d.id);
    printf("Full Name: "); clearBuffer();
    fgets(d.name, 50, stdin); d.name[strcspn(d.name, "\n")] = 0;
    printf("Specialty (e.g., Cardiology): ");
    fgets(d.specialty, 50, stdin); d.specialty[strcspn(d.specialty, "\n")] = 0;
    printf("City: ");
    fgets(d.city, 50, stdin); d.city[strcspn(d.city, "\n")] = 0;
    printf("Contact Number: ");
    fgets(d.contact, 15, stdin); d.contact[strcspn(d.contact, "\n")] = 0;
    
    saveDoctor(d);
    printf("Success: Doctor record stored.\n");
}

void viewDoctors() {
    FILE *file = fopen(DOCTOR_FILE, "rb");
    if(!file) { printf("No staff records found.\n"); return; }
    Doctor d;
    printf("\n%-4s %-20s %-15s %-15s %-15s\n", "ID", "Name", "Specialty", "City", "Contact");
    printf("--------------------------------------------------------------------------------\n");
    while(fread(&d, sizeof(Doctor), 1, file)) {
        printf("%-4d %-20s %-15s %-15s %-15s\n", d.id, d.name, d.specialty, d.city, d.contact);
    }
    fclose(file);
}

void searchDoctorBySpecialty() {
    char spec[50];
    printf("Enter Specialty to filter: ");
    clearBuffer();
    fgets(spec, 50, stdin); spec[strcspn(spec, "\n")] = 0;
    
    FILE *file = fopen(DOCTOR_FILE, "rb");
    if(!file) return;
    Doctor d;
    int found = 0;
    while(fread(&d, sizeof(Doctor), 1, file)) {
        if(strstr(d.specialty, spec)) {
            printf("Found: Dr. %-20s | Specialty: %-15s | Ph: %s\n", d.name, d.specialty, d.contact);
            found = 1;
        }
    }
    if(!found) printf("No doctors found with specialty like '%s'.\n", spec);
    fclose(file);
}

void updateDoctor() {
    int id;
    printf("Doctor ID to update: ");
    scanf("%d", &id);
    FILE *file = fopen(DOCTOR_FILE, "rb+");
    if(!file) return;
    Doctor d;
    while(fread(&d, sizeof(Doctor), 1, file)) {
        if(d.id == id) {
            printf("Updating Contact for %s. New Contact: ", d.name);
            scanf("%s", d.contact);
            fseek(file, -(long)sizeof(Doctor), SEEK_CUR);
            fwrite(&d, sizeof(Doctor), 1, file);
            printf("Record Success: Staff contact updated.\n");
            fclose(file);
            return;
        }
    }
    printf("Error: Doctor ID not found.\n");
    fclose(file);
}

// --------------------------------------------------------------------------
// APPOINTMENT LOGIC
// --------------------------------------------------------------------------
void appointmentMenu() {
    int choice;
    while(1) {
        printf("\n--- [ APPOINTMENT SYSTEM ] ---\n");
        printf("1. Schedule New Appointment\n");
        printf("2. View All Scheduled Visits\n");
        printf("3. Cancel Appointment\n");
        printf("4. Back to Main Menu\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: scheduleAppointment(); break;
            case 2: viewAppointments(); break;
            case 3: cancelAppointment(); break;
            case 4: return;
            default: printf("Error: Invalid choice.\n");
        }
    }
}

void scheduleAppointment() {
    Appointment a;
    printf("Target Patient ID: "); scanf("%d", &a.patientId);
    printf("Available Doctor ID: "); scanf("%d", &a.doctorId);
    printf("Date (DD/MM/YYYY): "); scanf("%s", a.date);
    printf("Time (HH:MM): "); scanf("%s", a.time);
    strcpy(a.status, "Scheduled");
    
    saveAppointment(a);
    printf("Success: Appointment record established.\n");
}

void viewAppointments() {
    FILE *file = fopen(APPOINTMENT_FILE, "rb");
    if(!file) { printf("No appointments scheduled.\n"); return; }
    Appointment a;
    printf("\n%-10s %-10s %-12s %-10s %-12s\n", "PatientID", "DoctorID", "Date", "Time", "Status");
    printf("------------------------------------------------------------\n");
    while(fread(&a, sizeof(Appointment), 1, file)) {
        printf("%-10d %-10d %-12s %-10s %-12s\n", a.patientId, a.doctorId, a.date, a.time, a.status);
    }
    fclose(file);
}

void cancelAppointment() {
    int pid;
    printf("Enter Patient ID to cancel their appointment: ");
    scanf("%d", &pid);
    FILE *file = fopen(APPOINTMENT_FILE, "rb+");
    if(!file) return;
    Appointment a;
    int found = 0;
    while(fread(&a, sizeof(Appointment), 1, file)) {
        if(a.patientId == pid && strcmp(a.status, "Cancelled") != 0) {
            strcpy(a.status, "Cancelled");
            fseek(file, -(long)sizeof(Appointment), SEEK_CUR);
            fwrite(&a, sizeof(Appointment), 1, file);
            printf("Success: Appointment for Patient %d is now Cancelled.\n", pid);
            found = 1;
            break;
        }
    }
    if(!found) printf("No active appointment found for ID %d.\n", pid);
    fclose(file);
}

// --------------------------------------------------------------------------
// BILLING LOGIC
// --------------------------------------------------------------------------
void billingMenu() {
    int choice, pid;
    while(1) {
        printf("\n--- [ BILLING & FINANCE ] ---\n");
        printf("1. Update Pharmacy/Medicine Bill\n");
        printf("2. Final Discharge & Print Invoice\n");
        printf("3. Return to Main Menu\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if(choice == 1) {
            printf("Patient ID: "); scanf("%d", &pid);
            FILE *f = fopen(PATIENT_FILE, "rb+");
            if(!f) continue;
            Patient p;
            while(fread(&p, sizeof(Patient), 1, f)) {
                if(p.id == pid) {
                    float add;
                    printf("Current Med Bill: $%.2f. Add Amt: ", p.medicineCharges);
                    scanf("%f", &add);
                    p.medicineCharges += add;
                    fseek(f, -(long)sizeof(Patient), SEEK_CUR);
                    fwrite(&p, sizeof(Patient), 1, f);
                    printf("Charges Added.\n");
                    break;
                }
            }
            fclose(f);
        } else if(choice == 2) {
            printf("Patient ID for Final Audit: "); scanf("%d", &pid);
            generateInvoice(pid);
        } else if(choice == 3) return;
    }
}

void generateInvoice(int patientId) {
    FILE *file = fopen(PATIENT_FILE, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if(!file || !temp) return;
    
    Patient p;
    int found = 0;
    while(fread(&p, sizeof(Patient), 1, file)) {
        if(p.id == patientId) {
            found = 1;
            int days;
            printf("\n--- GENERATING FINAL INVOICE FOR: %s ---\n", p.name);
            printf("Number of days stayed: "); scanf("%d", &days);
            p.roomCharges = days * 150.0; // Standard room rate
            p.docFees = 250.0; // Consultation block
            
            float total = p.roomCharges + p.medicineCharges + p.docFees;
            
            printf("\n************************************************\n");
            printf("         CITY METRO HOSPITAL INVOICE            \n");
            printf("************************************************\n");
            printf("Patient ID: %-5d | Date Admitted: %s\n", p.id, p.admissionDate);
            printf("Patient Name: %s\n", p.name);
            printf("------------------------------------------------\n");
            printf("Room Rent (%d days @ $150):     $%10.2f\n", days, p.roomCharges);
            printf("Pharmacy & Medication:          $%10.2f\n", p.medicineCharges);
            printf("Doctor Consultation Charges:    $%10.2f\n", p.docFees);
            printf("------------------------------------------------\n");
            printf("TOTAL PAYABLE AMOUNT:           $%10.2f\n", total);
            printf("************************************************\n\n");
            printf("Status: PATIENT DISCHARGED.\n");
        } else {
            fwrite(&p, sizeof(Patient), 1, temp);
        }
    }
    fclose(file); fclose(temp);
    remove(PATIENT_FILE); rename("temp.dat", PATIENT_FILE);
    if(!found) printf("Audit Error: Patient ID not found in system.\n");
}

// --------------------------------------------------------------------------
// UTILITY FUNCTIONS
// --------------------------------------------------------------------------
void savePatient(Patient p) {
    FILE *f = fopen(PATIENT_FILE, "ab");
    fwrite(&p, sizeof(Patient), 1, f);
    fclose(f);
}

void saveDoctor(Doctor d) {
    FILE *f = fopen(DOCTOR_FILE, "ab");
    fwrite(&d, sizeof(Doctor), 1, f);
    fclose(f);
}

void saveAppointment(Appointment a) {
    FILE *f = fopen(APPOINTMENT_FILE, "ab");
    fwrite(&a, sizeof(Appointment), 1, f);
    fclose(f);
}

int getNextPatientId() {
    FILE *f = fopen(PATIENT_FILE, "rb");
    if(!f) return 1001;
    fseek(f, 0, SEEK_END);
    int nextId = (ftell(f) / sizeof(Patient)) + 1001;
    fclose(f);
    return nextId;
}

int getNextDoctorId() {
    FILE *f = fopen(DOCTOR_FILE, "rb");
    if(!f) return 501;
    fseek(f, 0, SEEK_END);
    int nextId = (ftell(f) / sizeof(Doctor)) + 501;
    fclose(f);
    return nextId;
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
