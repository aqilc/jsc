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

	substart("Push strings");
	
		// Smol string test
		char* s = vnew();
		pushs(s, "smolstring");
		assert(vlen(s) == 10);

		// Big string test just to make sure
		#define BIGBUFLEN 200000
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
	pushsf(s2, "%d%f%s", 10, 1.2, "hi");
	subtest("Push formatted string", vlen(s2) == 12);
	vfree(s2);

	char* n1 = vnew();
	pushn(n1, 10, 'a');
	subtest("Pushn: `char`", vlen(n1) == 10);
	vfree(n1);

	substart("Pushn: `u32`");
		u32* n2 = vnew();
		pushn(n2, 10, 9120192);
		asserteq(_DATA(n2)->used, 10 * sizeof(u32));
	subend(vlen(n2) == 10);
	vfree(n2);
	

	substart("Pushnst: Big structs");
		struct big* n3 = vnew();
		pushnst(n3, 20, {0});
		asserteq(_DATA(n3)->used, 20 * sizeof(struct big));
	subend(vlen(n3) == 20);
	vfree(n3);
TEND()

struct random {
	struct big* hi;
};

TEST("Vector clear")
	struct big* v = vnew();
	push(v, {});
	push(v, {});
	push(v, {});

	vclear(v);
	subtest("Clear initial", vlen(v) == 0);

	push(v, {});
	push(v, {});
	push(v, {});
	push(v, {});
	assert(vlen(v) == 4);
	
	vclear(v);
	subtest("Clear again", vlen(v) == 0);

	// substart("Stress test");
	u8 halfway_reached = 0;
	for(int i = 0; i < 10000; i += 80000000 / (i + 40000)) {
		pushn(v, i,);
		assert(vlen(v) == i);
		vclear(v); 
		if(i == 0) subtest("Stresstest: empty", vlen(v) == 0);
		if(!halfway_reached && i >= 5000) { halfway_reached = 1; subtest("Stresstest: >5k", vlen(v) == 0); }
	}
	subtest("Stresstest: Finished", 1);
	vfree(v);
	

	struct random* hi = malloc(sizeof(struct random));
	hi->hi = vnew();
	push(hi->hi, {});
	push(hi->hi, {});
	push(hi->hi, {});

	vclear(hi->hi);
	subtest("Subfield: Clear initial", vlen(hi->hi) == 0);
	
	push(hi->hi, {});
	push(hi->hi, {});
	push(hi->hi, {});
	push(hi->hi, {});
	assert(vlen(hi->hi) == 4);
	
	vclear(hi->hi);
	subtest("Subfield: Push + Clear again", vlen(hi->hi) == 0);
	vfree(hi->hi);
	free(hi);
TEND();


#include "tests_end.h"
