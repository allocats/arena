#include "../src/arena.h"

#include <stdint.h>
#include <stdio.h>

static Arena arena = {0};

void print_int(int* ptr) {
    printf("addr: %p, val: %d\n", ptr, *ptr);
}

void print_arr(int* arr, size_t len) {
    for (size_t i = 0; i < len - 1; i++) {
        printf("%d -> ", arr[i]);
    }
    printf("%d\n", arr[len - 1]);
} 

typedef struct {
    char* name;
    uint8_t age;
    int* memcpy_test;
} Person;

int main() {
    int* a = (int*) arena_alloc(&arena, sizeof(int));
    *a = 12;

    int* b = (int*) arena_alloc(&arena, sizeof(int));
    *b = 2439587;

    print_int(a);
    print_int(b);

    Person* person = (Person*) arena_alloc(&arena, sizeof(Person));

    person -> name = arena_strdup(&arena, "Plink");
    person -> age = 21;
    person -> memcpy_test = (int*) arena_alloc(&arena, sizeof(int));
    arena_memcpy(person -> memcpy_test, b, sizeof(b));

    printf("addr: %p, name: %s, age: %d, memcpy_test: %d\n", person, person -> name, person -> age, *person -> memcpy_test);

    int* arr = (int*) arena_alloc(&arena, sizeof(int) * 2);

    arr[0] = 1;
    arr[1] = 2;
    arr = arena_realloc(&arena, arr, 8, 12);
    arr[2] = 3;
    print_arr(arr, 3);
 
    printf("\n== Usage: %zu / Capacity: %zu bytes ==\n", total_usage(&arena), total_capacity(&arena));
    arena_free(&arena);
}
