#include <stdio.h>
#include <string.h>

struct Student {
    char MSV[15], Name[40];
};

void writeFile(struct Student dssv[], int n) {
	int i;
    FILE *file = fopen("E://Dev-Cpp/Assingment cá nhân_AnhDQHE190302/students.dat/sinhvien.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (i = 0; i < n; i++) {
        fprintf(file, "%s,%s\n", dssv[i].MSV, dssv[i].Name);
    }

    fclose(file);
}

void readFromFile() {
    FILE *file = fopen("E://Dev-Cpp/Assingment cá nhân_AnhDQHE190302/students.dat/sinhvien.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("----------------------------------------------------------------------------------------------------");
    printf("\n|%15s|%28s|", "STUDENT ID", "FULL NAME");
    printf("\n----------------------------------------------------------------------------------------");

    char buffer[100]; // To store each line read from the file
    while (fgets(buffer, 100, file) != NULL) {
        char MSV[15], Name[40];
        sscanf(buffer, "%[^,],%[^\n]", MSV, Name);
        printf("\n|%15s|%28s|", MSV, Name);
        printf("\n________________________________________________________________________________________________________________");
    }

    fclose(file);
}


void input(struct Student dssv[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("ENTER INFORMATION OF STUDENT %d\n", i + 1);
        printf("Enter Full Name: ");
        fgets(dssv[i].Name, 40, stdin);
        dssv[i].Name[strcspn(dssv[i].Name, "\n")] = 0;
        printf("Enter Student ID: ");
        fgets(dssv[i].MSV, 15, stdin);
        dssv[i].MSV[strcspn(dssv[i].MSV, "\n")] = 0;
    }
}

void display(struct Student dssv[], int n) {
    int i = 0;
    printf("----------------------------------------------------------------------------------------------------");
    printf("\n|%15s|%28s|", "STUDENT ID", "FULL NAME");
    printf("\n----------------------------------------------------------------------------------------");
    for (i; i < n; i++) {
        printf("\n|%15s|%28s|", dssv[i].MSV, dssv[i].Name);
        printf("\n________________________________________________________________________________________________________________");
    }
}

int findStudent(struct Student dssv[], int n, char MSV[]) {
    int i;
    for (i = 0; i < n; i++) {
        if (strcmp(dssv[i].MSV, MSV) == 0) {
            return i; // Return the index of the student in the list
        }
    }
    return -1; // Return -1 if student not found
}

void update(struct Student dssv[], int n) {
    char MSV[15];
    printf("\nEnter Student ID to update: ");
    fgets(MSV, 15, stdin);
    MSV[strcspn(MSV, "\n")] = 0;
    int index = findStudent(dssv, n, MSV);
    if (index != -1) {
        printf("\nEnter new Name: ");
        fgets(dssv[index].Name, 40, stdin);
        dssv[index].Name[strcspn(dssv[index].Name, "\n")] = 0;
        printf("\nStudent information updated successfully!\n");
    } else {
        printf("\nStudent not found!\n");
    }
}

void delete(struct Student dssv[], int *n) {
    char MSV[15];
    printf("\nEnter Student ID to delete: ");
    fgets(MSV, 15, stdin);
    MSV[strcspn(MSV, "\n")] = 0;
    int index = findStudent(dssv, *n, MSV);
    if (index != -1) {
        int i;
        for (i = index; i < *n - 1; i++) {
            dssv[i] = dssv[i + 1]; // Shift the remaining students up
        }
        (*n)--; // Decrease the number of students by 1
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
        printf("1. Add Student\n");
        printf("2. Update Student Information\n");
        printf("3. Delete Student\n");
        printf("4. Display Student List from File\n");
        printf("5. Display Entered Student List\n");
        printf("6. Exit\n");
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);
        getchar(); // Discard the newline character from the buffer

        switch (choice) {
            case 1:
                printf("Enter number of students in list: ");
                scanf("%d", &n);
                getchar();
                input(dssv, n);
                writeFile(dssv, n);
                break;
            case 2:
                update(dssv, n);
                writeFile(dssv, n);
                break;
            case 3:
                delete(dssv, &n);
                writeFile(dssv, n);
                break;
            case 4:
                readFromFile();
                break;
            case 5:
                display(dssv, n);
                break;
            case 6:
                printf("\nExiting program...\n");
                break;
            default:
                printf("\nInvalid choice! Please enter a number between 1 and 6.\n");
                break;
        }
    } while (choice != 6);

    return 0;
}
