#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int rollNo;
    char name[50];
    float marks;
};

void addStudent() {
    struct Student s;
    FILE *fp;

    fp = fopen("students.dat", "ab");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &s.rollNo);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(struct Student), 1, fp);

    fclose(fp);

    printf("Student added successfully!\n");
}

void displayStudents() {
    struct Student s;
    FILE *fp;

    fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        printf("\nRoll Number : %d", s.rollNo);
        printf("\nName        : %s", s.name);
        printf("\nMarks       : %.2f\n", s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    struct Student s;
    FILE *fp;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.rollNo == roll) {
            printf("\nStudent Found!\n");
            printf("Roll Number : %d\n", s.rollNo);
            printf("Name        : %s\n", s.name);
            printf("Marks       : %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found!\n");

    fclose(fp);
}

void updateStudent() {
    struct Student s;
    FILE *fp;
    int roll, found = 0;

    fp = fopen("students.dat", "rb+");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Roll Number to update: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct Student), 1, fp)) {

        if (s.rollNo == roll) {

            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(struct Student), SEEK_CUR);

            fwrite(&s, sizeof(struct Student), 1, fp);

            printf("Student updated successfully!\n");

            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found!\n");

    fclose(fp);
}

void deleteStudent() {
    struct Student s;
    FILE *fp, *temp;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct Student), 1, fp)) {

        if (s.rollNo == roll) {
            found = 1;
        } else {
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("Student deleted successfully!\n");
    else
        printf("Student not found!\n");
}

int main() {
    int choice;

    do {
        printf("\n========== STUDENT RECORD MANAGEMENT ==========\n");
        printf("1. Add Student\n");
        printf("2. Delete Student\n");
        printf("3. Update Student\n");
        printf("4. Search Student\n");
        printf("5. Display Students\n");
        printf("6. Exit\n");
        printf("===============================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                addStudent();
                break;

            case 2:
                deleteStudent();
                break;

            case 3:
                updateStudent();
                break;

            case 4:
                searchStudent();
                break;

            case 5:
                displayStudents();
                break;

            case 6:
                printf("Program terminated.\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 6);

    return 0;
}
