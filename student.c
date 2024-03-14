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
        printf("Không th? m? t?p.\n");
        return 1;
    }

    // T?o và ghi d? li?u m?u vào t?p
    struct Student students[3] = {
        {"John", 1, 3.5},
        {"Alice", 2, 3.8},
        {"Bob", 3, 3.2}
    };

    fwrite(students, sizeof(struct Student), 3, file);

    // Ðóng t?p
    fclose(file);

    printf("T?p students.dat dã du?c t?o thành công và d? li?u dã du?c ghi vào.\n");

    return 0;
}
