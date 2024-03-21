
struct Student {
    char MSV[15], Name[40];
};

void ghiFile(struct Student dssv[], int n) {
    FILE *file = fopen("E://Dev-Cpp/sinhvien.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%s,%s\n", dssv[i].MSV, dssv[i].Name);
    }

    fclose(file);
}

void readFromFile() {
	FILE *file = fopen("E://Dev-Cpp/sinhvien.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("----------------------------------------------------------------------------------------------------");
    printf("\n|%15s|%28s|", "STUDENT ID", "FULL NAME");
    printf("\n----------------------------------------------------------------------------------------");

    char buffer[100]; // Ð? luu tr? m?i dòng d?c t? t?p tin
    while (fgets(buffer, 100, file) != NULL) {
        char MSV[15], Name[40];
        sscanf(buffer, "%[^,],%[^\n]", MSV, Name);
        printf("\n|%15s|%28s|", MSV, Name);
        printf("\n________________________________________________________________________________________________________________");
    }

    fclose(file);
}


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
    printf("Enter the size of student list: ");
    scanf("%d", &n);
    getchar();

    struct Student dssv[n];

    do {
        printf("\n\nMENU:\n");
        printf("1. Them sinh vien\n");
        printf("2. Cap nhat thong tin sinh vien\n");
        printf("3. Xoa sinh vien\n");
        printf("4. Xuat danh sach sinh vien tu file\n");
        printf("5. Xuat danh sach sinh vien da nhap\n");
        printf("6. Thoat\n");
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);
        getchar(); // Lo?i b? ký t? '\n' trong buffer

        switch (choice) {
            case 1:
                printf("Enter number of students in list: ");
                scanf("%d", &n);
                getchar();

                nhap(dssv, n);
                ghiFile(dssv, n);
                break;
            case 2:
                capNhat(dssv, n);
                break;
            case 3:
                xoa(dssv, &n);
                break;
            case 4:
                readFromFile();
                break;
            case 5:
                xuat(dssv, n);
                break;
            case 6:
                printf("\nExiting program...\n");
                break;
            default:
                printf("\nInvalid choice! Please enter a number between 1 and 4.\n");
                break;
        }
    } while (choice != 6);

    return 0;
}
