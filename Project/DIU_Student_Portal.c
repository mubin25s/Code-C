<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * Project: DIU Student Portal (Daffodil International University)
 * Description: A comprehensive portal for DIU students to manage courses, results, and fees.
 * Estimated Lines: ~380-420
 */

// --------------------------------------------------------------------------
// STRUCTURES
// --------------------------------------------------------------------------
typedef struct {
    char code[15];
    char name[50];
    float credit;
    float marks;
    char grade[5];
} Course;

typedef struct {
    char id[20];        // Format: 221-15-XXXX
    char password[20];
    char name[100];
    char dept[50];
    char campus[20];    // DSC, MC, PC
    int semester;
    Course registeredCourses[6];
    int courseCount;
    float cgpa;
    float totalPayable;
    float waiverPercent;
    float paidAmount;
} Student;

// --------------------------------------------------------------------------
// PROTOTYPES
// --------------------------------------------------------------------------
void loginPanel();
void studentDashboard(char *studentId);
void adminPanel();
void welcomeHeader();

// Admin Functions
void registerNewStudent();
void viewAllStudents();
void updateStudentResult();
void manageFinances();

// Student Functions
void viewProfile(Student s);
void courseRegistration(char *studentId);
void viewSmartResult(Student s);
void showFinancePortal(Student s);
void universityNotices();

// Helpers
void saveStudent(Student s);
void updateStudent(Student s);
Student* findStudent(char *id);
void clearBuffer();
float calculateGPA(Student s);
void getGrade(float marks, char *grade);

#define DB_FILE "diu_students.dat"
#define ADMIN_PASS "2850"

// --------------------------------------------------------------------------
// MAIN
// --------------------------------------------------------------------------
int main() {
    FILE *f = fopen(DB_FILE, "ab"); fclose(f);
    loginPanel();
    return 0;
}

void welcomeHeader() {
    system("cls");
    printf("\n========================================================\n");
    printf("        DAFFODIL INTERNATIONAL UNIVERSITY (DIU)         \n");
    printf("                  STUDENT SMART PORTAL                  \n");
    printf("========================================================\n");
}

void loginPanel() {
    int choice;
    while(1) {
        welcomeHeader();
        printf("1. Student Login\n");
        printf("2. Admin/Registrar Access\n");
        printf("3. Exit System\n");
        printf("Selection: ");
        scanf("%d", &choice);

        if(choice == 1) {
            char id[20], pass[20];
            printf("\nDIU ID (e.g., 221-15-XXX): ");
            scanf("%s", id);
            printf("Password: ");
            scanf("%s", pass);

            Student *s = findStudent(id);
            if(s && strcmp(s->password, pass) == 0) {
                studentDashboard(id);
            } else {
                printf("\nError: ID or Password incorrect!\n");
                system("pause");
            }
            free(s);
        } else if(choice == 2) {
            char pass[20];
            printf("\nEnter Admin Key: ");
            scanf("%s", pass);
            if(strcmp(pass, ADMIN_PASS) == 0) adminPanel();
            else printf("Access Denied.\n");
        } else if(choice == 3) exit(0);
    }
}

// --------------------------------------------------------------------------
// ADMIN PANEL
// --------------------------------------------------------------------------
void adminPanel() {
    int choice;
    while(1) {
        welcomeHeader();
        printf("--- [ REGISTRAR ADMIN PANEL ] ---\n");
        printf("1. Register New Student admission\n");
        printf("2. View Student Directory\n");
        printf("3. Post Semester Marks/Result\n");
        printf("4. Process Waiver & Fees\n");
        printf("5. Logout\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: registerNewStudent(); break;
            case 2: viewAllStudents(); break;
            case 3: updateStudentResult(); break;
            case 4: manageFinances(); break;
            case 5: return;
        }
        system("pause");
    }
}

void registerNewStudent() {
    Student s;
    printf("\n--- New Admission Form ---\n");
    printf("Enter Student ID: "); scanf("%s", s.id);
    
    // Check if duplicate
    Student *check = findStudent(s.id);
    if(check) { printf("Error: ID already exists!\n"); free(check); return; }

    printf("Full Name: "); clearBuffer();
    fgets(s.name, 100, stdin); s.name[strcspn(s.name, "\n")] = 0;
    
    printf("Department (e.g. CSE/EEE/BBA): ");
    scanf("%s", s.dept);
    
    printf("Campus (DSC/MC): ");
    scanf("%s", s.campus);
    
    printf("Initial Semester: ");
    scanf("%d", &s.semester);
    
    printf("Set Portal Password: ");
    scanf("%s", s.password);

    s.courseCount = 0;
    s.cgpa = 0.0;
    s.totalPayable = 850000.0; // Total degree cost estimation
    s.waiverPercent = 0.0;
    s.paidAmount = 0.0;

    saveStudent(s);
    printf("\nSuccess: Student %s registered successfully.\n", s.id);
}

