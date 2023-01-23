@echo off

gcc -O3 main.c tok.c codegen.c util/vec.c util/hash.c util/hashfunc.c -o main.exe
main

rem gcc -E vec.c main.c tok.c
rem gcc -c out.s
