#include "tests.h"
#include "../../util/hash.h"
#include "macrohelp.h"
#include <stdlib.h>

// size_t _msize(void*);

#define MAX_STRING_LENGTH 10
#define STRINGS 500000
char arr[STRINGS][MAX_STRING_LENGTH+1];
INIT() {
    int i, j;
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    srand(0x10930930);
    for (i = 0; i < STRINGS; i++) {
        for (j = 0; j < MAX_STRING_LENGTH; j++) {
            int index = rand() % (sizeof(charset) - 1);
            arr[i][j] = charset[index];
        }
        arr[i][MAX_STRING_LENGTH] = '\0';
    }
    // for (i = 0; i < 300; i++)
    //     printf("%s\n", arr[i]);
}


TEST("Initializing") {
  ht(int, int) h = {0};
  htresize((struct GENERIC_TABLE_*)&h, 20, sizeof(int));
  assert(h.n == 0);
  assert(h.size == 20);
  assert(h.items != NULL);
  hfree(h);
}

TEST("Integer Keys") {
  ht(int, int) h = {0};

  substart("First Set + Get");
  hsetst(h, {1}) = 2;
  assert(1);
  subend(*hgetst(h, {1}) == 2);
  hfree(h);
}

TEST("String keys") {
  ht(char*, int) h = {0};

  substart("First Set + Get");
    hsets(h, "hello") = 1;
    assert(1);
  subend(*hgets(h, "hello") == 1);

  substart("Autoresize + inserting benchmark: " STR(STRINGS) " strings");
    for (int i = 0; i < STRINGS; i++)
      hsets(h, arr[i]) = i;
  subend(1);
  substart("Get benchmark: " STR(STRINGS) " strings");
    for (int i = 0; i < STRINGS; i++)
      asserteq(*hgets(h, arr[i]), i);
  subend(1);
  hfree(h);
}

TEST("Struct keys") {
  struct Test {
    int a, b, c, d;
  };

  ht(struct Test, int) h = {0};

  substart("First Set + Get");
  struct Test t = {1, 2, 3, 4};
  hset(h, t) = 3;
  hsetst(h, { .a = 4, .b = 5 }) = 6;
  assert(1);
  asserteq(*hgetst(h, { .a = 4, .b = 5 }), 6);
  subend(*hget(h, t) == 3);
  hfree(h);
}

#include "tests_end.h"
