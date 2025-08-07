# Arena Allocator   

Arena Allocator in C, arenas work by allocating memory up front then segmenting it up into smaller pieces. Greatly reducing malloc() and free() calls. It also provides a safer way of managing memory, one only has to call arena_free() at the end to free all allocated memory. 

## Setup  

To use the arena allocator, you **must** define `USING_ARENA` **before** including the header:
`
#define USING_ARENA
#include "arena.h"
`

## API

#### Allocation
`
void* arena_alloc(Arena* arena, size_t size);
void* arena_realloc(Arena* arena, void* ptr, size_t old_size, size_t new_size);
`
#### Memory Utilities
`
void* arena_memset(void* ptr, int value, size_t len);
void* arena_memcpy(void* dest, const void* src, size_t len);
char* arena_strdup(Arena* arena, const char* str);
`
#### Freeing and Management  
`
void arena_reset(Arena* arena); // Resets arena for reuse
void arena_free(Arena* arena);  // Frees all memory
`
#### Array Macros
```
#define arena_array(arena, type, count) \  
    (type*) arena_alloc(arena, sizeof(type) * (count))  

#define arena_array_zero(arena, type, count) \  
    (type*) arena_memset(arena_alloc(arena, sizeof(type) * (count)), 0, sizeof(type) * (count))  
```

## Credits
  
This was inspired by tsoding's implementation ([arena](https://github.com/tsoding/arena)).  
