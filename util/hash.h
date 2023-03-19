#ifndef HASH_H
#define HASH_H
#include "hashfunc.h"

#define HASH_CONCAT_RAW(x, y) x##y
#define HASH_CONCAT(x, y) HASH_CONCAT_RAW(x, y)

// Defines an item for the hashtable.
#define item(key, val) struct HASH_CONCAT(item_, __LINE__) { key k; val v; struct HASH_CONCAT(item_, __LINE__)* next; }

// Defines a hashtable variable.
#define ht(key, val) struct { int n; key* keys; item(key, val)* items; int size; }

#define round_to_next(num, var) hi


#endif

