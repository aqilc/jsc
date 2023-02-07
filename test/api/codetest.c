#include "tests.h"

#include "../../codegen.h"

TEST("Nothing")
	assert(strcmp(codegen(tokenize("")), "	.globl main\n"
	"main:\n"
	"	movl $1, %eax\n"
	"	ret") == 0);
TEND()

#include "tests_end.h"
