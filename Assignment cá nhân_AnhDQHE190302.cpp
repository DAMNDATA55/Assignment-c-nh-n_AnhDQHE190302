#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50

// Ð?nh nghia c?u trúc Sinh viên
typedef struct {
    char name[MAX_NAME_LENGTH];
    int age;
    float gpa;
} Student;

// Hàm d? thêm sinh viên m?i vào t?p
void addStudent(FILE *file) {
    Student newStudent;
    printf("Nh?p tên sinh viên: ");
    fgets(newStudent.name, MAX_NAME_LENGTH, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0'; // Xóa ký t? '\n' t? fgets
    printf("Nh?p tu?i sinh viên: ");
    scanf("%d", &newStudent.age);
    printf("Nh?p di?m trung bình: ");
    scanf("%f", &newStudent.gpa);

    // Di chuy?n con tr? t?p d?n cu?i t?p và ghi d? li?u c?a sinh viên m?i vào t?p
    fseek(file, 0, SEEK_END);
    fwrite(&newStudent, sizeof(Student), 1, file);
    printf("Sinh viên dã du?c thêm vào t?p.\n");
}

// Hàm d? hi?n th? danh sách sinh viên t? t?p
void displayStudents(FILE *file) {
    rewind(file); // Ðua con tr? t?p v? d?u t?p
    Student currentStudent;
    printf("\nDanh sách sinh viên:\n");
    while (fread(&currentStudent, sizeof(Student), 1, file)) {
        printf("Tên: %s, Tu?i: %d, Ði?m trung bình: %.2f\n", currentStudent.name, currentStudent.age, currentStudent.gpa);
    }
}

// Hàm d? c?p nh?t thông tin c?a m?t sinh viên trong t?p
void updateStudent(FILE *file) {
    int studentIndex;
    printf("Nh?p ch? s? c?a sinh viên c?n c?p nh?t: ");
    scanf("%d", &studentIndex);
    fseek(file, studentIndex * sizeof(Student), SEEK_SET); // Di chuy?n con tr? t?p d?n v? trí c?a sinh viên c?n c?p nh?t

    Student updatedStudent;
    printf("Nh?p tên sinh viên m?i: ");
    getchar(); // L?y ký t? '\n' còn sót l?i t? scanf tru?c
    fgets(updatedStudent.name, MAX_NAME_LENGTH, stdin);
    updatedStudent.name[strcspn(updatedStudent.name, "\n")] = '\0'; // Xóa ký t? '\n' t? fgets
    printf("Nh?p tu?i sinh viên m?i: ");
    scanf("%d", &updatedStudent.age);
    printf("Nh?p di?m trung bình m?i: ");
    scanf("%f", &updatedStudent.gpa);

    fwrite(&updatedStudent, sizeof(Student), 1, file);
    printf("Thông tin sinh viên dã du?c c?p nh?t.\n");
}

// Hàm d? xóa thông tin c?a m?t sinh viên kh?i t?p
void deleteStudent(FILE *file) {
    int studentIndex;
    printf("Nh?p ch? s? c?a sinh viên c?n xóa: ");
    scanf("%d", &studentIndex);
    fseek(file, studentIndex * sizeof(Student), SEEK_SET); // Di chuy?n con tr? t?p d?n v? trí c?a sinh viên c?n xóa

    // T?o m?t sinh viên gi? d? ghi dè lên sinh viên c?n xóa, gi?m kích thu?c c?a t?p
    Student emptyStudent = {"", 0, 0.0};
    fwrite(&emptyStudent, sizeof(Student), 1, file);
    printf("Sinh viên dã du?c xóa kh?i t?p.\n");
}

int main() {
    FILE *file;
    file = fopen("students.dat", "r+");
    if (file == NULL) {
        printf("Không th? m? t?p.\n");
        return 1;
    }

    int choice;
    do {
        printf("\nCh?n thao tác:\n");
        printf("1. Thêm sinh viên\n");
        printf("2. Hi?n th? danh sách sinh viên\n");
        printf("3. C?p nh?t sinh viên\n");
        printf("4. Xóa sinh viên\n");
        printf("5. Thoát\n");
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
                printf("K?t thúc chuong trình.\n");
                break;
            default:
                printf("L?a ch?n không h?p l?. Vui lòng ch?n l?i.\n");
        }
    } while (choice != 5);

    fclose(file); // Ðóng t?p tru?c khi k?t thúc chuong trình
    return 0;
}