void viewAllStudents() {
    FILE *f = fopen(DB_FILE, "rb");
    Student s;
    printf("\n%-12s %-20s %-10s %-8s %-5s\n", "ID", "Name", "Dept", "Campus", "CGPA");
    printf("------------------------------------------------------------------\n");
    while(fread(&s, sizeof(Student), 1, f)) {
        printf("%-12s %-20s %-10s %-8s %-5.2f\n", s.id, s.name, s.dept, s.campus, s.cgpa);
    }
    fclose(f);
}

// --------------------------------------------------------------------------
// STUDENT DASHBOARD
// --------------------------------------------------------------------------
void studentDashboard(char *studentId) {
    int choice;
    while(1) {
        Student *sptr = findStudent(studentId);
        if(!sptr) return;
        Student s = *sptr; free(sptr);

        welcomeHeader();
        printf("Welcome, %s (%s)\n", s.name, s.id);
        printf("Semester: %d | CGPA: %.2f\n", s.semester, s.cgpa);
        printf("--------------------------------------------------------\n");
        printf("1. View My Profile\n");
        printf("2. Course Registration\n");
        printf("3. Smart Result Inquiry\n");
        printf("4. Accounts & Finance\n");
        printf("5. University Notices\n");
        printf("6. Logout\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: viewProfile(s); break;
            case 2: courseRegistration(s.id); break;
            case 3: viewSmartResult(s); break;
            case 4: showFinancePortal(s); break;
            case 5: universityNotices(); break;
            case 6: return;
        }
        system("pause");
    }
}

void viewProfile(Student s) {
    printf("\n--- [ MY PROFILE ] ---\n");
    printf("Name:     %s\n", s.name);
    printf("ID:       %s\n", s.id);
    printf("Dept:     %s\n", s.dept);
    printf("Campus:   %s\n", s.campus);
    printf("Semester: %d\n", s.semester);
    printf("Courses:  %d Registered\n", s.courseCount);
}

void courseRegistration(char *studentId) {
    Student *sptr = findStudent(studentId);
    if(!sptr) return;
    Student s = *sptr; free(sptr);

    printf("\n--- DIU COURSE REGISTRATION ---\n");
    printf("How many courses to register (Max 6): ");
    int count;
    scanf("%d", &count);
    
    if(count > 6) { printf("Limit exceeded!\n"); return; }
    
    s.courseCount = count;
    for(int i=0; i<count; i++) {
        printf("Course %d Code: ", i+1);
        scanf("%s", s.registeredCourses[i].code);
        printf("Course %d Credit: ", i+1);
        scanf("%f", &s.registeredCourses[i].credit);
        s.registeredCourses[i].marks = 0;
        strcpy(s.registeredCourses[i].grade, "N/A");
    }
    
    updateStudent(s);
    printf("\nRegistration Successful. Waiting for Advisor approval.\n");
}

void viewSmartResult(Student s) {
    printf("\n--- [ SEMESTER RESULT CARD ] ---\n");
    printf("%-15s %-10s %-10s\n", "Course Code", "Marks", "Grade");
    printf("-------------------------------------------\n");
    for(int i=0; i<s.courseCount; i++) {
        printf("%-15s %-10.1f %-10s\n", 
            s.registeredCourses[i].code, 
            s.registeredCourses[i].marks, 
            s.registeredCourses[i].grade);
    }
    printf("-------------------------------------------\n");
    printf("CURRENT CGPA: %.2f\n", s.cgpa);
}

void showFinancePortal(Student s) {
    float waiverAmount = (s.totalPayable * s.waiverPercent) / 100;
    float currentPayable = s.totalPayable - waiverAmount;
    float due = currentPayable - s.paidAmount;

    printf("\n--- [ DIU ACCOUNTS & FINANCE ] ---\n");
    printf("Estimated Degree Cost:  $%10.2f\n", s.totalPayable);
    printf("Applied Waiver (%d%%):  -$%10.2f\n", (int)s.waiverPercent, waiverAmount);
    printf("-------------------------------------------\n");
    printf("Net Payable Amount:     $%10.2f\n", currentPayable);
    printf("Total Amount Paid:      $%10.2f\n", s.paidAmount);
    printf("-------------------------------------------\n");
    printf("CURRENT OUTSTANDING:    $%10.2f\n", due > 0 ? due : 0.0);
}

