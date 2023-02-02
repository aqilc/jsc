// #include "tests.h"
#include <setjmp.h>

jmp_buf owo;
unsigned int sigthing = 0;

#if defined(_WIN32)
// WINDOWS WHY ARE YOUR HEADERS SO BIG
#include <errhandlingapi.h>
LONG WINAPI plswork(PEXCEPTION_POINTERS pinfo) {
	sigthing = pinfo->ExceptionRecord->ExceptionCode;
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


	// Generates the array of funcs that are the tests in the file
	TESTFUNCRET (*testfuncs[])TESTFUNCARGS = { TESTFUNGEN() };

	// Initializes variables for number of total nad failed tests
	int failed = 0;
	int tests = __COUNTER__ - 1;
	
	printf("Executing %d tests.\n", tests);
	for (int i = 0, len = tests; i < len; i ++) {

		// SigSegV Exception handling
		if(!setjmp(owo)) {
			if (testfuncs[i]()) failed ++;
		} else {
			char* subtest = "subtest", * test = "test";
			puts("");
			if(subtests_run) printf(SUBTESTINDENT);
			printf(TERMREDBGBLACK" FATAL ERROR "TERMRESET" Recieved "TERMREDBOLD);

			#if defined(_WIN32)
			// Found on lines 1350+ in winnt.h
			switch (sigthing) {
				case STATUS_FLOAT_DIVIDE_BY_ZERO: printf("STATUS_FLOAT_DIVIDE_BY_ZERO"); break;
				case STATUS_INTEGER_DIVIDE_BY_ZERO: printf("STATUS_INTEGER_DIVIDE_BY_ZERO"); break;
				case STATUS_STACK_OVERFLOW: printf("STATUS_STACK_OVERFLOW"); break;
				case STATUS_ACCESS_VIOLATION: printf("STATUS_ACCESS_VIOLATION"); break;
				default: printf("STATUS_UNKNOWN (%X)", sigthing);
			}
			#endif
			
			printf(TERMRESET" on %s %d\n",
				subtests_run ? subtest : test,
				(subtests_run > 0 ? subtests_run : i) + 1);
			subtests_run = 0;
			subtests_passed = 0;
			failed ++;
		}
	}
	if(!failed) printf("ALL TESTS PASSED!! Nice job bro.");
	else if(failed == tests) printf("All tests failed. Spectacular.");
	else printf("%d / %d tests passed.", tests - failed, tests);
	printf(" Took "TERMBLUEBOLD"%.1f ms"TERMRESET"\n", totaltime / (double)(CLOCKS_PER_SEC / 1000));
	return 0;
}
