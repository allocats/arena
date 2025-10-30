#!/usr/bin/env bash

mkdir -p build/bin/

clang -O3 -flto -c src/arena.c -o build/arena.o
clang -O3 -flto -mavx2 -c src/arena_avx2.c -o build/arena_avx2.o
clang -O3 -flto -msse2 -c src/arena_sse2.c -o build/arena_sse2.o
clang -O3 -flto -c src/arena_generic.c -o build/arena_generic.o

ar rcs build/bin/libarena.a build/arena.o build/arena_avx2.o build/arena_sse2.o build/arena_generic.o
