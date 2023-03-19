#include "hash.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Copies string and makes it 
static inline char* copystr(char* s) { char* ns = malloc(strlen(s)); strcpy(ns, s); return ns; }

// Initializes a hashtable
