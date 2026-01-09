<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Project: Academic Excellence - Student Record System
 * Description: Management of students, grade recording, and GPA calculation.
 * Estimated Lines: ~350-400
 */

// --------------------------------------------------------------------------
// DATA STRUCTURES
// --------------------------------------------------------------------------
typedef struct {
    char courseCode[10];
    char courseName[30];
    int credits;
    float marks;
    char grade[3];
} AcademicRecord;

typedef struct {
    int id;
    char name[50];
    char department[30];
    int semester;
    AcademicRecord courses[5];
    float sgpa;
    char rank[20];
} Student;

// --------------------------------------------------------------------------
// PROTOTYPES
// --------------------------------------------------------------------------
void login();
void mainMenu();
void studentMenu();
void academicMenu();

void addStudent();
void viewAllStudents();
void searchStudent();
void updateStudentInfo();
void deleteStudent();

void recordMarks();
void calculateGPA(Student *s);
void viewGradeSheet();
void generateReportTable();

// Utils
int getNextStudentId();
void clearBuffer();
float marksToPoints(float marks);
void pointsToGrade(float marks, char *grade);
void saveStudent(Student s);
void updateStudentFile(Student s);

#define STUDENT_FILE "students.dat"
#define ADMIN_PASS "2850"

// --------------------------------------------------------------------------
// MAIN
// --------------------------------------------------------------------------
int main() {
    FILE *f = fopen(STUDENT_FILE, "ab"); fclose(f);
    login();
    mainMenu();
    return 0;
}

void login() {
    char pass[10];
    printf("\n======================================================\n");
    printf("        ACADEMIC EXCELLENCE - STUDENT SYSTEM         \n");
    printf("======================================================\n");
    while(1) {
        printf("\nEnter System Password: ");
        scanf("%s", pass);
        if(strcmp(pass, ADMIN_PASS) == 0) {
            printf("\nAccess Granted. Welcome Administrator.\n");
            break;
        } else {
            printf("Access Denied.\n");
        }
    }
}

// --------------------------------------------------------------------------
// MENUS
// --------------------------------------------------------------------------
void mainMenu() {
    int choice;
    while(1) {
        printf("\n--- [ UNIVERSITY MAIN PANEL ] ---\n");
        printf("1. Student Registry Management\n");
        printf("2. Academic Grading System\n");
        printf("3. General Statistics & Reports\n");
        printf("4. Exit Application\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: studentMenu(); break;
            case 2: academicMenu(); break;
            case 3: generateReportTable(); break;
            case 4: printf("System Shutdown.\n"); exit(0);
            default: printf("Error: Invalid select.\n");
        }
    }
}

void studentMenu() {
    int choice;
    while(1) {
        printf("\n--- [ STUDENT REGISTRY ] ---\n");
        printf("1. Register New Student\n");
        printf("2. View Registry Table\n");
        printf("3. Find Student Profile\n");
        printf("4. Modify Student Data\n");
        printf("5. Delete Record\n");
        printf("6. Back to Main Panel\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(); break;
            case 2: viewAllStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudentInfo(); break;
            case 5: deleteStudent(); break;
            case 6: return;
            default: printf("Invalid Choice.\n");
        }
    }
}

void academicMenu() {
    int choice;
    while(1) {
        printf("\n--- [ ACADEMIC GRADING ] ---\n");
        printf("1. Enter Course Marks\n");
        printf("2. View Individual Grade Sheet\n");
        printf("3. Back to Main Panel\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: recordMarks(); break;
            case 2: viewGradeSheet(); break;
            case 3: return;
            default: printf("Invalid Choice.\n");
        }
    }
}

// --------------------------------------------------------------------------
// REGISTRY LOGIC
// --------------------------------------------------------------------------
void addStudent() {
    Student s;
    s.id = getNextStudentId();
    printf("\n--- Registration (ID: %d) ---\n", s.id);
    printf("Full Name: ");
    clearBuffer();
    fgets(s.name, 50, stdin); s.name[strcspn(s.name, "\n")] = 0;
    printf("Department: ");
    fgets(s.department, 30, stdin); s.department[strcspn(s.department, "\n")] = 0;
    printf("Current Semester: ");
    scanf("%d", &s.semester);
    
    // Initialize marks
    for(int i=0; i<5; i++) {
        s.courses[i].marks = 0;
        strcpy(s.courses[i].grade, "N/A");
    }
    s.sgpa = 0.0;
    strcpy(s.rank, "Pending");

    saveStudent(s);
    printf("Success: %s admitted.\n", s.name);
}