void universityNotices() {
    printf("\n--- [ DIU NOTICE BOARD ] ---\n");
    printf("1. End-semester exams start from 20th Jan.\n");
    printf("2. Library membership renewal open at PC.\n");
    printf("3. Convocation 2026 registration starts next week.\n");
}

// --------------------------------------------------------------------------
// ADMIN ACTION LOGIC
// --------------------------------------------------------------------------
void updateStudentResult() {
    char id[20];
    printf("Enter Student ID to update marks: ");
    scanf("%s", id);
    Student *sptr = findStudent(id);
    if(!sptr) { printf("Not found.\n"); return; }
    Student s = *sptr; free(sptr);

    printf("Updating results for: %s\n", s.name);
    for(int i=0; i<s.courseCount; i++) {
        printf("Enter marks for %s: ", s.registeredCourses[i].code);
        scanf("%f", &s.registeredCourses[i].marks);
        getGrade(s.registeredCourses[i].marks, s.registeredCourses[i].grade);
    }
    s.cgpa = calculateGPA(s);
    updateStudent(s);
    printf("Results published!\n");
}

void manageFinances() {
    char id[20];
    printf("Enter Student ID: ");
    scanf("%s", id);
    Student *sptr = findStudent(id);
    if(!sptr) return;
    Student s = *sptr; free(sptr);

    int opt;
    printf("1. Set Waiver Percentage\n2. Update Paid Amount\nChoice: ");
    scanf("%d", &opt);
    if(opt == 1) {
        printf("Enter waiver (%%): ");
        scanf("%f", &s.waiverPercent);
    } else {
        float p;
        printf("Enter payment amount: ");
        scanf("%f", &p);
        s.paidAmount += p;
    }
    updateStudent(s);
    printf("Billing updated.\n");
}

// --------------------------------------------------------------------------
// CORE HELPERS
// --------------------------------------------------------------------------
void saveStudent(Student s) {
    FILE *f = fopen(DB_FILE, "ab");
    fwrite(&s, sizeof(Student), 1, f);
    fclose(f);
}

void updateStudent(Student s) {
    FILE *f = fopen(DB_FILE, "rb+");
    Student temp;
    while(fread(&temp, sizeof(Student), 1, f)) {
        if(strcmp(temp.id, s.id) == 0) {
            fseek(f, -(long)sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, f);
            break;
        }
    }
    fclose(f);
}

Student* findStudent(char *id) {
    FILE *f = fopen(DB_FILE, "rb");
    Student *s = (Student*)malloc(sizeof(Student));
    while(fread(s, sizeof(Student), 1, f)) {
        if(strcmp(s->id, id) == 0) {
            fclose(f);
            return s;
        }
    }
    fclose(f);
    free(s);
    return NULL;
}

float calculateGPA(Student s) {
    float totalPoints = 0, totalCredits = 0;
    for(int i=0; i<s.courseCount; i++) {
        float m = s.registeredCourses[i].marks;
        float points = 0;
        if(m >= 80) points = 4.0;
        else if(m >= 75) points = 3.75;
        else if(m >= 70) points = 3.5;
        else if(m >= 65) points = 3.25;
        else if(m >= 60) points = 3.0;
        else if(m >= 55) points = 2.75;
        else if(m >= 50) points = 2.5;
        else if(m >= 45) points = 2.25;
        else if(m >= 40) points = 2.0;
        
        totalPoints += points * s.registeredCourses[i].credit;
        totalCredits += s.registeredCourses[i].credit;
    }
    return (totalCredits > 0) ? (totalPoints / totalCredits) : 0.0;
}

