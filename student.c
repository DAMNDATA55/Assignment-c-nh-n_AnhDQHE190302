#include <stdio.h>
#include <stdlib.h>

struct Student {
    char name[50];
    int id;
    float gpa;
};

int main() {
    // M? t?p students.dat d? ghi
    FILE *file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("Kh�ng th? m? t?p.\n");
        return 1;
    }

    // T?o v� ghi d? li?u m?u v�o t?p
    struct Student students[3] = {
        {"John", 1, 3.5},
        {"Alice", 2, 3.8},
        {"Bob", 3, 3.2}
    };

    fwrite(students, sizeof(struct Student), 3, file);

    // ��ng t?p
    fclose(file);

    printf("T?p students.dat d� du?c t?o th�nh c�ng v� d? li?u d� du?c ghi v�o.\n");

    return 0;
}
