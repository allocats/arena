rm -rvf build >/dev/null
mkdir -p build/bin

clang -O3 -c test/main.c -o build/main.o
clang -O3 build/main.o -o build/bin/main

./build/bin/main
