#include <stdio.h>
#include <stdlib.h>
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

void exec(char* cmd) {
	printf("executing %s\n", cmd);
	system(cmd);
}

int main(int argn, char** args) {
	char* str = codegen(tokenize(read(c("test/", c(args[1], ".rs")))));
	char* filename = c("test/", args[1]);
	char* asmfile = c(filename, ".asm");
	FILE* ez = fopen(asmfile, "w+");
	fputs(str, ez);
	puts(str);
	exec(c(c("nasm -f win32 -o ", c(filename, ".obj ")), asmfile));
	exec(c(c(c(c("link ", filename), ".obj msvcrt.lib /subsystem:console /out:"), filename), ".exe"));
	// system("");
}

