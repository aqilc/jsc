#include "tests.h"
#include "../../util/hash.h"
#include "macrohelp.h"
#include <stdlib.h>
#include <malloc.h>

// size_t _msize(void*);

#define MAX_STRING_LENGTH 10
char arr[300000][MAX_STRING_LENGTH+1];
INIT() {
    int i, j;
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    srand(0x10930930);
    for (i = 0; i < 30000; i++) {
        for (j = 0; j < MAX_STRING_LENGTH; j++) {
            int index = rand() % strlen(charset);
            arr[i][j] = charset[index];
        }
        arr[i][MAX_STRING_LENGTH] = '\0';
    }
    // for (i = 0; i < 300; i++)
    //     printf("%s\n", arr[i]);
}


TEST("Initializing")
  ht(int, int) h = {0};
  htresize((struct GENERIC_TABLE_*)&h, 20, sizeof(int));
  assert(h.n == 0);
  assert(h.size == 20);
  assert(h.items != NULL);
TEND()

TEST("Integer Keys")
  ht(int, int) h = {0};

  substart("First Set + Get");
  hset(h, {1}) = 2;
  assert(1);
  subend(*hget(h, {1}) == 2);
TEND()

TEST("String keys")
  ht(char*, int) h = {0};

  substart("First Set + Get");
  hsets(h, "hello") = 1;
  assert(1);
  subend(*hgets(h, "hello") == 1);

  substart("Autoresize + benchmark");
  for (int i = 0; i < 300000; i++)
    hsets(h, arr[i]) = i;
  assert(1);
  subend(1);
TEND()

#include "tests_end.h"