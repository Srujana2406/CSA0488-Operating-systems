#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define FILENAME "employee_data.bin"

// Structure to store employee details
struct Employee {
    int id;
    char name[MAX_NAME_LENGTH];
    float salary;
};

// Function to add an employee record to the file
void addEmployee() {
    FILE *file = fopen(FILENAME, "ab");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Employee emp;

    printf("Enter employee ID: ");
    scanf("%d", &emp.id);
    fflush(stdin); // Flush the input buffer
    printf("Enter employee name: ");
    fgets(emp.name, MAX_NAME_LENGTH, stdin);
    emp.name[strcspn(emp.name, "\n")] = 0; // Remove newline character
    printf("Enter employee salary: ");
    scanf("%f", &emp.salary);

    fwrite(&emp, sizeof(struct Employee), 1, file);

    fclose(file);
}

// Function to display all employee records from the file
void displayAllEmployees() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Employee emp;

    printf("Employee Details:\n");
    printf("ID\tName\t\tSalary\n");
    while (fread(&emp, sizeof(struct Employee), 1, file)) {
        printf("%d\t%s\t\t%.2f\n", emp.id, emp.name, emp.salary);
    }

    fclose(file);
}

// Function to search for an employee by ID
void searchEmployeeByID(int id) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Employee emp;
    int found = 0;

    while (fread(&emp, sizeof(struct Employee), 1, file)) {
        if (emp.id == id) {
            printf("Employee found:\n");
            printf("ID: %d\nName: %s\nSalary: %.2f\n", emp.id, emp.name, emp.salary);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", id);
    }

    fclose(file);
}

int main() {
    int choice;
    int id;

    do {
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee by ID\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                displayAllEmployees();
                break;
            case 3:
                printf("Enter employee ID to search: ");
                scanf("%d", &id);
                searchEmployeeByID(id);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}

