/*
 * SINGLE FILE TEST SUITE HEADER MACRO LIB
 * **LIMITED TO 50 TESTS**
 https://stackoverflow.com/a/33206814/10013227
 🤬
 */

#include <stdio.h>

int subtests_run = 0;
int subtests_passed = 0;
int asserts = 0;

// Custom assert, requires something to be true to continue with the test.
#define assert(x) do { if(x) {\
	for(int tehueu = -1; tehueu < asserts; tehueu++) printf("\b\b");\
	for(int tehueu = -1; tehueu < asserts; tehueu++) printf("\033[1;32m%c \033[0m", 251);\
	asserts ++; break; \
} printf("\n(%s:%d) \033[1;31mFatal error\033[0m: Assertion '"#x"' failed. Aborting test.\n", __FILE__, __LINE__); return 1; } while (0)

#define SUBTESTINDENT "  "

// A sub test, which checks if something is going according to plan but if it's not, it can still continue
#define subtest(x, y) do {\
	subtests_run++;\
	printf("\n"SUBTESTINDENT"%d) %-*s", subtests_run, 40 - strlen(SUBTESTINDENT), "'"x"'");\
	if(y) { printf("\033[42;30m PASSED \033[0m"); subtests_passed++; break; }\
	printf("\n"SUBTESTINDENT"(%s:%d) \033[1;31mSubtest '" x "' (#%d) failed.\033[0m\n", __FILE__, __LINE__, subtests_run);\
} while (0)


// For subtests with multiple checks
#define substart(x) do {\
	asserts = 0;\
	subtests_run++;\
	printf("\n"SUBTESTINDENT"%d) %-*s", subtests_run, 40 - strlen(SUBTESTINDENT), "'"x"'");\
} while(0)

#define subend(x) do {\
	if(x) { printf("\033[42;30m PASSED \033[0m"); subtests_passed++; break; }\
	printf("\n"SUBTESTINDENT"(%s:%d) \033[1;31mSubtest #%d failed.\033[0m\n", __FILE__, __LINE__, subtests_run);\
} while(0)


// Macro based testing framework starts here -------------------------------------------------------
#define TESTINIT
#define TESTCLEAN

#define CONCAT(a, b) a##b
// #define MACCONCAT(a, b) CONCAT(a, b)
#define TESTFUNCRET int
#define TESTFUNCARGS (void)


#define TEST_(name, N) \
TESTFUNCRET CONCAT(test_, N)TESTFUNCARGS {\
	asserts = 0;\
	printf("%d) %-40.40s", N + 1, "'"name"'");\
	TESTINIT
#define TEST(name) TEST_(name, __COUNTER__)

#define TEND() TESTCLEAN\
	if(!subtests_run)\
		puts("\033[42;30m PASSED \033[0m");\
	else {\
		int allpassed = subtests_run == subtests_passed;\
		if(allpassed) puts("\n"SUBTESTINDENT"All subtests passed.");\
		else printf(SUBTESTINDENT"%d / %d subtests passed.\n", subtests_passed, subtests_run);\
		subtests_run = 0;\
		subtests_passed = 0;\
		if(!allpassed) return 1;\
	}\
	return 0;\
}



#define TESTFUNGEN__(N) TESTFUNC##N
#define TESTFUNGEN_(N) TESTFUNGEN__(N)
#define TESTFUNGEN() TESTFUNGEN_(__COUNTER__)

#define TDELIM ,
#define TESTFUNC0
#define TESTFUNC1 test_0
#define TESTFUNC2 TESTFUNC1 TDELIM test_1
#define TESTFUNC3 TESTFUNC2 TDELIM test_2
#define TESTFUNC4 TESTFUNC3 TDELIM test_3
#define TESTFUNC5 TESTFUNC4 TDELIM test_4
#define TESTFUNC6 TESTFUNC5 TDELIM test_5
#define TESTFUNC7 TESTFUNC6 TDELIM test_6
#define TESTFUNC8 TESTFUNC7 TDELIM test_7
#define TESTFUNC9 TESTFUNC8 TDELIM test_8
#define TESTFUNC10 TESTFUNC9 TDELIM test_9
#define TESTFUNC11 TESTFUNC10 TDELIM test_10
#define TESTFUNC12 TESTFUNC11 TDELIM test_11
#define TESTFUNC13 TESTFUNC12 TDELIM test_12
#define TESTFUNC14 TESTFUNC13 TDELIM test_13
#define TESTFUNC15 TESTFUNC14 TDELIM test_14
#define TESTFUNC16 TESTFUNC15 TDELIM test_15
#define TESTFUNC17 TESTFUNC16 TDELIM test_16
#define TESTFUNC18 TESTFUNC17 TDELIM test_17
#define TESTFUNC19 TESTFUNC18 TDELIM test_18
#define TESTFUNC20 TESTFUNC19 TDELIM test_19
#define TESTFUNC21 TESTFUNC20 TDELIM test_20
#define TESTFUNC22 TESTFUNC21 TDELIM test_21
#define TESTFUNC23 TESTFUNC22 TDELIM test_22
#define TESTFUNC24 TESTFUNC23 TDELIM test_23
#define TESTFUNC25 TESTFUNC24 TDELIM test_24
#define TESTFUNC26 TESTFUNC25 TDELIM test_25
#define TESTFUNC27 TESTFUNC26 TDELIM test_26
#define TESTFUNC28 TESTFUNC27 TDELIM test_27
#define TESTFUNC29 TESTFUNC28 TDELIM test_28
#define TESTFUNC30 TESTFUNC29 TDELIM test_29
#define TESTFUNC31 TESTFUNC30 TDELIM test_30
#define TESTFUNC32 TESTFUNC31 TDELIM test_31
#define TESTFUNC33 TESTFUNC32 TDELIM test_32
#define TESTFUNC34 TESTFUNC33 TDELIM test_33
#define TESTFUNC35 TESTFUNC34 TDELIM test_34
#define TESTFUNC36 TESTFUNC35 TDELIM test_35
#define TESTFUNC37 TESTFUNC36 TDELIM test_36
#define TESTFUNC38 TESTFUNC37 TDELIM test_37
#define TESTFUNC39 TESTFUNC38 TDELIM test_38
#define TESTFUNC40 TESTFUNC39 TDELIM test_39
#define TESTFUNC41 TESTFUNC40 TDELIM test_40
#define TESTFUNC42 TESTFUNC41 TDELIM test_41
#define TESTFUNC43 TESTFUNC42 TDELIM test_42
#define TESTFUNC44 TESTFUNC43 TDELIM test_43
#define TESTFUNC45 TESTFUNC44 TDELIM test_44
#define TESTFUNC46 TESTFUNC45 TDELIM test_45
#define TESTFUNC47 TESTFUNC46 TDELIM test_46
#define TESTFUNC48 TESTFUNC47 TDELIM test_47
#define TESTFUNC49 TESTFUNC48 TDELIM test_48
#define TESTFUNC50 TESTFUNC49 TDELIM test_49



/*
	Test format:
TEST("name")
	subtest("name")
TEND()
*/

