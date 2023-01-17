#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "vec.h"


int main() {
	u32* data = new_vec();

	puts("starting 1000000 reallocs ez");
  clock_t start_time = clock();
	for(int i = 0; i < 1000000; i ++)
		push(data, rand());
	data[2000] = 100;
	
	printf("Done in %f seconds\n", (double)(clock() - start_time) / CLOCKS_PER_SEC);
	printf("%d\n", data);
	printf("used: %d, cap: %d\n", _DATA(data)->used, _DATA(data)->cap);
	printf("%d\n", data[200000]);
	printf("%d\n", data[200001]);
}

