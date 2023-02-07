# https://devblogs.microsoft.com/cppblog/addresssanitizer-asan-for-windows-with-msvc/

UTIL := vec.o hash.o hashfunc.o errors.o
TESTSUITE := tests.h tests_end.h
CC := gcc
CFLAGS := -g


# if ($(OS),Windows_NT)
# 	define _del
# 		del $(1)
# 	endef
# else
# 	define _del
# 		rm $(1)
# 	endef
# endif



all: tok vec code

clean:
	del *.o
	del *.exe

code: codetest.exe
	@codetest.exe
tok: toktest.exe
	@toktest.exe
vec: vectest.exe
	@vectest.exe

.PHONY: tok vec clean



# ============== Test bins ==============
codetest.exe: codetest.o vec.o tok.o codegen.o $(UTIL)
	@$(CC) $^ -o $@
vectest.exe: vectest.o vec.o $(UTIL)
	@$(CC) $^ -o $@
toktest.exe: toktest.o tok.o $(UTIL)
	@$(CC) $^ -o $@

# ============= Test Builds =============
codetest.o: codetest.c $(TESTSUITE)
	$(CC) $(CFLAGS) -c codetest.c -o codetest.o
toktest.o: toktest.c $(TESTSUITE)
	$(CC) $(CFLAGS) -c toktest.c -o toktest.o
vectest.o: vectest.c $(TESTSUITE)
	$(CC) $(CFLAGS) -c vectest.c -o vectest.o

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

