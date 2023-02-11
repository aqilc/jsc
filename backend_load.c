#include <stdio.h>
#include <stdlib.h>
#include "backend_load.h"

#define GENERIC_FN (void (__cdecl **)(void))

void (*cdg_exit)(char* p);


// Holds function names and the corresponding var ptr to read the func ptr into
typedef struct funcnamesobj {
	char* name;
	void (**func)(void);
} funcnamesobj;
funcnamesobj funcnames[] = {
	"cdg_exit",       GENERIC_FN &cdg_exit
};


#ifdef _WIN32
#include <libloaderapi.h>
void load_arch(char* arch) {
	char buf[50] = {0};
	strcat(buf, arch);
	strcat(buf, ".dll");
	
	HINSTANCE lib = LoadLibrary(TEXT(buf));
	if(!lib) { printf("Could not load library '%s'. Aborting.", buf); abort(); }

	for(int i = 0; i < sizeof(funcnames) / sizeof(funcnamesobj); i ++) {
		*(funcnames[i].func) = (void (__cdecl *)(void)) GetProcAddress(lib, funcnames[i].name);
		if(!*(funcnames[i].func)){ printf("Could not load symbol '%s' in library '%s'. Aborting.", funcnames[i].name, buf); abort(); }
		else printf("Loaded symbol '%s'\n", funcnames[i].name);
	}

	FreeLibrary(lib);

	printf("'%s' Successfully loaded.\n", buf);
}
#else
void load_arch(char* arch) {
	
}	
#endif
