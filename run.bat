@echo off

rem gcc -E vec.c main.c tok.c


gcc -O3 main.c vec.c tok.c -o main.exe
main.exe
rem gcc -c out.s
