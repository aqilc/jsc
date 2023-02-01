#include <stdlib.h>
#include "tests.h"
#include "../../util/vec.h"

struct big { u64 i,j,k,l,m,n,o,p,q,r,s,t,w,x,y,z,a,b,c,d,e,f,g,h; };

TEST("Vector free")
	vfree(vnew());
TEND()

TEST("Vector push")

	substart("Push single char");
		char* v = vnew();
		push(v, 'a');
		assert(v[0] == 'a');
		assert(vlen(v) == 1);
	subend(1);
	vfree(v);

	struct big* w = vnew();
	push(w, { .a = 5 });
	subtest("Push big struct", w[0].a == 5);
	vfree(w);

	// ((char*)(0))[100000] = 0;


	substart("Push strings");
	
		// Smol string test
		char* s = vnew();
		pushs(s, "smolstring");
		assert(vlen(s) == 10);

		// Big string test just to make sure
		#define BIGBUFLEN 20000000
		char* bigbuf = malloc(BIGBUFLEN);
		memset(bigbuf, 's', BIGBUFLEN - 1);
		bigbuf[BIGBUFLEN - 1] = 0;
		pushs(s, bigbuf);
		free(bigbuf);
		assert(s[BIGBUFLEN - 230]);
		assert(vlen(s) == BIGBUFLEN + 10 - 1);
	subend(1);
	vfree(s);


	char* s2 = vnew();
	printf("%d%f%s", 10, 1.2, "hi");
	subtest("Push formatted string", vlen(s2) == 12);
TEND()

TEST("Vector clear")
	struct big* v = vnew();
	push(v, {});
	push(v, {});
	push(v, {});

	vclear(v);
	assert(vlen(v) == 0);
TEND();


#include "tests_end.h"
