#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct IntArray {
    int* items;
    int length;
} IntArray;

int find(IntArray arr, int value) {
    for (int i = 0; i < arr.length; i++) {
        if (arr.items[i] == value)
            return i;
    }
    return -1;
}

void print(IntArray arr) {
    for (int i = 0; i < arr.length; i++) {
        printf("%d\t", arr.items[i]);
    }
}

void deallocate(IntArray arr) {
    free(arr.items);
}

#endif