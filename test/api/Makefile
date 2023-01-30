UTIL := vec.o hash.o hashfunc.o errors.o
CC := gcc
CFLAGS := -o2

tok: tokenizer.exe

tokenizer.exe: tokenizer.o tok.o $(UTIL)
	$(CC) $^ -o $@

tokenizer.o: tokenizer.c
	$(CC) $(CFLAGS) -c tokenizer.c -o tokenizer.o




clean:
	del *.o

.PHONY: tok clean

# ----------- Base lib builds -----------
vec.o: ../../util/vec.c
	$(CC) $(CFLAGS) -c ../../util/vec.c -o vec.o
tok.o:
	$(CC) $(CFLAGS) -c ../../tok.c -o tok.o
errors.o:
	$(CC) $(CFLAGS) -c ../../errors.c -o errors.o
hash.o:
	$(CC) $(CFLAGS) -c ../../util/hash.c -o hash.o
hashfunc.o:
	$(CC) $(CFLAGS) -c ../../util/hashfunc.c -o hashfunc.o

