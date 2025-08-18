#include "../src/arena.h"
#include <stdio.h>

// Define arena and initialise it
static Arena arena = {0};

typedef struct ListNode {
    struct ListNode* next;
    int value;
} ListNode;

int main() {
    int* arr = arena_array(&arena, int, 10);

    for (int i = 0; i < 10; i++) {
        arr[i] = i;
        printf("%d ", arr[i]);
    }

    char* msg = arena_strdup(&arena, "Hi there");
    printf("%s\n", msg);

    ListNode* node = arena_alloc(&arena, sizeof(ListNode));
    node -> next = NULL;
    node -> value = 9;
    printf("node value: %d\n", node -> value);

    arena_free(&arena);
}
