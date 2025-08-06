#include "../src/arena.h"

#include <stdint.h>
#include <stdio.h>

static Arena arena = {0};

void print_int(int* ptr) {
    printf("addr: %p, val: %d\n", ptr, *ptr);
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
    printf("\n== Total Memory: %zu bytes ==\n", total_memory(&arena));

    arena_free(&arena);
}
