#ifndef UTILS_H
#define UTILS_H

#include <stdarg.h>
#include <stdio.h>

int choice(
    const char* label,
    ...
) {
    int count = 0;

    va_list ptr;
    va_start(ptr, label);

    printf("\n%s %s %s\n", "\x1B[1m", label, "\x1B[0m");
    while (ptr) {
        count++;
        const char* option = va_arg(ptr, const char*);
        if (!option)
            break;

        printf("%d. %s\n", count, option);
    }

    int choice = -1;
    char valid = 0;
    do {
        printf("Choose an option: ");
        scanf("%d", &choice);

        valid = 0 < choice && choice < count;
    } while (!valid);

    va_end(ptr);
    printf("\n");

    return choice;
}

void printMat(int row, int col, int (*mat)[col]) {
    for (int i = 0;  i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}

#endif