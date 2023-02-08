#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "codegen.h"


// Unperformant file reader, but it works ok :(
char* read(char* file) {
  FILE *fp = fopen(file, "rb");
  if(!fp) {
    printf("Couldn't open file %s", file);
    return "";
  }
  
  // Finds length of file
  fseek(fp, 0, SEEK_END);
  size_t len = ftell(fp);
  rewind(fp);
  
  // Mallocs enough for the file + nullbyte i think
  char* contents = malloc(len * sizeof(char) + 1);
  contents[len] = '\0';
  
  // Reads file into the contents variable then closes it
  fread(contents, 1, len, fp);
  fclose(fp);
  
  // returns both
  return contents;
}

// Strcat but usable smh
char* c(char* s1, char* s2) {
	u32 len1 = strlen(s1);
	char* out = malloc(len1 + strlen(s2) + 1);
	strcpy(out, s1);
	strcpy(out + len1, s2);
	return out;
}


static char** strings = NULL;
static int stringslen = 0;

// Formats and returns a heap allocated string
char* format(char* str, ...) {

  // Gets a pointer to the arguments, with the stdlib func va_start
  va_list args;
  va_start(args, str);
  va_list debug;
  va_start(debug, str);

  // Gets the length of the returned string
  int len = vsnprintf(NULL, 0, str, args) + 1;

  // Allocates a buffer on the heap with the length
  char* arr = malloc(len);

  // Prints and sets the last byte to 0 to indicate the end of the string
  vsprintf(arr, str, debug);
  arr[len - 1] = 0;
  
  va_end(args);
  va_end(debug);

  // Keeps track of a string array with it's length, which we free later.
  if(strings == NULL) strings = malloc(sizeof(char*));
  else strings = realloc(strings, sizeof(char*) * (stringslen + 1));
  strings[stringslen] = arr;
  stringslen ++;
  
  return arr;
}

void freeformat() {
  for(int i = 0; i < stringslen; i ++)
    free(strings[i]);
  stringslen = 0;
}

void exec(char* cmd) {
	printf("executing %s\n", cmd);
	system(cmd);
}

int main(int argn, char** args) {
	char* str = codegen(tokenize(read(c("test/lang/", c(args[1], ".rs")))));
	char* filename = c("test/asm/", args[1]);
	char* asmfile = c(filename, ".asm");
	FILE* ez = fopen(asmfile, "w+");
	fputs(str, ez);
	puts(str);
	exec(c(c("nasm -f win32 -o ", c(filename, ".obj ")), asmfile));
	exec(c(c(c(c("link ", filename), ".obj msvcrt.lib /subsystem:console /out:"), filename), ".exe"));
	// system("");
}