void viewAllStudents() {
    FILE *f = fopen(STUDENT_FILE, "rb");
    if(!f) return;
    Student s;
    printf("\n%-4s %-20s %-15s %-4s %-6s\n", "ID", "Name", "Dept", "Sem", "SGPA");
    printf("------------------------------------------------------------\n");
    while(fread(&s, sizeof(Student), 1, f)) {
        printf("%-4d %-20s %-15s %-4d %-6.2f\n", s.id, s.name, s.department, s.semester, s.sgpa);
    }
    fclose(f);
}

void searchStudent() {
    int id;
    printf("Enter Student ID: ");
    scanf("%d", &id);
    FILE *f = fopen(STUDENT_FILE, "rb");
    Student s;
    int found = 0;
    while(fread(&s, sizeof(Student), 1, f)) {
        if(s.id == id) {
            printf("\n[ PROFILE FOUND ]\nName: %s\nID: %d\nDept: %s\nSem: %d\nSGPA: %.2f | Rank: %s\n", 
                   s.name, s.id, s.department, s.semester, s.sgpa, s.rank);
            found = 1; break;
        }
    }
    if(!found) printf("No record for ID %d.\n", id);
    fclose(f);
}

void updateStudentInfo() {
    int id;
    printf("ID to Update: ");
    scanf("%d", &id);
    FILE *f = fopen(STUDENT_FILE, "rb+");
    Student s;
    int found = 0;
    while(fread(&s, sizeof(Student), 1, f)) {
        if(s.id == id) {
            printf("Updating %s...\nNew Dept: ", s.name);
            clearBuffer();
            fgets(s.department, 30, stdin); s.department[strcspn(s.department, "\n")] = 0;
            printf("New Semester: ");
            scanf("%d", &s.semester);
            fseek(f, -(long)sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, f);
            printf("Success: Record updated.\n");
            found = 1; break;
        }
    }
    fclose(f);
}

void deleteStudent() {
    int id;
    printf("Student ID to Remove: ");
    scanf("%d", &id);
    FILE *f = fopen(STUDENT_FILE, "rb");
    FILE *t = fopen("temp.dat", "wb");
    Student s;
    int found = 0;
    while(fread(&s, sizeof(Student), 1, f)) {
        if(s.id == id) { found = 1; }
        else { fwrite(&s, sizeof(Student), 1, t); }
    }
    fclose(f); fclose(t);
    remove(STUDENT_FILE); rename("temp.dat", STUDENT_FILE);
    if(found) printf("Record deleted.\n");
    else printf("Not found.\n");
}

// --------------------------------------------------------------------------
// ACADEMIC LOGIC
// --------------------------------------------------------------------------
void recordMarks() {
    int id;
    printf("Search ID to grading: ");
    scanf("%d", &id);
    FILE *f = fopen(STUDENT_FILE, "rb+");
    Student s;
    int found = 0;
    while(fread(&s, sizeof(Student), 1, f)) {
        if(s.id == id) {
            printf("\nGrading for: %s\n", s.name);
            for(int i=0; i<5; i++) {
                printf("Course %d Marks (0-100): ", i+1);
                scanf("%f", &s.courses[i].marks);
                pointsToGrade(s.courses[i].marks, s.courses[i].grade);
                s.courses[i].credits = 3; // Default
            }
            calculateGPA(&s);
            fseek(f, -(long)sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, f);
            printf("Academic update success.\n");
            found = 1; break;
        }
    }
    fclose(f);
}

void calculateGPA(Student *s) {
    float totalPoints = 0;
    for(int i=0; i<5; i++) {
        totalPoints += marksToPoints(s->courses[i].marks) * 3;
    }
    s->sgpa = totalPoints / 15.0;
    if(s->sgpa >= 3.7) strcpy(s->rank, "Excellent");
    else if(s->sgpa >= 3.0) strcpy(s->rank, "Good");
    else if(s->sgpa >= 2.0) strcpy(s->rank, "Average");
    else strcpy(s->rank, "Probation");
}

void viewGradeSheet() {
    int id;
    printf("Enter Student ID: ");
    scanf("%d", &id);
    FILE *f = fopen(STUDENT_FILE, "rb");
    Student s;
    while(fread(&s, sizeof(Student), 1, f)) {
        if(s.id == id) {
            printf("\n************************************************\n");
            printf("           OFFICIAL ACADEMIC REPORTCARD         \n");
            printf("************************************************\n");
            printf("Name: %-25s ID: %-5d\n", s.name, s.id);
            printf("Dept: %-25s Semester: %-3d\n", s.department, s.semester);
            printf("------------------------------------------------\n");
            printf("%-10s %-10s %-10s %-10s\n", "Course", "Marks", "Grade", "Points");
            for(int i=0; i<5; i++) {
                printf("Course %d   %-10.1f %-10s %-10.2f\n", 
                       i+1, s.courses[i].marks, s.courses[i].grade, marksToPoints(s.courses[i].marks));
            }
            printf("------------------------------------------------\n");
            printf("SEMESTER GPA: %.2f | RANK: %s\n", s.sgpa, s.rank);
            printf("************************************************\n");
        }
    }
    fclose(f);
}

