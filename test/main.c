#include "../src/arena.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

static Arena arena = {0};

double get_time_diff(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

void do_work_with_memory(void* ptr, size_t size) {
    memset(ptr, 0x42, size);
    
    char* data = (char*)ptr;
    for (size_t i = 0; i < size; i++) {
        data[i] = (char)(i & 0xFF);
    }
}

void benchmark_malloc_free(int iterations, int allocs_per_iteration) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    for (int iter = 0; iter < iterations; iter++) {
        void** ptrs = malloc(sizeof(void*) * allocs_per_iteration);
        
        for (int i = 0; i < allocs_per_iteration; i++) {
            size_t size = 64 + (i & 1023); 
            ptrs[i] = malloc(size);
            do_work_with_memory(ptrs[i], size);
        }
        
        for (int i = 0; i < allocs_per_iteration; i++) {
            free(ptrs[i]);
        }
        
        free(ptrs);
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = get_time_diff(start, end);
    
    printf("Malloc/Free: %.4f seconds (%d iterations, %d allocs each)\n", time_taken, iterations, allocs_per_iteration);
}

void benchmark_arena_reset(int iterations, int allocs_per_iteration) {
    struct timespec start, end;
    
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    for (int iter = 0; iter < iterations; iter++) {
        arena_reset(&arena);
        
        for (int i = 0; i < allocs_per_iteration; i++) {
            size_t size = 64 + (i & 1023); 
            void* ptr = arena_alloc(&arena, size);
            do_work_with_memory(ptr, size);
        }
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = get_time_diff(start, end);
    printf("Arena Reset: %.4f seconds (%d iterations, %d allocs each)\n", time_taken, iterations, allocs_per_iteration);
    arena_free(&arena);
}

int main() {
    printf("Memory Allocation Benchmark\n");
    printf("===========================\n\n");
    
    const int iterations = 1000;
    const int allocs_per_iteration = 1000;
    
    printf("Test: %d iterations, %d allocations per iteration\n", iterations, allocs_per_iteration);
    printf("Allocation sizes: 64-1063 bytes (variable)\n\n");
    
    benchmark_malloc_free(iterations, allocs_per_iteration);
    benchmark_arena_reset(iterations, allocs_per_iteration);
    
    return 0;
}
