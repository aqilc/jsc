#include <stdio.h>
#include <stdbool.h>
#include "../util/vec.h"
#include "helpers.h"


struct var {
  enum type {
    INT,
    FLOAT,
    STRING,
    BOOL,
    VOID
  } type;
  union {
    int i;
    float f;
    char* s;
    bool b;
  } val;
};

struct var* vars = NULL;


void export(init)() {
  vars = vnew();
}

void export(exit)() {
  printf("Program finished.");
}



char* export(prog)() {
  return "lmao";
}