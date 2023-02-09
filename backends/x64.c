
#include "../util/vec.h"

#define export __declspec(dllexport)

export void cdg_exit(char* p) {
	pushs(p,
	"	xor rax, rax\n"
	"	ret");
}
