// #include "tests.h"

int main() {
	TESTFUNCRET (*testfuncs[])TESTFUNCARGS = { TESTFUNGEN() };
	for (int i = 0, len = __COUNTER__ - 1; i < len; i ++) {
		testfuncs[i]();
	}
}
