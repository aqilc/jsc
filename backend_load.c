#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "backend_load.h"



#define GENERIC_FN (void (__cdecl *)())
#define GENERIC_FN_PTR (void (__cdecl **)())

// Func ptr definitions
void  (*cdg_exit)(void);
void  (*cdg_init)(void);
char* (*cdg_prog)(void);
void  (*cdg_var) (int);
void  (*cdg_add) (struct num, struct num);

// Holds function names and the corresponding var ptr to read the func ptr into
struct funcnamesobj {
	char* name;
	bool req;
	void (**func)(void);
} funcnames[] = {
	"cdg_exit",       true, GENERIC_FN_PTR &cdg_exit,
	"cdg_init",       true, GENERIC_FN_PTR &cdg_init,
	"cdg_prog",       true, GENERIC_FN_PTR &cdg_prog,
	"cdg_var",        true, GENERIC_FN_PTR &cdg_var,
	"cdg_add",        true, GENERIC_FN_PTR &cdg_add,

};




#ifdef _WIN32
	#include <libloaderapi.h>

	HINSTANCE lib = NULL;
	void load_back(char* arch) {
		char buf[50] = {0};
		strcat(buf, arch);
		strcat(buf, ".dll");
		
		if(lib) FreeLibrary(lib);
		lib = LoadLibrary(TEXT(buf));
		if(!lib) { printf("Could not load library '%s'. Aborting.", buf); abort(); }

		for(int i = 0; i < sizeof(funcnames) / sizeof(struct funcnamesobj); i ++) {
			*(funcnames[i].func) = GENERIC_FN GetProcAddress(lib, funcnames[i].name);
			if(!*(funcnames[i].func))
				printf("Warning: Could not load symbol '%s' in library '%s'.", funcnames[i].name, buf);
			// else printf("Loaded symbol '%s'\n", funcnames[i].name);
		}

		// printf("'%s' Successfully loaded.\n", buf);
	}
#else
	void load_back(char* arch) {
		
	}
#endif