void getGrade(float m, char *g) {
    if(m >= 80) strcpy(g, "A+");
    else if(m >= 75) strcpy(g, "A");
    else if(m >= 70) strcpy(g, "A-");
    else if(m >= 65) strcpy(g, "B+");
    else if(m >= 60) strcpy(g, "B");
    else if(m >= 55) strcpy(g, "B-");
    else if(m >= 50) strcpy(g, "C+");
    else if(m >= 45) strcpy(g, "C");
    else if(m >= 40) strcpy(g, "D");
    else strcpy(g, "F");
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * Project: DIU Student Portal (Daffodil International University)
 * Description: A comprehensive portal for DIU students to manage courses, results, and fees.
 * Estimated Lines: ~380-420
 */

// --------------------------------------------------------------------------
// STRUCTURES
// --------------------------------------------------------------------------
typedef struct {
    char code[15];
    char name[50];
    float credit;
    float marks;
    char grade[5];
} Course;

typedef struct {
    char id[20];        // Format: 221-15-XXXX
    char password[20];
    char name[100];
    char dept[50];
    char campus[20];    // DSC, MC, PC
    int semester;
    Course registeredCourses[6];
    int courseCount;
    float cgpa;
    float totalPayable;
    float waiverPercent;
    float paidAmount;
} Student;

// --------------------------------------------------------------------------
// PROTOTYPES
// --------------------------------------------------------------------------
void loginPanel();
void studentDashboard(char *studentId);
void adminPanel();
void welcomeHeader();

// Admin Functions
void registerNewStudent();
void viewAllStudents();
void updateStudentResult();
void manageFinances();

// Student Functions
void viewProfile(Student s);
void courseRegistration(char *studentId);
void viewSmartResult(Student s);
void showFinancePortal(Student s);
void universityNotices();

// Helpers
void saveStudent(Student s);
void updateStudent(Student s);
Student* findStudent(char *id);
void clearBuffer();
float calculateGPA(Student s);
void getGrade(float marks, char *grade);

#define DB_FILE "diu_students.dat"
#define ADMIN_PASS "2850"

// --------------------------------------------------------------------------
// MAIN
// --------------------------------------------------------------------------
int main() {
    FILE *f = fopen(DB_FILE, "ab"); fclose(f);
    loginPanel();
    return 0;
}

void welcomeHeader() {
    system("cls");
    printf("\n========================================================\n");
    printf("        DAFFODIL INTERNATIONAL UNIVERSITY (DIU)         \n");
    printf("                  STUDENT SMART PORTAL                  \n");
    printf("========================================================\n");
}

void loginPanel() {
    int choice;
    while(1) {
        welcomeHeader();
        printf("1. Student Login\n");
        printf("2. Admin/Registrar Access\n");
        printf("3. Exit System\n");
        printf("Selection: ");
        scanf("%d", &choice);

        if(choice == 1) {
            char id[20], pass[20];
            printf("\nDIU ID (e.g., 221-15-XXX): ");
            scanf("%s", id);
            printf("Password: ");
            scanf("%s", pass);

            Student *s = findStudent(id);
            if(s && strcmp(s->password, pass) == 0) {
                studentDashboard(id);
            } else {
                printf("\nError: ID or Password incorrect!\n");
                system("pause");
            }
            free(s);
        } else if(choice == 2) {
            char pass[20];
            printf("\nEnter Admin Key: ");
            scanf("%s", pass);
            if(strcmp(pass, ADMIN_PASS) == 0) adminPanel();
            else printf("Access Denied.\n");
        } else if(choice == 3) exit(0);
    }
}

// --------------------------------------------------------------------------
// ADMIN PANEL
// --------------------------------------------------------------------------
void adminPanel() {
    int choice;
    while(1) {
        welcomeHeader();
        printf("--- [ REGISTRAR ADMIN PANEL ] ---\n");
        printf("1. Register New Student admission\n");
        printf("2. View Student Directory\n");
        printf("3. Post Semester Marks/Result\n");
        printf("4. Process Waiver & Fees\n");
        printf("5. Logout\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: registerNewStudent(); break;
            case 2: viewAllStudents(); break;
            case 3: updateStudentResult(); break;
            case 4: manageFinances(); break;
            case 5: return;
        }
        system("pause");
    }
}

void registerNewStudent() {
    Student s;
    printf("\n--- New Admission Form ---\n");
    printf("Enter Student ID: "); scanf("%s", s.id);
    
    // Check if duplicate
    Student *check = findStudent(s.id);
    if(check) { printf("Error: ID already exists!\n"); free(check); return; }

    printf("Full Name: "); clearBuffer();
    fgets(s.name, 100, stdin); s.name[strcspn(s.name, "\n")] = 0;
    
    printf("Department (e.g. CSE/EEE/BBA): ");
    scanf("%s", s.dept);
    
    printf("Campus (DSC/MC): ");
    scanf("%s", s.campus);
    
    printf("Initial Semester: ");
    scanf("%d", &s.semester);
    
    printf("Set Portal Password: ");
    scanf("%s", s.password);

    s.courseCount = 0;
    s.cgpa = 0.0;
    s.totalPayable = 850000.0; // Total degree cost estimation
    s.waiverPercent = 0.0;
    s.paidAmount = 0.0;

    saveStudent(s);
    printf("\nSuccess: Student %s registered successfully.\n", s.id);
}

void viewAllStudents() {
    FILE *f = fopen(DB_FILE, "rb");
    Student s;
    printf("\n%-12s %-20s %-10s %-8s %-5s\n", "ID", "Name", "Dept", "Campus", "CGPA");
    printf("------------------------------------------------------------------\n");
    while(fread(&s, sizeof(Student), 1, f)) {
        printf("%-12s %-20s %-10s %-8s %-5.2f\n", s.id, s.name, s.dept, s.campus, s.cgpa);
    }
    fclose(f);
}

// --------------------------------------------------------------------------
// STUDENT DASHBOARD
// --------------------------------------------------------------------------
void studentDashboard(char *studentId) {
    int choice;
    while(1) {
        Student *sptr = findStudent(studentId);
        if(!sptr) return;
        Student s = *sptr; free(sptr);

        welcomeHeader();
        printf("Welcome, %s (%s)\n", s.name, s.id);
        printf("Semester: %d | CGPA: %.2f\n", s.semester, s.cgpa);
        printf("--------------------------------------------------------\n");
        printf("1. View My Profile\n");
        printf("2. Course Registration\n");
        printf("3. Smart Result Inquiry\n");
        printf("4. Accounts & Finance\n");
        printf("5. University Notices\n");
        printf("6. Logout\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: viewProfile(s); break;
            case 2: courseRegistration(s.id); break;
            case 3: viewSmartResult(s); break;
            case 4: showFinancePortal(s); break;
            case 5: universityNotices(); break;
            case 6: return;
        }
        system("pause");
    }
}

void viewProfile(Student s) {
    printf("\n--- [ MY PROFILE ] ---\n");
    printf("Name:     %s\n", s.name);
    printf("ID:       %s\n", s.id);
    printf("Dept:     %s\n", s.dept);
    printf("Campus:   %s\n", s.campus);
    printf("Semester: %d\n", s.semester);
    printf("Courses:  %d Registered\n", s.courseCount);
}

void courseRegistration(char *studentId) {
    Student *sptr = findStudent(studentId);
    if(!sptr) return;
    Student s = *sptr; free(sptr);

    printf("\n--- DIU COURSE REGISTRATION ---\n");
    printf("How many courses to register (Max 6): ");
    int count;
    scanf("%d", &count);
    
    if(count > 6) { printf("Limit exceeded!\n"); return; }
    
    s.courseCount = count;
    for(int i=0; i<count; i++) {
        printf("Course %d Code: ", i+1);
        scanf("%s", s.registeredCourses[i].code);
        printf("Course %d Credit: ", i+1);
        scanf("%f", &s.registeredCourses[i].credit);
        s.registeredCourses[i].marks = 0;
        strcpy(s.registeredCourses[i].grade, "N/A");
    }
    
    updateStudent(s);
    printf("\nRegistration Successful. Waiting for Advisor approval.\n");
}

void viewSmartResult(Student s) {
    printf("\n--- [ SEMESTER RESULT CARD ] ---\n");
    printf("%-15s %-10s %-10s\n", "Course Code", "Marks", "Grade");
    printf("-------------------------------------------\n");
    for(int i=0; i<s.courseCount; i++) {
        printf("%-15s %-10.1f %-10s\n", 
            s.registeredCourses[i].code, 
            s.registeredCourses[i].marks, 
            s.registeredCourses[i].grade);
    }
    printf("-------------------------------------------\n");
    printf("CURRENT CGPA: %.2f\n", s.cgpa);
}

void showFinancePortal(Student s) {
    float waiverAmount = (s.totalPayable * s.waiverPercent) / 100;
    float currentPayable = s.totalPayable - waiverAmount;
    float due = currentPayable - s.paidAmount;

    printf("\n--- [ DIU ACCOUNTS & FINANCE ] ---\n");
    printf("Estimated Degree Cost:  $%10.2f\n", s.totalPayable);
    printf("Applied Waiver (%d%%):  -$%10.2f\n", (int)s.waiverPercent, waiverAmount);
    printf("-------------------------------------------\n");
    printf("Net Payable Amount:     $%10.2f\n", currentPayable);
    printf("Total Amount Paid:      $%10.2f\n", s.paidAmount);
    printf("-------------------------------------------\n");
    printf("CURRENT OUTSTANDING:    $%10.2f\n", due > 0 ? due : 0.0);
}

void universityNotices() {
    printf("\n--- [ DIU NOTICE BOARD ] ---\n");
    printf("1. End-semester exams start from 20th Jan.\n");
    printf("2. Library membership renewal open at PC.\n");
    printf("3. Convocation 2026 registration starts next week.\n");
}

// --------------------------------------------------------------------------
// ADMIN ACTION LOGIC
// --------------------------------------------------------------------------
void updateStudentResult() {
    char id[20];
    printf("Enter Student ID to update marks: ");
    scanf("%s", id);
    Student *sptr = findStudent(id);
    if(!sptr) { printf("Not found.\n"); return; }
    Student s = *sptr; free(sptr);

    printf("Updating results for: %s\n", s.name);
    for(int i=0; i<s.courseCount; i++) {
        printf("Enter marks for %s: ", s.registeredCourses[i].code);
        scanf("%f", &s.registeredCourses[i].marks);
        getGrade(s.registeredCourses[i].marks, s.registeredCourses[i].grade);
    }
    s.cgpa = calculateGPA(s);
    updateStudent(s);
    printf("Results published!\n");
}

void manageFinances() {
    char id[20];
    printf("Enter Student ID: ");
    scanf("%s", id);
    Student *sptr = findStudent(id);
    if(!sptr) return;
    Student s = *sptr; free(sptr);

    int opt;
    printf("1. Set Waiver Percentage\n2. Update Paid Amount\nChoice: ");
    scanf("%d", &opt);
    if(opt == 1) {
        printf("Enter waiver (%%): ");
        scanf("%f", &s.waiverPercent);
    } else {
        float p;
        printf("Enter payment amount: ");
        scanf("%f", &p);
        s.paidAmount += p;
    }
    updateStudent(s);
    printf("Billing updated.\n");
}

// --------------------------------------------------------------------------
// CORE HELPERS
// --------------------------------------------------------------------------
void saveStudent(Student s) {
    FILE *f = fopen(DB_FILE, "ab");
    fwrite(&s, sizeof(Student), 1, f);
    fclose(f);
}

void updateStudent(Student s) {
    FILE *f = fopen(DB_FILE, "rb+");
    Student temp;
    while(fread(&temp, sizeof(Student), 1, f)) {
        if(strcmp(temp.id, s.id) == 0) {
            fseek(f, -(long)sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, f);
            break;
        }
    }
    fclose(f);
}

Student* findStudent(char *id) {
    FILE *f = fopen(DB_FILE, "rb");
    Student *s = (Student*)malloc(sizeof(Student));
    while(fread(s, sizeof(Student), 1, f)) {
        if(strcmp(s->id, id) == 0) {
            fclose(f);
            return s;
        }
    }
    fclose(f);
    free(s);
    return NULL;
}

float calculateGPA(Student s) {
    float totalPoints = 0, totalCredits = 0;
    for(int i=0; i<s.courseCount; i++) {
        float m = s.registeredCourses[i].marks;
        float points = 0;
        if(m >= 80) points = 4.0;
        else if(m >= 75) points = 3.75;
        else if(m >= 70) points = 3.5;
        else if(m >= 65) points = 3.25;
        else if(m >= 60) points = 3.0;
        else if(m >= 55) points = 2.75;
        else if(m >= 50) points = 2.5;
        else if(m >= 45) points = 2.25;
        else if(m >= 40) points = 2.0;
        
        totalPoints += points * s.registeredCourses[i].credit;
        totalCredits += s.registeredCourses[i].credit;
    }
    return (totalCredits > 0) ? (totalPoints / totalCredits) : 0.0;
}

void getGrade(float m, char *g) {
    if(m >= 80) strcpy(g, "A+");
    else if(m >= 75) strcpy(g, "A");
    else if(m >= 70) strcpy(g, "A-");
    else if(m >= 65) strcpy(g, "B+");
    else if(m >= 60) strcpy(g, "B");
    else if(m >= 55) strcpy(g, "B-");
    else if(m >= 50) strcpy(g, "C+");
    else if(m >= 45) strcpy(g, "C");
    else if(m >= 40) strcpy(g, "D");
    else strcpy(g, "F");
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
>>>>>>> da39c685085797a14e004aa3c962df02b596d6ae
