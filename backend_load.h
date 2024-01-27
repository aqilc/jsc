#include "helpers.h"

enum numtype {
	F32, F64, F128, // dk about f128 support but we'll see
	U8, U16, U32, U64,
	I8, I16, I32, I64,
};

union gennum {
	i64 i;
	u64 u;
	float f;
	double d;
};

struct num {
	enum numtype type;
	char* val;
};



// Generates the assembly code for exiting a program.
extern void  (*cdg_exit)(void);

// Generates the bootstrap assembly
extern void  (*cdg_init)(void);

// Returns the string that holds the program
extern char* (*cdg_prog)(void);

// Allocates a variable with size `int`
extern void  (*cdg_var) (int);

// 
extern void  (*cdg_add) (struct num, struct num);


void load_back(char* arch);
