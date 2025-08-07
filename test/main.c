#include "../src/arena.h"
#include <stdio.h>

static Arena arena = {0};

int main() {
    int* arr = arena_array_zero(&arena, int, 10);


    for (int i = 0; i < 10; i++) {
        arr[i] = i;
        printf("%d ", arr[i]);
    }

    arena_free(&arena);
}
