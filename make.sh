rm -rvf build >/dev/null
mkdir -p build/bin

clang -O3 -c src/arena.c -o build/arena.o
clang -O3 -c test/main.c -o build/main.o

clang -O3 build/arena.o build/main.o -o build/bin/main
./build/bin/main
