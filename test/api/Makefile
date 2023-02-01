UTIL := vec.o hash.o hashfunc.o errors.o
TESTSUITE := tests.h tests_end.h
CC := gcc
CFLAGS := -g

all: tok vec

clean:
	@del *.o
	@del *.exe

tok: toktest.exe
	@toktest
vec: vectest.exe
	@vectest

.PHONY: tok vec clean



# ============== Test bins ==============
vectest.exe: vectest.o vec.o $(UTIL)
	@$(CC) $^ -o $@
toktest.exe: toktest.o tok.o $(UTIL)
	@$(CC) $^ -o $@

# ============= Test Builds =============
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

tok.o: ../../tok.c
	$(CC) $(CFLAGS) -c ../../tok.c -o tok.o
errors.o: ../../errors.c
	$(CC) $(CFLAGS) -c ../../errors.c -o errors.o

