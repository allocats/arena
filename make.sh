rm -rvf build >/dev/null
mkdir -p build/bin

clang -c src/arena.c -o build/arena.o
clang -c test/main.c -o build/main.o

clang build/arena.o build/main.o -o build/bin/main
./build/bin/main
