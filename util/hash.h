#ifndef HASH_H
#define HASH_H
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hashfunc.h"

// Generic structs for sizing
struct GENERIC_ITEM_ { void* k; void* v; struct GENERIC_ITEM_* next; };
#define TABLEFIELDS int n; int size; int filledbuckets; int ksize;
struct GENERIC_TABLE_ {
  TABLEFIELDS

  void*** keys; // An ARRAY containing pointers to key __POINTERS__ stored in the item, so requires 3 ptr things lol
  struct GENERIC_ITEM_* items;
};

#define HASH_STRIFY2(x) #x
#define HASH_STRIFY(x) HASH_STRIFY2(x)

#define HASH_CONCAT_RAW(x, y) x##y
#define HASH_CONCAT(x, y) HASH_CONCAT_RAW(x, y)

// Defines an item for the hashtable. Types for `k` get messed up when you pass in `char*` but we ignore it bc it barely matters.
#define item(key, val) struct HASH_CONCAT(itemht_, __LINE__) { key* k; val* v; struct HASH_CONCAT(itemht_, __LINE__)* next; }

// Defines a hashtable type.
#define ht(key, val) struct { TABLEFIELDS\
  key** keys; item(key, val)* items; }

// macros for easy hashtable method calling, main api:
#define hkeyt(htb) typeof(**(htb).keys)
#define hvalt(htb) typeof(*(htb).items->v)

// Resize if there are too many conflicts (n - filledbuckets) or if there are too many filled buckets 
#define mayberesize(htb) ((htb).n - (htb).filledbuckets * 3 / 2 >= (htb).filledbuckets || (htb).filledbuckets >= (htb).size * 3 / 4) && _Generic(**(htb).keys,\
  char*: htsresize((struct GENERIC_TABLE_*) &(htb), (htb).size * 3 / 2 + 10),\
  default: htresize((struct GENERIC_TABLE_*) &(htb), (htb).size * 3 / 2 + 10, sizeof(**(htb).keys)))

#define hget(htb, ...)  (hvalt(htb)*) htget((struct GENERIC_TABLE_*) &(htb), &(hkeyt(htb)) __VA_ARGS__, sizeof(**(htb).keys), false)
#define hgets(htb, key) (hvalt(htb)*) htget((struct GENERIC_TABLE_*) &(htb), key, strlen(key) + 1, true)


#define hset(htb, ...) mayberesize(htb), *(hvalt(htb)*) htset((struct GENERIC_TABLE_*) &(htb), &(hkeyt(htb)) __VA_ARGS__, sizeof(**(htb).keys), sizeof((htb).items->v), false)
#define hsets(htb, key) mayberesize(htb), *(hvalt(htb)*) htset((struct GENERIC_TABLE_*) &(htb), key, strlen(key) + 1, sizeof((htb).items->v), true)

#define hsetcpys(str, htb, ...) mayberesize(htb), strcpy((char*) htset((struct GENERIC_TABLE_*) &(htb), &(hkeyt(htb)) __VA_ARGS__, sizeof(**(htb).keys), strlen(str), false), str)
#define htsetscpys(str, htb, key) mayberesize(htb), strcpy((char*) htset((struct GENERIC_TABLE_*) &(htb), key, strlen(key) + 1, strlen(str) + 1, true), str)

#define hfree(htb) htfree((struct GENERIC_TABLE_*) &(htb))
#define hreset(htb) htreset((struct GENERIC_TABLE_*) &(htb))


// Raw Hashtable methods
void  htinit(struct GENERIC_TABLE_* t, unsigned int size);

bool  htresize(struct GENERIC_TABLE_* t, unsigned int size, unsigned int ksize);
bool  htsresize(struct GENERIC_TABLE_* t, unsigned int size);

void  htfree(struct GENERIC_TABLE_* t);
void  htreset(struct GENERIC_TABLE_* t);

void* htget(struct GENERIC_TABLE_* t, void* k, unsigned int ksize, bool str);

void* htset(struct GENERIC_TABLE_* t, void* k, unsigned int ksize, size_t vsize, bool str);


/*
struct customkey {
  int k;
  int keynum;
  char* idk;
};

ht(int, int) h;
ht(char*, int) h2;
ht(struct customkey, int) h3;

int main() {
  hgets(h2, "hello");
  hget(h3, { 1, 2, "hello" });

  hsets(h2, "hello") = 10;
  hset(h3, { 2, 3, "lol" }) = 5;
}
*/

#endif

