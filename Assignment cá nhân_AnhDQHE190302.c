#include <stdio.h>
#include <string.h>

struct Student {
    char MSV[15], Name[40];
};

void nhap(struct Student dssv[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("NHAP THONG TIN CUA SINH VIEN THU %d", i + 1);
        printf("\nNhap Ho ten cua sinh vien : ");
        fgets(dssv[i].Name, 40, stdin);
        dssv[i].Name[strcspn(dssv[i].Name, "\n")] = 0;
        printf("\nNhap ma so sinh vien: ");
        fgets(dssv[i].MSV, 15, stdin);
        dssv[i].MSV[strcspn(dssv[i].MSV, "\n")] = 0;
    }
}

void xuat(struct Student dssv[], int n) {
    int i = 0;
    printf("----------------------------------------------------------------------------------------------------");
    printf("\n|%15s|%28s|", "STUDENT ID", "FULL NAME");
    printf("\n----------------------------------------------------------------------------------------");
    for (i; i < n; i++) {
        printf("\n|%15s|%28s|", dssv[i].MSV, dssv[i].Name);
        printf("\n________________________________________________________________________________________________________________");
    }
}

int timSinhVien(struct Student dssv[], int n, char MSV[]) {
    int i;
    for (i = 0; i < n; i++) {
        if (strcmp(dssv[i].MSV, MSV) == 0) {
            return i; // Tr? v? ch? s? c?a sinh viên trong danh sách
        }
    }
    return -1; // Tr? v? -1 n?u không tìm th?y sinh viên
}

void capNhat(struct Student dssv[], int n) {
    char MSV[15];
    printf("\nEnter Student ID to update: ");
    fgets(MSV, 15, stdin);
    MSV[strcspn(MSV, "\n")] = 0;
    int index = timSinhVien(dssv, n, MSV);
    if (index != -1) {
        printf("\nEnter new Name: ");
        fgets(dssv[index].Name, 40, stdin);
        dssv[index].Name[strcspn(dssv[index].Name, "\n")] = 0;
        printf("\nStudent information updated successfully!\n");
    } else {
        printf("\nStudent not found!\n");
    }
}

void xoa(struct Student dssv[], int *n) {
    char MSV[15];
    printf("\nEnter Student ID to delete: ");
    fgets(MSV, 15, stdin);
    MSV[strcspn(MSV, "\n")] = 0;
    int index = timSinhVien(dssv, *n, MSV);
    if (index != -1) {
        int i;
        for (i = index; i < *n - 1; i++) {
            dssv[i] = dssv[i + 1]; // D?ch chuy?n các sinh viên phía sau lên tru?c
        }
        (*n)--; // Gi?m s? lu?ng sinh viên di 1
        printf("\nStudent deleted successfully!\n");
    } else {
        printf("\nStudent not found!\n");
    }
}

int main() {
    int choice, n;
    printf("Enter number of students in list: ");
    scanf("%d", &n);
    getchar();
    struct Student dssv[n];
    nhap(dssv, n);
    xuat(dssv, n);

    do {
        printf("\n\nMENU:\n");
        printf("1. Cap nhat thong tin sinh vien\n");
        printf("2. Xoa sinh vien\n");
        printf("3. Xuat danh sach sinh vien\n");
        printf("4. Thoat\n");
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);
        getchar(); // Lo?i b? ký t? '\n' trong buffer

        switch (choice) {
            case 1:
                capNhat(dssv, n);
                break;
            case 2:
                xoa(dssv, &n);
                break;
            case 3:
                xuat(dssv, n);
                break;
            case 4:
                printf("\nExiting program...\n");
                break;
            default:
                printf("\nInvalid choice! Please enter a number between 1 and 4.\n");
                break;
        }
    } while (choice != 4);

    return 0;
}
