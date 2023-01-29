#include <stdio.h>
#include <ctype.h>
int main() {
  char str[] = "the fox is very fast";


  int start = -1;
  int end = 0;
  for(int i = 0; str[i]; i ++) {
    if(start < 0 && isalnum(str[i]) || str[i] == '_')
      start = i;
    else if(isalnum(str[i]) || str[i] == '_') end = i;
    else {
      printf("%.*s\n", end - start + 1, str + start);
      start = -1;
    }
  }
  if(start > -1) printf("%s\n", str + start);
}


