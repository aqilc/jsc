/*
 * SINGLE FILE TEST SUITE HEADER MACRO LIB
 * **LIMITED TO 50 TESTS**
 */

#include <stdio.h>
#include <stdbool.h>
// #include <assert.h>

#define assert(x) do { if(x) break; printf("\nLINE %d: Test failed.\n", __LINE__); return 1; } while (0)
#define subtest(x, y) do {\
	subtests_run = true;\
	printf("Subtest '" x "' running");\
	if(x) { puts(" ... passed"); break; }\
	printf("\nLINE %d: Subtest '" x "' failed.\n", __LINE__);\
	return 1;\
} while (0)

int tests_run;
bool subtests_run;

#define TESTINIT
#define TESTCLEAN

#define CONCAT(a, b) a##b
#define MACCONCAT(a, b) CONCAT(a, b)
#define TESTFUNCRET int
#define TESTFUNCARGS (void)
#define TEST(name) \
TESTFUNCRET MACCONCAT(test_, __COUNTER__)TESTFUNCARGS {\
	printf("LINE %d: Running test #%d, \"%s\"", __LINE__, tests_run + 1, name);\
	tests_run++;\
	TESTINIT

#define TEND() TESTCLEAN\
	if(!subtests_run)\
		puts(" ... passed");\
	else puts("All subtests passed.");\
	return 0;\
}


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

// #define EXPAND(...) __VA_ARGS__
#define TESTFUNGEN__(N) TESTFUNC##N
#define TESTFUNGEN_(N) TESTFUNGEN__(N)
#define TESTFUNGEN() TESTFUNGEN_(__COUNTER__)


/*
	Test format:
TEST("name")
	
TEND()
*/

