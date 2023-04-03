# https://devblogs.microsoft.com/cppblog/addresssanitizer-asan-for-windows-with-msvc/

UTIL := vec.o hash.o hashfunc.o
TESTSUITE := tests.h tests_end.h
CC := gcc
TCFLAGS := -g
CFLAGS := -g -Wall -Wextra -Wpedantic


# if ($(OS),Windows_NT)
# 	define _del
# 		del $(1)
# 	endef
# else
# 	define _del
# 		rm $(1)
# 	endef
# endif



all: tok vec code hash

clean:
	del *.o
	del *.exe

code: codetest.exe
	@echo Running '$^'
	@codetest.exe
	@echo.
tok: toktest.exe
	@echo Running '$^'
	@toktest.exe
	@echo.
vec: vectest.exe
	@echo Running '$^'
	@vectest.exe
	@echo.
hash: hashtest.exe
	@echo Running '$^'
	@hashtest.exe
	@echo.

.PHONY: tok vec hash code clean



# ============== Test bins ==============
codetest.exe: codetest.o tok.o codegen.o errors.o $(UTIL)
	@$(CC) $^ -o $@
hashtest.exe: hashtest.o hash.o hashfunc.o $(UTIL)
	@$(CC) $^ -o $@
vectest.exe: vectest.o vec.o $(UTIL)
	@$(CC) $^ -o $@
toktest.exe: toktest.o tok.o errors.o $(UTIL)
	@$(CC) $^ -o $@

# ============= Test Builds =============
codetest.o: codetest.c $(TESTSUITE)
	$(CC) $(TCFLAGS) -c codetest.c -o codetest.o
toktest.o: toktest.c $(TESTSUITE)
	$(CC) $(TCFLAGS) -c toktest.c -o toktest.o
vectest.o: vectest.c $(TESTSUITE)
	$(CC) $(TCFLAGS) -c vectest.c -o vectest.o
hashtest.o: hashtest.c ../../util/hash.h $(TESTSUITE)
	$(CC) $(TCFLAGS) -c hashtest.c -o hashtest.o

# ----------- Base lib builds -----------
vec.o: ../../util/vec.c
	$(CC) $(CFLAGS) -c ../../util/vec.c -o vec.o
hash.o: ../../util/hash.c
	$(CC) $(CFLAGS) -c ../../util/hash.c -o hash.o
hashfunc.o: ../../util/hashfunc.c
	$(CC) $(CFLAGS) -c ../../util/hashfunc.c -o hashfunc.o

codegen.o: ../../codegen.c
	$(CC) $(CFLAGS) -c ../../codegen.c -o codegen.o
tok.o: ../../tok.c
	$(CC) $(CFLAGS) -c ../../tok.c -o tok.o
errors.o: ../../errors.c
	$(CC) $(CFLAGS) -c ../../errors.c -o errors.o
# backend_load.o: ../../backend_load.c
# 	$(CC) $(CFLAGS) -c ../../backend_load.c -o backend_load.o

