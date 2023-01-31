#include "hash.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

static void pushs(hashtable* h, char* s);

// Creates a table of specified size
hashtable* ht(unsigned short size) {
  hashtable* h = malloc(sizeof(hashtable));
  h->size = size;
  h->count = 0;
  h->t = calloc(size, sizeof(hashitem*));
  h->keys = malloc(sizeof(char*) * 4);
  h->keyssize = 4;
  h->fastdeleted = 0;
  return h;
}

// New<type> functions for creating objects on the heap on the fly
int* new_i(int i) { int* v = malloc(sizeof(int)); *v = i; return v; }
unsigned int* new_ui(unsigned int i) { unsigned int* v = malloc(sizeof(unsigned int)); *v = i; return v; }
float* new_f(float f) { float* v = malloc(sizeof(float)); *v = f; return v; }
char* new_c(char c) { char* s = malloc(2); s[0] = c; s[1] = '\0'; return s; }
char* new_s(char* s) { size_t len = strlen(s); char *t = malloc(len + 1); return strcpy(t, s); }

// Insert a key and value (use malloc(new_s) on strings, and cast ints to ptrs)
hashtable* hti(hashtable* ht, char* key, void* data) {

  // Clones the key just to make sure.
  key = new_s(key);
  
  // Does the hash, and then mods it with the size
  unsigned int place = hash(key, strlen(key)) % ht->size;
  
  // Since we have to account for collisions, we store the pointer to the start of the linked list, so we can move along and get to the end if needed
  hashitem** cur = ht->t + place;
  while(*cur != NULL) {
    
    // If the key is the same, put the new value in and just return
    if (!strcmp(key, (*cur)->key)) { (*cur)->value = data; return ht; }

    // Else go to the end of the linked list
    cur = &((*cur)->next);
  }
  
  // Makes a new item, and puts it into whatever cur was
  hashitem* i = malloc(sizeof(hashitem));
  i->key = key;
  i->value = data;
  i->next = NULL;
  *cur = i;

  // Pushes the key onto the keys array
  pushs(ht, key);
  return ht;
}

// Get value from ht with key
void* htg(hashtable* h, char* key) {
  
  // Gens hash
  unsigned int place = hash(key, strlen(key)) % h->size;
  
  // Checks the place where the hash resolves to, and returns null if there's nothing
  hashitem* cur = h->t[place];
  if(!cur) return NULL;
  
  // Until there's an exact match, loop through the linked list of keys and values
  while(cur != NULL)
    if(strcmp(key, cur->key))
      cur = cur->next;
    else return cur->value;

  // If it didn't find anything, return NULL
  return NULL;
}

// Deletes a key (VERY EXPENSIVE SO USE AT YOUR OWN RISK) (don't forget to free your return ptr if you need to)
void* htd(hashtable* h, char* key) {
  
  // Same setup as `htg()`
  unsigned int place = hash(key, strlen(key)) % h->size;
  hashitem* cur = h->t[place];
  if(!cur) return NULL;

  // Deletes the key in the keystore
  char* keyptr = NULL; unsigned int numkeys = 0;
  for(int i = 0; i < h->count; i++)
    if(!strcmp(h->keys[i], key)) { numkeys = h->count - i - 1; keyptr = h->keys[i]; break; }
  if(keyptr == NULL) return NULL;
  if(numkeys) memmove(keyptr, keyptr + 1, numkeys);

  // Tries to find the parent of the key we're looking for
  if(strcmp(key, cur->key)) {

    // While there's still a next value that is what we're looking for, continue on to the next.
    while(cur->next != NULL)
      if(strcmp(key, cur->next->key))
        cur = cur->next;
      else goto found;

    // If the key was a child of the main hastable array, just delete the entry and the key
  } else {

    // Replaces the base place in the hashtable with NULL, and frees the key and item.
    h->count --;
    h->t[place] = NULL;
    void* val = cur->value;
    free(cur->key); free(cur);
    return val;
  }

  // If we did not find anything return NULL. This is also the signal that something is very
  // messed up in the map tho, if there's a keystore entry but no actual entry lol
  return NULL;
  
  // If we found a suitable parent
found:
  h->count --;
  void* val = cur->next->value;
  free(cur->next->key); free(cur->next);
  cur->next = NULL;
  return val;
}

// For deleting everything in a table really fast.
// **WARNING Table is unusable after you call this.**
// IS ALSO UNSAFE FOR BAD TABLES BC IT SKIPS A COUPLE CHECKS
void* htdfast(hashtable* h) {
  if(h->fastdeleted >= h->count) return NULL;
  char* key = h->keys[h->fastdeleted ++];
  unsigned int place = hash(key, strlen(key)) % h->size;
  hashitem* cur = h->t[place];

  // copied from htd()
  if(strcmp(key, cur->key)) {
    while(cur->next != NULL)
      if(strcmp(key, cur->next->key))
        cur = cur->next;
      else goto found;
  } else {
    void* val = cur->value;
    free(cur->key); free(cur);
    return val;
  }
  return NULL; // if this is reached there is something really really messed up
found:;
  void* val = cur->next->value;
  free(cur->next->key); free(cur->next);
  cur->next = NULL;
  return val;
}

void htreset(hashtable* h) {
  h->count = 0;
  h->t = realloc(h->t, h->size * sizeof(hashitem*));
  memset(h->t, 0, h->size * sizeof(hashitem*));
  h->keys = realloc(h->keys, sizeof(char*) * 4);
  h->keyssize = 4;
  h->fastdeleted = 0;
}

// Frees EMPTY table
void htfree(hashtable* h) {
  free(h->keys); free(h->t);
  free(h);
}

// Getter functions that return types so it's easier to deal with them
int htgi(hashtable* h, char* key) { return *(int*) htg(h, key); }
unsigned int htgui(hashtable* h, char* key) { return *(unsigned int*) htg(h, key); }
float htgf(hashtable* h, char* key) { return *(float*) htg(h, key); }

// Pushes a string onto the keystore of the hashtable, reallocs 4 ptrs at a time for perf
static void pushs(hashtable* h, char* s) {
  if(h->count >= h->keyssize) {
    h->keyssize += 4;
    h->keys = realloc(h->keys, sizeof(char *) * h->keyssize);
  }
  h->keys[h->count] = s;
  h->count++;
}