void generateReportTable() {
    FILE *f = fopen(STUDENT_FILE, "rb");
    Student s;
    printf("\n--- ACADEMIC PERFORMANCE SUMMARY ---\n");
    printf("%-20s %-6s %-12s\n", "NAME", "GPA", "STATUS");
    while(fread(&s, sizeof(Student), 1, f)) {
        printf("%-20s %-6.2f %-12s\n", s.name, s.sgpa, s.rank);
    }
    fclose(f);
}

// --------------------------------------------------------------------------
// HELPERS
// --------------------------------------------------------------------------
float marksToPoints(float marks) {
    if(marks >= 80) return 4.0;
    if(marks >= 70) return 3.5;
    if(marks >= 60) return 3.0;
    if(marks >= 50) return 2.5;
    if(marks >= 40) return 2.0;
    return 0.0;
}

void pointsToGrade(float marks, char *grade) {
    if(marks >= 80) strcpy(grade, "A+");
    else if(marks >= 70) strcpy(grade, "A");
    else if(marks >= 60) strcpy(grade, "B");
    else if(marks >= 50) strcpy(grade, "C");
    else if(marks >= 40) strcpy(grade, "D");
    else strcpy(grade, "F");
}

int getNextStudentId() {
    FILE *f = fopen(STUDENT_FILE, "rb");
    if(!f) return 202401;
    fseek(f, 0, SEEK_END);
    int count = (ftell(f) / sizeof(Student)) + 202401;
    fclose(f);
    return count;
}

