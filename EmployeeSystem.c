#include <stdio.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    float salary;
};

int main() {
    int n, i, j;
    struct Employee temp;

    printf("Enter number of employees: ");
    scanf("%d", &n);

    struct Employee emps[n];

    for (i = 0; i < n; i++) {
        printf("\nEnter details for employee %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &emps[i].id);
        printf("Name: ");
        scanf("%s", emps[i].name);
        printf("Salary: ");
        scanf("%f", &emps[i].salary);
    }

    printf("\nID\tName\t\tSalary\n");
    printf("------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%-10s\t%.2f\n", emps[i].id, emps[i].name, emps[i].salary);
    }

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (emps[j].salary < emps[j + 1].salary) {
                temp = emps[j];
                emps[j] = emps[j + 1];
                emps[j + 1] = temp;
            }
        }
    }

    printf("\nSorted List (by Salary Descending):\n");
    printf("ID\tName\t\tSalary\n");
    printf("------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%-10s\t%.2f\n", emps[i].id, emps[i].name, emps[i].salary);
    }

    return 0;
}
