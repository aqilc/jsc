# How to complete port to Unix

I have not been able to debug, or even work on the Unix port to this compiler because I don't have a suitable machine.

The files that need to be ported as of now:
- `/test/api/tests_end.h`
	- (~lines 18, 68) Figure out how to identify SIGNAL, and write the appropriate output for test. CRUCIAL step to start testing on Linux, BSD, Mac OS.
- `/backend_load.c`
	- Need to completely implement Unix version for .a files.
- `/Makefile`
	- Theorhetically already ported, just need to properly test endings and build.
