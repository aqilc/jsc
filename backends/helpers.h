#include "../helpers.h"

#ifdef _WIN32
	#define export(x) __declspec(dllexport) cdg_##x
#else
	#define export(x) cdg_##x
#endif

#define INS(X) "	" X "\n"
#define ins(v, ...) pushs(v, FOR_EACH(INS, __VA_ARGS__))
