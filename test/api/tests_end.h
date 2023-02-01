// #include "tests.h"
#include <setjmp.h>

jmp_buf owo;

#if defined(_WIN32)
// WINDOWS WHY ARE YOUR HEADERS SO BIG
#include <errhandlingapi.h>
LONG WINAPI plswork(PEXCEPTION_POINTERS pinfoimaignore) {
	longjmp(owo, 1);
}
#else
#include <signal.h>
static void handler (int sig, siginfo_t* bruh, void* idc) {
	longjmp(owo, 1);
}
#endif

int main() {

	// Win32 so simple
	#if defined(_WIN32)
	// https://stackoverflow.com/questions/1992816/how-to-handle-seg-faults-under-windows
	SetUnhandledExceptionFilter(plswork);

	// f*ck linux bruh
	#else
	// https://stackoverflow.com/questions/10202941/segmentation-fault-handling
	struct sigaction sa = {0};
  sigemptyset(&sa.sa_mask);
  sa.sa_flags     = SA_NODEFER;
  sa.sa_sigaction = handler;
  sigaction(SIGSEGV, &sa, NULL); /* ignore whether it works or not */ 
	#endif
	
	TESTFUNCRET (*testfuncs[])TESTFUNCARGS = { TESTFUNGEN() };
	int failed = 0;
	int tests = __COUNTER__ - 1;
	printf("Executing %d tests.\n", tests);
	for (int i = 0, len = tests; i < len; i ++) {
		if(!setjmp(owo)) {
			if (testfuncs[i]()) failed ++;
		} else {
			char* subtest = "subtest", * test = "test";
			puts("");
			if(subtests_run) printf(SUBTESTINDENT);
			printf("\033[30;41m FATAL ERROR \033[0m Recieved \033[1;31mSIGSEGV\033[0m on %s %d\n",
				subtests_run ? subtest : test,
				(subtests_run > 0 ? subtests_run : i) + 1);
			subtests_run = 0;
			subtests_passed = 0;
			failed ++;
		}
	}
	if(!failed) {
		puts("ALL TESTS PASSED!! Nice job bro.");
		return 0;
	} else if(failed == tests) puts("All tests failed. Spectacular.");
	else printf("%d / %d tests passed.\n", tests - failed, tests);
	return 1;
}
