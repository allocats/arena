/*
 *
 *  Inspired by tsoding's implementation at https://github.com/tsoding/arena
 *  Original work licensed under MIT License
 *
 */

#ifndef ARENA_H
#define ARENA_H 

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#define DEFAULT_CAPACITY 8 

typedef struct Block {
    struct Block* next;
    size_t usage;
    size_t capacity;
    uintptr_t data[];
} Block;

typedef struct {
    Block* start;
    Block* end;
} Arena;

Block* new_block(size_t size);
void free_block(Block* block);

void* arena_alloc(Arena* arena, size_t size);
void* arena_memcpy(void* dest, const void* src, size_t len);
char* arena_strdup(Arena* arena, const char* str);

void arena_free(Arena* arena); 

size_t total_memory(Arena* arena);

#endif // !ARENA_H
