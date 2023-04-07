/*
 * TODO:
  [-] Properly add:
   [-] `keys`
   [-] `filledbuckets`
    [ ] In Resize
  [ ] Clearing
  [-] Resizing
   [ ] Don't rehash + traverse for keys in the array, just use ptr
  [ ] Freeing
*/

#include "hash.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// #include <stdio.h>

typedef unsigned int uint; // bc why

// Aligns to the next multiple of a, where a is a power of 2
static inline int align(int n, int a) { return (n + a - 1) & ~(a - 1); }
static inline void pushkey(struct GENERIC_TABLE_* t, void* ptr) {
  if(!t->keys) {
    t->keys = malloc(4 * sizeof(void*));
    t->keys[0] = ptr;
    t->n = 1;
    return;
  }
  int newsize = align(t->n + 1, 4);
  if(newsize != t->ksize)
    t->keys = realloc(t->keys, newsize * sizeof(void*)), t->ksize = newsize;
  t->keys[t->n] = ptr;
  t->n ++;
}






// Initializes a hashtable
void htinit(struct GENERIC_TABLE_* t, uint size) {
  t->n = 0; t->size = size;
  t->items = calloc(sizeof(struct GENERIC_ITEM_), size); 
}

// Resizes a hashtable, rehashing all the keys. Slow right now, will make it faster later.
#define RESIZE(...) {\
  if(!t->size) { htinit(t, size); return true; }\
  struct GENERIC_ITEM_* new = calloc(sizeof(struct GENERIC_ITEM_), size);\
\
  for(int i = 0; i < t->n; i++) {\
    __VA_ARGS__\
    uint h = hash(*t->keys[i], ksize);\
    uint oldind = h % t->size;\
    uint newind = h % size;\
\
    struct GENERIC_ITEM_* item;\
    struct GENERIC_ITEM_* last = NULL;\
    while(item != NULL)\
      if (memcmp(item->k, t->keys[i], ksize) == 0) {\
        if (last == NULL) t->items[oldind] = *(item->next);\
        else last->next = item->next;\
        break;\
      } else {\
        last = item;\
        item = item->next;\
      }\
\
    if (item == NULL) continue;\
    memcpy(new + newind, item, sizeof(struct GENERIC_ITEM_));\
  }\
\
  free(t->items);\
  t->items = new;\
  t->size = size;\
  return true;\
}

bool htresize(struct GENERIC_TABLE_* t, uint size, uint ksize) RESIZE()
bool htsresize(struct GENERIC_TABLE_* t, uint size)
// RESIZE(
//   uint ksize = strlen(*t->keys[i]);
//)

{
  if(!t->size) { htinit(t, size); return true; }
  struct GENERIC_ITEM_* new = calloc(sizeof(struct GENERIC_ITEM_), size);

  for(int i = 0; i < t->n; i++) {
    uint ksize = strlen(*t->keys[i]);
    uint h = hash(*t->keys[i], ksize);
    uint newind = h % size;

    struct GENERIC_ITEM_* item = (struct GENERIC_ITEM_*)t->keys[i];
    struct GENERIC_ITEM_* newitem = new + newind;

    /* If it's a top level item, we would have to copy it over or allocate it separately */
    if (item >= t->items && item < t->items + t->size) {
      if (newitem->k) {
        while(newitem->next) newitem = newitem->next;
        newitem->next = malloc(sizeof(struct GENERIC_ITEM_));
        newitem = newitem->next;
      }
      newitem->k = item->k;
      newitem->v = item->v;
      newitem->next = NULL;
      t->keys[i] = &newitem->k;
      continue;
    }

    /* If it's not top level, it's separately allocated, so we need to free it in the instance we're setting to top level, or just set the item -> next to the new item */
    if (newitem->k) {
      while(newitem->next) newitem = newitem->next;
      newitem = newitem->next = item;
      newitem->next = NULL;
    }
    else {
      newitem->k = item->k;
      newitem->v = item->v;
      // newitem->next = NULL; // Already NULL
      free(item);
    }
    t->keys[i] = &newitem->k;
  }

  free(t->items);
  t->items = new;
  t->size = size;
  return true;
}






// Frees a linked item, an item not in the main array of items.
static inline void freeitem(struct GENERIC_ITEM_* item) {
  free(item->k); free(item->v);
  if(item->next) freeitem(item->next);
  free(item);
}

void htfree(struct GENERIC_TABLE_* t) {
  for(int i = 0; i < t->n; i ++) {
    struct GENERIC_ITEM_* k = (struct GENERIC_ITEM_*) t->keys[i];
    if(k < t->items || k > t->items + t->size) continue; // Only select top level items, items that aren't separately allocated and linked to
    free(k->k); free(k->v);
    if(k->next) freeitem(k->next); // Much simpler to do it recursively here.
  }
  free(t->items);
  free(t->keys);
}

void htreset(struct GENERIC_TABLE_* t) {
  for(int i = 0; i < t->n; i ++) {
    struct GENERIC_ITEM_* k = (struct GENERIC_ITEM_*) t->keys[i];
    if(k < t->items || k > t->items + t->size) continue;
    free(k->k); free(k->v);
    if(k->next) freeitem(k->next);
    memset(k, 0, sizeof(struct GENERIC_ITEM_));
  }
  memset(t->keys, 0, t->n * sizeof(void*));
  t->n = 0;
  t->filledbuckets = 0;
  // t->size = 0;
}





// Gets an arbitrary type key from hash table
void* htget(struct GENERIC_TABLE_* t, void* k, uint ksize, bool str) {
  if(!t->size) return NULL; // If the table is empty, return NULL (no key found)
  int index = hash(k, ksize) % t->size;
  struct GENERIC_ITEM_* item = t->items + index;
  
  if(item->k != NULL) {
    if(str)
      do {
        if (strcmp(item->k, k) == 0)
          return item->v;
        else item = item->next;
      } while (item != NULL);
    else
      do {
        if (memcmp(item->k, k, ksize) == 0)
          return item->v;
        else item = item->next;
      } while (item != NULL);
  }

  return NULL;
}

// Sets/inserts an arbitrary type key in the given hash table
void* htset(struct GENERIC_TABLE_* t, void* k, uint ksize, size_t vsize, bool str) {
  int index = hash(k, ksize) % t->size;
  struct GENERIC_ITEM_* item = t->items + index;
  struct GENERIC_ITEM_* last = NULL;

  if(item->k != NULL) {
    if(str)
      do {
        if (strcmp(item->k, k) == 0)
          return item->v = realloc(item->v, vsize);
        else item = item->next, last = item;
      } while (item != NULL);
    else
      do {
        if (memcmp(item->k, k, ksize) == 0)
          return item->v = realloc(item->v, vsize);
        else item = item->next, last = item;
      } while (item != NULL);
  } else t->filledbuckets ++;

  if(!item) item = malloc(sizeof(struct GENERIC_ITEM_));
  if(last) last->next = item;
  
  item->v = malloc(vsize);
  item->k = malloc(ksize);
  memcpy(item->k, k, ksize);
  item->next = NULL;
  pushkey(t, &item->k);
  return item->v;
}