void saveStudent(Student s) {
    FILE *f = fopen(STUDENT_FILE, "ab");
    fwrite(&s, sizeof(Student), 1, f);
    fclose(f);
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Project: Academic Excellence - Student Record System
 * Description: Management of students, grade recording, and GPA calculation.
 * Estimated Lines: ~350-400
 */

// --------------------------------------------------------------------------
// DATA STRUCTURES
// --------------------------------------------------------------------------
typedef struct {
    char courseCode[10];
    char courseName[30];
    int credits;
    float marks;
    char grade[3];
} AcademicRecord;

typedef struct {
    int id;
    char name[50];
    char department[30];
    int semester;
    AcademicRecord courses[5];
    float sgpa;
    char rank[20];
} Student;

// --------------------------------------------------------------------------
// PROTOTYPES
// --------------------------------------------------------------------------
void login();
void mainMenu();
void studentMenu();
void academicMenu();

void addStudent();
void viewAllStudents();
void searchStudent();
void updateStudentInfo();
void deleteStudent();

void recordMarks();
void calculateGPA(Student *s);
void viewGradeSheet();
void generateReportTable();

// Utils
int getNextStudentId();
void clearBuffer();
float marksToPoints(float marks);
void pointsToGrade(float marks, char *grade);
void saveStudent(Student s);
void updateStudentFile(Student s);

#define STUDENT_FILE "students.dat"
#define ADMIN_PASS "2850"

// --------------------------------------------------------------------------
// MAIN
// --------------------------------------------------------------------------
int main() {
    FILE *f = fopen(STUDENT_FILE, "ab"); fclose(f);
    login();
    mainMenu();
    return 0;
}

void login() {
    char pass[10];
    printf("\n======================================================\n");
    printf("        ACADEMIC EXCELLENCE - STUDENT SYSTEM         \n");
    printf("======================================================\n");
    while(1) {
        printf("\nEnter System Password: ");
        scanf("%s", pass);
        if(strcmp(pass, ADMIN_PASS) == 0) {
            printf("\nAccess Granted. Welcome Administrator.\n");
            break;
        } else {
            printf("Access Denied.\n");
        }
    }
}

// --------------------------------------------------------------------------
// MENUS
// --------------------------------------------------------------------------
void mainMenu() {
    int choice;
    while(1) {
        printf("\n--- [ UNIVERSITY MAIN PANEL ] ---\n");
        printf("1. Student Registry Management\n");
        printf("2. Academic Grading System\n");
        printf("3. General Statistics & Reports\n");
        printf("4. Exit Application\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: studentMenu(); break;
            case 2: academicMenu(); break;
            case 3: generateReportTable(); break;
            case 4: printf("System Shutdown.\n"); exit(0);
            default: printf("Error: Invalid select.\n");
        }
    }
}

void studentMenu() {
    int choice;
    while(1) {
        printf("\n--- [ STUDENT REGISTRY ] ---\n");
        printf("1. Register New Student\n");
        printf("2. View Registry Table\n");
        printf("3. Find Student Profile\n");
        printf("4. Modify Student Data\n");
        printf("5. Delete Record\n");
        printf("6. Back to Main Panel\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(); break;
            case 2: viewAllStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudentInfo(); break;
            case 5: deleteStudent(); break;
            case 6: return;
            default: printf("Invalid Choice.\n");
        }
    }
}

void academicMenu() {
    int choice;
    while(1) {
        printf("\n--- [ ACADEMIC GRADING ] ---\n");
        printf("1. Enter Course Marks\n");
        printf("2. View Individual Grade Sheet\n");
        printf("3. Back to Main Panel\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: recordMarks(); break;
            case 2: viewGradeSheet(); break;
            case 3: return;
            default: printf("Invalid Choice.\n");
        }
    }
}

// --------------------------------------------------------------------------
// REGISTRY LOGIC
// --------------------------------------------------------------------------
void addStudent() {
    Student s;
    s.id = getNextStudentId();
    printf("\n--- Registration (ID: %d) ---\n", s.id);
    printf("Full Name: ");
    clearBuffer();
    fgets(s.name, 50, stdin); s.name[strcspn(s.name, "\n")] = 0;
    printf("Department: ");
    fgets(s.department, 30, stdin); s.department[strcspn(s.department, "\n")] = 0;
    printf("Current Semester: ");
    scanf("%d", &s.semester);
    
    // Initialize marks
    for(int i=0; i<5; i++) {
        s.courses[i].marks = 0;
        strcpy(s.courses[i].grade, "N/A");
    }
    s.sgpa = 0.0;
    strcpy(s.rank, "Pending");

    saveStudent(s);
    printf("Success: %s admitted.\n", s.name);
}

void viewAllStudents() {
    FILE *f = fopen(STUDENT_FILE, "rb");
    if(!f) return;
    Student s;
    printf("\n%-4s %-20s %-15s %-4s %-6s\n", "ID", "Name", "Dept", "Sem", "SGPA");
    printf("------------------------------------------------------------\n");
    while(fread(&s, sizeof(Student), 1, f)) {
        printf("%-4d %-20s %-15s %-4d %-6.2f\n", s.id, s.name, s.department, s.semester, s.sgpa);
    }
    fclose(f);
}

void searchStudent() {
    int id;
    printf("Enter Student ID: ");
    scanf("%d", &id);
    FILE *f = fopen(STUDENT_FILE, "rb");
    Student s;
    int found = 0;
    while(fread(&s, sizeof(Student), 1, f)) {
        if(s.id == id) {
            printf("\n[ PROFILE FOUND ]\nName: %s\nID: %d\nDept: %s\nSem: %d\nSGPA: %.2f | Rank: %s\n", 
                   s.name, s.id, s.department, s.semester, s.sgpa, s.rank);
            found = 1; break;
        }
    }
    if(!found) printf("No record for ID %d.\n", id);
    fclose(f);
}

void updateStudentInfo() {
    int id;
    printf("ID to Update: ");
    scanf("%d", &id);
    FILE *f = fopen(STUDENT_FILE, "rb+");
    Student s;
    int found = 0;
    while(fread(&s, sizeof(Student), 1, f)) {
        if(s.id == id) {
            printf("Updating %s...\nNew Dept: ", s.name);
            clearBuffer();
            fgets(s.department, 30, stdin); s.department[strcspn(s.department, "\n")] = 0;
            printf("New Semester: ");
            scanf("%d", &s.semester);
            fseek(f, -(long)sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, f);
            printf("Success: Record updated.\n");
            found = 1; break;
        }
    }
    fclose(f);
}

void deleteStudent() {
    int id;
    printf("Student ID to Remove: ");
    scanf("%d", &id);
    FILE *f = fopen(STUDENT_FILE, "rb");
    FILE *t = fopen("temp.dat", "wb");
    Student s;
    int found = 0;
    while(fread(&s, sizeof(Student), 1, f)) {
        if(s.id == id) { found = 1; }
        else { fwrite(&s, sizeof(Student), 1, t); }
    }
    fclose(f); fclose(t);
    remove(STUDENT_FILE); rename("temp.dat", STUDENT_FILE);
    if(found) printf("Record deleted.\n");
    else printf("Not found.\n");
}

// --------------------------------------------------------------------------
// ACADEMIC LOGIC
// --------------------------------------------------------------------------
void recordMarks() {
    int id;
    printf("Search ID to grading: ");
    scanf("%d", &id);
    FILE *f = fopen(STUDENT_FILE, "rb+");
    Student s;
    int found = 0;
    while(fread(&s, sizeof(Student), 1, f)) {
        if(s.id == id) {
            printf("\nGrading for: %s\n", s.name);
            for(int i=0; i<5; i++) {
                printf("Course %d Marks (0-100): ", i+1);
                scanf("%f", &s.courses[i].marks);
                pointsToGrade(s.courses[i].marks, s.courses[i].grade);
                s.courses[i].credits = 3; // Default
            }
            calculateGPA(&s);
            fseek(f, -(long)sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, f);
            printf("Academic update success.\n");
            found = 1; break;
        }
    }
    fclose(f);
}

void calculateGPA(Student *s) {
    float totalPoints = 0;
    for(int i=0; i<5; i++) {
        totalPoints += marksToPoints(s->courses[i].marks) * 3;
    }
    s->sgpa = totalPoints / 15.0;
    if(s->sgpa >= 3.7) strcpy(s->rank, "Excellent");
    else if(s->sgpa >= 3.0) strcpy(s->rank, "Good");
    else if(s->sgpa >= 2.0) strcpy(s->rank, "Average");
    else strcpy(s->rank, "Probation");
}

void viewGradeSheet() {
    int id;
    printf("Enter Student ID: ");
    scanf("%d", &id);
    FILE *f = fopen(STUDENT_FILE, "rb");
    Student s;
    while(fread(&s, sizeof(Student), 1, f)) {
        if(s.id == id) {
            printf("\n************************************************\n");
            printf("           OFFICIAL ACADEMIC REPORTCARD         \n");
            printf("************************************************\n");
            printf("Name: %-25s ID: %-5d\n", s.name, s.id);
            printf("Dept: %-25s Semester: %-3d\n", s.department, s.semester);
            printf("------------------------------------------------\n");
            printf("%-10s %-10s %-10s %-10s\n", "Course", "Marks", "Grade", "Points");
            for(int i=0; i<5; i++) {
                printf("Course %d   %-10.1f %-10s %-10.2f\n", 
                       i+1, s.courses[i].marks, s.courses[i].grade, marksToPoints(s.courses[i].marks));
            }
            printf("------------------------------------------------\n");
            printf("SEMESTER GPA: %.2f | RANK: %s\n", s.sgpa, s.rank);
            printf("************************************************\n");
        }
    }
    fclose(f);
}

void generateReportTable() {
    FILE *f = fopen(STUDENT_FILE, "rb");
    Student s;
    printf("\n--- ACADEMIC PERFORMANCE SUMMARY ---\n");
    printf("%-20s %-6s %-12s\n", "NAME", "GPA", "STATUS");
    while(fread(&s, sizeof(Student), 1, f)) {
        printf("%-20s %-6.2f %-12s\n", s.name, s.sgpa, s.rank);
    }
    fclose(f);
}

// --------------------------------------------------------------------------
// HELPERS
// --------------------------------------------------------------------------
float marksToPoints(float marks) {
    if(marks >= 80) return 4.0;
    if(marks >= 70) return 3.5;
    if(marks >= 60) return 3.0;
    if(marks >= 50) return 2.5;
    if(marks >= 40) return 2.0;
    return 0.0;
}

void pointsToGrade(float marks, char *grade) {
    if(marks >= 80) strcpy(grade, "A+");
    else if(marks >= 70) strcpy(grade, "A");
    else if(marks >= 60) strcpy(grade, "B");
    else if(marks >= 50) strcpy(grade, "C");
    else if(marks >= 40) strcpy(grade, "D");
    else strcpy(grade, "F");
}

int getNextStudentId() {
    FILE *f = fopen(STUDENT_FILE, "rb");
    if(!f) return 202401;
    fseek(f, 0, SEEK_END);
    int count = (ftell(f) / sizeof(Student)) + 202401;
    fclose(f);
    return count;
}

void saveStudent(Student s) {
    FILE *f = fopen(STUDENT_FILE, "ab");
    fwrite(&s, sizeof(Student), 1, f);
    fclose(f);
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
>>>>>>> da39c685085797a14e004aa3c962df02b596d6ae
