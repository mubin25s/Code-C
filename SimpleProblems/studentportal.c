#include <stdio.h>
#include <string.h>

struct Student {
    char id[20];
    char name[50];
    char department[50];
    int age;
    int batch;
    float cgpa;
};

void insertStudent(struct Student *students, int *count, struct Student newStudent) {
    if (*count >= 1000) {
        printf("Storage full.\n");
        return;
    }
    int pos = 0;
    while (pos < *count && strcmp(students[pos].id, newStudent.id) < 0) pos++;
    if (pos < *count && strcmp(students[pos].id, newStudent.id) == 0) {
        printf("Student already exists.\n");
        return;
    }
    if (pos < *count) {
        memmove(&students[pos + 1], &students[pos], (*count - pos) * sizeof(struct Student));
    }
    students[pos] = newStudent;
    (*count)++;
}

void loadStudents(struct Student *students, int *count) {
    FILE *file = fopen("students.txt", "r");
    *count = 0;
    if (!file) return;

    char line[256];
    struct Student s;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%19[^,],%49[^,],%49[^,],%d,%d,%f",
                   s.id, s.name, s.department, &s.age, &s.batch, &s.cgpa) == 6) {
            insertStudent(students, count, s);
        }
    }
    fclose(file);
}

void saveStudents(struct Student *students, int count) {
    FILE *file = fopen("students.txt", "w");
    if (!file) return;

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%s,%s,%d,%d,%.2f\n",
                students[i].id,
                students[i].name,
                students[i].department,
                students[i].age,
                students[i].batch,
                students[i].cgpa);
    }
    fclose(file);
}

int findStudent(struct Student *students, int count, const char *id) {
    int left = 0, right = count - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = strcmp(students[mid].id, id);

        if (cmp == 0) return mid;
        else if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }

    return -1;
}

void displayStudent(struct Student s) {
    printf("ID: %s\n", s.id);
    printf("Name: %s\n", s.name);
    printf("Department: %s\n", s.department);
    printf("Age: %d\n", s.age);
    printf("Batch: %d\n", s.batch);
    printf("CGPA: %.2f\n", s.cgpa);
}

void addStudent(struct Student *students, int *count, const char *id) {
    if (findStudent(students, *count, id) != -1) {
        printf("Student already exists.\n");
        return;
    }

    struct Student s;
    strncpy(s.id, id, sizeof(s.id) - 1);
    s.id[sizeof(s.id) - 1] = '\0';

    printf("Enter name: ");
    scanf(" %49[^\n]", s.name);

    printf("Enter department: ");
    scanf(" %49[^\n]", s.department);

    do {
        printf("Enter age: ");
        scanf("%d", &s.age);

        if (s.age <= 0 || s.age > 30) {
            printf("Invalid age. Please re-enter.\n");
        } else if (s.age < 13) {
            printf("Hmm, this age seems too low for a graduation student. Please re-enter.\n");
        }
    } while (s.age <= 0 || s.age > 30 || s.age < 13);

    printf("Enter batch: ");
    scanf("%d", &s.batch);

    do {
        printf("Enter CGPA: ");
        scanf("%f", &s.cgpa);

        if (s.cgpa < 0 || s.cgpa > 4.00) {
            printf("Maximum CGPA is 4.00. Please enter a valid CGPA.\n");
        }
    } while (s.cgpa < 0 || s.cgpa > 4.00);

    insertStudent(students, count, s);
    printf("Student added successfully.\n");
}

void removeStudent(struct Student *students, int *count, const char *id) {
    int index = findStudent(students, *count, id);
    if (index == -1) {
        printf("No student found with ID %s\n", id);
        return;
    }

    if (index < *count - 1) {
        memmove(&students[index], &students[index + 1], (*count - index - 1) * sizeof(struct Student));
    }
    (*count)--;
    printf("Student removed successfully.\n");
}

int main() {
    struct Student students[1000];
    int count;

    loadStudents(students, &count);

    char pin[10];
    int attempts = 0;

    while (attempts < 15) {
        printf("Enter admin PIN: ");
        scanf("%9s", pin);

        if (strcmp(pin, "1234") == 0) break;

        printf("Incorrect PIN. Try again.\n");
        attempts++;
    }

    if (attempts == 15) {
        printf("Too many failed attempts. Exiting.\n");
        return 0;
    }

    printf("Welcome to the Student Portal\n");

    while (1) {
        int choice;
        printf("\n1. Search Student\n2. Add Student\n3. Remove Student\n4. Exit\nEnter choice: ");

        if (scanf("%d", &choice) != 1) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
            continue;
        }

        if (choice == 1) {
            char id[20];
            printf("Enter student ID: ");
            scanf("%19s", id);

            int index = findStudent(students, count, id);

            if (index != -1) {
                displayStudent(students[index]);
            } else {
                printf("Student not found.\n");
                char choiceStr[10];
                printf("Do you want to add this student? (yes/no): ");
                scanf("%9s", choiceStr);

                for (int i = 0; choiceStr[i]; i++)
                    if (choiceStr[i] >= 'A' && choiceStr[i] <= 'Z')
                        choiceStr[i] += 32;

                if (strcmp(choiceStr, "yes") == 0) {
                    addStudent(students, &count, id);
                    saveStudents(students, count);
                }
            }

        } else if (choice == 2) {
            char id[20];
            printf("Enter student ID: ");
            scanf("%19s", id);

            addStudent(students, &count, id);
            saveStudents(students, count);

        } else if (choice == 3) {
            char id[20];
            printf("Enter student ID to remove: ");
            scanf("%19s", id);

            removeStudent(students, &count, id);
            saveStudents(students, count);

        } else if (choice == 4) {
            printf("Exiting Student Portal.\n");
            break;

        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
