UTIL := vec.o hash.o hashfunc.o errors.o
TESTSUITE := tests.h tests_end.h
CC := gcc
CFLAGS := -g

tok: tokenizer.exe

tokenizer.exe: tokenizer.o tok.o $(UTIL)
	$(CC) $^ -o $@

tokenizer.o: tokenizer.c $(TESTSUITE)
	$(CC) $(CFLAGS) -c tokenizer.c -o tokenizer.o




clean:
	del *.o

.PHONY: tok clean

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

