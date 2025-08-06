/*
 *
 *  Inspired by tsoding's implementation at https://github.com/tsoding/arena
 *  Original work licensed under MIT License
 *
 */

#include "arena.h"

static inline size_t align_size(size_t size) {
    return (size + 7) &~7;
}

static inline size_t _strlen(const char* str) {
    size_t len = 0;
    while (*str++) len++;
    return len;
}

Block* new_block(size_t size) {
    size_t capacity = DEFAULT_CAPACITY;

    while (size > capacity) capacity *= 2;

    size_t total_size = sizeof(Block) + sizeof(uintptr_t) * capacity;
    Block* block = (Block*) malloc(total_size);
    assert(block);

    block -> next = NULL;
    block -> usage =  0;
    block -> capacity = capacity;

    return block;
}

void free_block(Block* block) {
    free(block);
}

void* arena_alloc(Arena* arena, size_t size) {
    size = align_size(size);

    if (arena -> end == NULL && arena -> start == NULL) {
        arena -> end = new_block(size);
        arena -> start = arena -> end;
    }

    if (arena -> end -> usage + size > arena -> end -> capacity) {
        Block* block = new_block(size);
        arena -> end -> next = block;
        arena -> end = block;
    }

    size_t i = arena -> end -> usage / sizeof(uintptr_t);
    void* result = (void*) &arena -> end -> data[i];
    arena -> end -> usage += size;

    return result;
}

void* arena_memcpy(void* dest, const void* src, size_t len) {
    char* d = dest;
    const char* s = src;

    while (len > 0) {
        *d++ = *s++;
        len--;
    }

    return dest;
}

char* arena_strdup(Arena* arena, const char* str) {
    size_t len = _strlen(str);
    char* duplicate = (char*) arena_alloc(arena, len + 1);

    arena_memcpy(duplicate, str, len + 1);
    duplicate[len] = '\0';

    return duplicate;
}

void arena_free(Arena* arena) {
    Block* block = arena -> start;

    while (block != NULL) {
        Block* previous = block;
        block = block -> next;
        free_block(previous);
    }

    arena -> start = NULL;
    arena -> end = NULL;
}

size_t total_memory(Arena* arena) {
    Block* current = arena -> start;
    size_t total = 0;

    while (current != NULL) {
        total += current -> usage;
        current = current -> next;
    }
    
    return total;
}
