/* 
Class: bcs-1c
Roll: 25K-0989
Name: Ali Naqi 

Question 3
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[100];
    char designation[50];
    double salary;
} Employee;

/* displayEmployees: prints table-like output */
void displayEmployees(Employee *arr, int n) {
    int i;
    printf("ID\tName\t\tDesignation\tSalary\n");
    printf("-------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%-15s\t%-10s\t%.2f\n", arr[i].id, arr[i].name, arr[i].designation, arr[i].salary);
    }
}

/* findHighestSalary: prints employee with highest salary */
void findHighestSalary(Employee *arr, int n) {
    if (n <= 0) {
        printf("No employees.\n");
        return;
    }
    int idx = 0, i;
    for (i = 1; i < n; i++) {
        if (arr[i].salary > arr[idx].salary) idx = i;
    }
    printf("Highest salary employee:\n");
    printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n", arr[idx].id, arr[idx].name, arr[idx].designation, arr[idx].salary);
}

/* searchEmployee: search by id or name (case-sensitive) */
void searchEmployee(Employee *arr, int n) {
    char mode[10];
    printf("Search by 'id' or 'name': ");
    if (scanf("%9s", mode) != 1) return;
    if (strcmp(mode, "id") == 0) {
        int qid;
        printf("Enter ID: ");
        if (scanf("%d", &qid) != 1) return;
        int i, found = 0;
        for (i = 0; i < n; i++) {
            if (arr[i].id == qid) {
                printf("Found: ID=%d Name=%s Designation=%s Salary=%.2f\n", arr[i].id, arr[i].name, arr[i].designation, arr[i].salary);
                found = 1;
                break;
            }
        }
        if (!found) printf("Not found.\n");
    } else if (strcmp(mode, "name") == 0) {
        char qname[100];
        printf("Enter Name (case-sensitive): ");
        getchar();
        fgets(qname, sizeof(qname), stdin);
        qname[strcspn(qname, "\n")] = '\0';
        int i, found = 0;
        for (i = 0; i < n; i++) {
            if (strcmp(arr[i].name, qname) == 0) {
                printf("Found: ID=%d Name=%s Designation=%s Salary=%.2f\n", arr[i].id, arr[i].name, arr[i].designation, arr[i].salary);
                found = 1;
            }
        }
        if (!found) printf("Not found.\n");
    } else {
        printf("Invalid mode.\n");
    }
}

/* updateSalariesBelowThreshold: demonstrates passing array by reference (Employee* passed and modified in place)
 * gives 10% bonus to those with salary < threshold.
 */
void updateSalariesBelowThreshold(Employee *arr, int n, double threshold) {
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i].salary < threshold) {
            arr[i].salary *= 1.10; /* add 10% */
        }
    }
    printf("Updated salaries for employees earning below %.2f\n", threshold);
}

int main(void) {
    int n, i;
    printf("Enter number of employees: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number.\n");
        return 0;
    }

    /* allocate array */
    Employee *arr = malloc(sizeof(Employee) * n);
    if (!arr) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Employee %d ID: ", i+1);
        scanf("%d", &arr[i].id);
        printf("Name: ");
        getchar(); /* clear newline */
        fgets(arr[i].name, sizeof(arr[i].name), stdin);
        arr[i].name[strcspn(arr[i].name, "\n")] = '\0';
        printf("Designation: ");
        fgets(arr[i].designation, sizeof(arr[i].designation), stdin);
        arr[i].designation[strcspn(arr[i].designation, "\n")] = '\0';
        printf("Salary: ");
        scanf("%lf", &arr[i].salary);
    }

    printf("\nAll employees:\n");
    displayEmployees(arr, n);

    printf("\n");
    findHighestSalary(arr, n);

    printf("\nSearch an employee:\n");
    searchEmployee(arr, n);

    printf("\nApplying 10%% bonus to salaries below 50000 (demo).\n");
    updateSalariesBelowThreshold(arr, n, 50000.0);

    printf("\nEmployees after update:\n");
    displayEmployees(arr, n);

    free(arr);
    return 0;
}
