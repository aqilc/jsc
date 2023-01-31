// #include "tests.h"

int main() {
	TESTFUNCRET (*testfuncs[])TESTFUNCARGS = { TESTFUNGEN() };
	int failed = 0;
	for (int i = 0, len = __COUNTER__ - 1; i < len; i ++)
		if (testfuncs[i]()) failed ++;
	if(!failed) {
		puts("ALL TESTS PASSED!! Nice job bro.");
		return 0;
	} else if(failed == tests_run) puts("All tests failed. Spectacular.");
	else printf(" %d / %d tests passed.\n", tests_run - failed, tests_run);
	return 1;
}
