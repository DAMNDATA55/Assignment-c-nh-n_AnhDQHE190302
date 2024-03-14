#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50

// �?nh nghia c?u tr�c Sinh vi�n
typedef struct {
    char name[MAX_NAME_LENGTH];
    int age;
    float gpa;
} Student;

// H�m d? th�m sinh vi�n m?i v�o t?p
void addStudent(FILE *file) {
    Student newStudent;
    printf("Nh?p t�n sinh vi�n: ");
    fgets(newStudent.name, MAX_NAME_LENGTH, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0'; // X�a k� t? '\n' t? fgets
    printf("Nh?p tu?i sinh vi�n: ");
    scanf("%d", &newStudent.age);
    printf("Nh?p di?m trung b�nh: ");
    scanf("%f", &newStudent.gpa);

    // Di chuy?n con tr? t?p d?n cu?i t?p v� ghi d? li?u c?a sinh vi�n m?i v�o t?p
    fseek(file, 0, SEEK_END);
    fwrite(&newStudent, sizeof(Student), 1, file);
    printf("Sinh vi�n d� du?c th�m v�o t?p.\n");
}

// H�m d? hi?n th? danh s�ch sinh vi�n t? t?p
void displayStudents(FILE *file) {
    rewind(file); // �ua con tr? t?p v? d?u t?p
    Student currentStudent;
    printf("\nDanh s�ch sinh vi�n:\n");
    while (fread(&currentStudent, sizeof(Student), 1, file)) {
        printf("T�n: %s, Tu?i: %d, �i?m trung b�nh: %.2f\n", currentStudent.name, currentStudent.age, currentStudent.gpa);
    }
}

// H�m d? c?p nh?t th�ng tin c?a m?t sinh vi�n trong t?p
void updateStudent(FILE *file) {
    int studentIndex;
    printf("Nh?p ch? s? c?a sinh vi�n c?n c?p nh?t: ");
    scanf("%d", &studentIndex);
    fseek(file, studentIndex * sizeof(Student), SEEK_SET); // Di chuy?n con tr? t?p d?n v? tr� c?a sinh vi�n c?n c?p nh?t

    Student updatedStudent;
    printf("Nh?p t�n sinh vi�n m?i: ");
    getchar(); // L?y k� t? '\n' c�n s�t l?i t? scanf tru?c
    fgets(updatedStudent.name, MAX_NAME_LENGTH, stdin);
    updatedStudent.name[strcspn(updatedStudent.name, "\n")] = '\0'; // X�a k� t? '\n' t? fgets
    printf("Nh?p tu?i sinh vi�n m?i: ");
    scanf("%d", &updatedStudent.age);
    printf("Nh?p di?m trung b�nh m?i: ");
    scanf("%f", &updatedStudent.gpa);

    fwrite(&updatedStudent, sizeof(Student), 1, file);
    printf("Th�ng tin sinh vi�n d� du?c c?p nh?t.\n");
}

// H�m d? x�a th�ng tin c?a m?t sinh vi�n kh?i t?p
void deleteStudent(FILE *file) {
    int studentIndex;
    printf("Nh?p ch? s? c?a sinh vi�n c?n x�a: ");
    scanf("%d", &studentIndex);
    fseek(file, studentIndex * sizeof(Student), SEEK_SET); // Di chuy?n con tr? t?p d?n v? tr� c?a sinh vi�n c?n x�a

    // T?o m?t sinh vi�n gi? d? ghi d� l�n sinh vi�n c?n x�a, gi?m k�ch thu?c c?a t?p
    Student emptyStudent = {"", 0, 0.0};
    fwrite(&emptyStudent, sizeof(Student), 1, file);
    printf("Sinh vi�n d� du?c x�a kh?i t?p.\n");
}

int main() {
    FILE *file;
    file = fopen("students.dat", "r+");
    if (file == NULL) {
        printf("Kh�ng th? m? t?p.\n");
        return 1;
    }

    int choice;
    do {
        printf("\nCh?n thao t�c:\n");
        printf("1. Th�m sinh vi�n\n");
        printf("2. Hi?n th? danh s�ch sinh vi�n\n");
        printf("3. C?p nh?t sinh vi�n\n");
        printf("4. X�a sinh vi�n\n");
        printf("5. Tho�t\n");
        printf("Nh?p l?a ch?n c?a b?n: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(file);
                break;
            case 2:
                displayStudents(file);
                break;
            case 3:
                updateStudent(file);
                break;
            case 4:
                deleteStudent(file);
                break;
            case 5:
                printf("K?t th�c chuong tr�nh.\n");
                break;
            default:
                printf("L?a ch?n kh�ng h?p l?. Vui l�ng ch?n l?i.\n");
        }
    } while (choice != 5);

    fclose(file); // ��ng t?p tru?c khi k?t th�c chuong tr�nh
    return 0;
}

