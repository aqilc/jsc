#ifndef HASH_H
#define HASH_H
#include "hashfunc.h"

typedef struct hashitem {
  char* key;
  void* value;
  
  // Make the item a linked list in case of collisions
  struct hashitem* next;
} hashitem;

typedef struct hashtable {
  char** keys;
  hashitem** t;
  unsigned short size;
  unsigned int count;
  unsigned int keyssize;
  unsigned int fastdeleted;
} hashtable;

// Creates a table of specified size
hashtable* ht(unsigned short size);
// Insert a key and value (use malloc(new_s) on strings, and cast ints to ptrs)
hashtable* hti(hashtable* ht, char* key, void* data);
// Get value from ht with key
void* htg(hashtable* h, char* key);
// Deletes a key (VERY EXPENSIVE SO USE AT YOUR OWN RISK) (don't forget to free your return ptr if you need to)
void* htd(hashtable* h, char* key);

int* new_i(int i);
unsigned int* new_ui(unsigned int i);
float* new_f(float f);
char* new_c(char c);
char* new_s(char* s);

int htgi(hashtable* h, char* key);
unsigned int htgui(hashtable* h, char* key);
float htgf(hashtable* h, char* key);

// For deleting everything in a table really fast.
// **WARNING Table is unusable after you call this.**
// IS ALSO UNSAFE FOR BAD TABLES BC IT SKIPS A COUPLE CHECKS
void* htdfast(hashtable* h);
// Frees EMPTY table
void htfree(hashtable* h);
// Resets EMPTY table, reallocs some things
void htreset(hashtable* h);
#endif

