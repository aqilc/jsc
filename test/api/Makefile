# https://devblogs.microsoft.com/cppblog/addresssanitizer-asan-for-windows-with-msvc/


MSVC := ${MSVC}

ifeq ($(MSVC), 1)
	# MSVC
	CC := cl
	CFLAGS := /std:c++17 /EHsc /MDd /Zi /D_CRT_SECURE_NO_WARNINGS
	TCFLAGS := /std:c++17 /EHsc /MDd /Zi /D_CRT_SECURE_NO_WARNINGS
	OBJEND := .obj
	OUTPUTFILENAME := /Fo
	EXENAME := /Fe
	COMPILEFLAG := /c
	LINK := /link /debug
else
	# GCC
	CC := gcc
	CFLAGS := -g -Wall -Wextra -Wpedantic
	TCFLAGS := -g
	OBJEND := .o
	OUTPUTFILENAME := -o 
	EXENAME := -o 
	COMPILEFLAG := -c
	LINK := 
endif


UTIL := vec$(OBJEND) hash$(OBJEND) hashfunc$(OBJEND)
TESTSUITE := tests.h tests_end.h


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
	del *.obj
	del *.bin
	del *.exe
	del *.pdb

code: codetest.exe
	@echo Running '$^'
	@codetest.exe
	@%systemroot%\system32\cmd.exe /C "echo."
tok: toktest.exe
	@echo Running '$^'
	@toktest.exe
	@%systemroot%\system32\cmd.exe /C "echo."
vec: vectest.exe
	@echo Running '$^'
	@vectest.exe
	@%systemroot%\system32\cmd.exe /C "echo."
hash: hashtest.exe
	@echo Running '$^'
	@hashtest.exe
	@%systemroot%\system32\cmd.exe /C "echo."

.PHONY: tok vec hash code clean



# ============== Test bins ==============
codetest.exe: codetest$(OBJEND) tok$(OBJEND) codegen$(OBJEND) errors$(OBJEND) $(UTIL)
	$(CC) $^ $(EXENAME)$@
hashtest.exe: hashtest$(OBJEND) hash$(OBJEND) hashfunc$(OBJEND) $(UTIL)
	$(CC) $^ $(EXENAME)$@
vectest.exe: vectest$(OBJEND) vec$(OBJEND) $(UTIL)
	$(CC) $^ $(EXENAME)$@
toktest.exe: toktest$(OBJEND) tok$(OBJEND) errors$(OBJEND) $(UTIL)
	$(CC) $^ $(EXENAME)$@

# ============= Test Builds =============
codetest$(OBJEND): codetest.c $(TESTSUITE)
	$(CC) $(TCFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<
toktest$(OBJEND): toktest.c $(TESTSUITE)
	$(CC) $(TCFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<
vectest$(OBJEND): vectest.c $(TESTSUITE)
	$(CC) $(TCFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<
hashtest$(OBJEND): hashtest.c ../../util/hash.h $(TESTSUITE)
	$(CC) $(TCFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

# ----------- Base lib builds -----------
vec$(OBJEND): ../../util/vec.c
	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<
hash$(OBJEND): ../../util/hash.c
	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<
hashfunc$(OBJEND): ../../util/hashfunc.c
	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

codegen$(OBJEND): ../../codegen.c
	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<
tok$(OBJEND): ../../tok.c
	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<
errors$(OBJEND): ../../errors.c
	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<
# backend_load$(OBJEND): ../../backend_load.c
# 	$(CC) $(CFLAGS) $(OUTPUTFILENAME)$@ $(COMPILEFLAG) $<

