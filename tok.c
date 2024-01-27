#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include "errors.h"
#include "tok.h"

// FOR DEBUG
#include <stdio.h>

// To differentiate our many different types of strings we have sometimes
typedef char* vstr;

static inline bool skip(char* s, u32* idx);
static inline vstr symb(char* str, u32 idx);
static inline i32 expect(char* s, u32 idx, char* e);
static inline void parse(struct Tokens* toks, char* str);
static inline u32 findeos(char* s, u32 idx);

ht(char*, enum TokenType) keywords;

// Defines every keyword
struct { char* s; enum TokenType t; } keyword_defs[] = {
	"let",    TTDECL,
	"fn",     TTDECL,
	"struct", TTDECL,
	"if",     TTKEYWORD,
	"else",   TTKEYWORD,
	"return", TTKEYWORD
};


void init_keywords() {
	for(u32 i = 0; i < sizeof(keyword_defs) / sizeof(keyword_defs[0]); i++)
		hsets(keywords, keyword_defs[i].s) = keyword_defs[i].t;
}

struct Tokens* tokenize(char* str) {

	// Initializes the keyword dict
	if(!hgets(keywords, "if")) init_keywords();

	struct Tokens* toks = malloc(sizeof(struct Tokens));
	toks->toks = vnew();

	// Initializes the hash tables (with all 0s), kinda dangerous but it should always work
	// memset(&toks->vars, 0, sizeof(toks->vars) * 3);

	parse(toks, str);
	return toks;
}


// Uses existing tokenizer object to tokenize, saves time, space, money and funccalls
void retokenize(struct Tokens* toks, char* str) {
	vclear(toks->toks);

	// hreset(toks->vars);
	// hreset(toks->funcs);
	// hreset(toks->structs);
	
	if(*str)
		parse(toks, str);
}

// Frees tokenizer output
void tokfree(struct Tokens* t) {
	vfree(t->toks);
	// hfree(t->vars);
	// hfree(t->funcs);
	// hfree(t->structs);
	free(t);
}




static inline void parse(struct Tokens* toks, char* str) {
	u32 idx = 0;
	struct Token* t = toks->toks;

	// Makes it easy to push tokens
	#define tok(x, l, ...) push(t, { .loc = idx, .type = x, .len = l, __VA_ARGS__ }), idx += l/*,*/\
		// printf("\nPushed token '"#x"' with length %d at idx %d on line %d", l, idx - l, __LINE__)
	#define throw(...) { error_at(str, idx, __VA_ARGS__); goto error; }
	#define SKIP skip(str, &idx)

	while (str[idx]) {
		// printf("%c", str[idx]);
		
		if(isspace(str[idx])) goto end;

		// Evaluates a number
		if(isdigit(str[idx])) {
			int num; u32 len = 1;

			// If the number is longer than just a single digit, do a lot of stuff ig
			if(isdigit(str[idx + 1])) {
				
				// Create a vector string to keep track of number chars
				vstr numstr = vnew();
				while(isdigit(str[idx]))
					push(numstr, str[idx]), idx++;
				len = vlen(numstr);
			
				num = atoi(numstr);
			} else num = str[idx] - '0';

			tok(TTNUM, len, .val = num);
			continue;
		}

		// Operators
		switch(str[idx]) {
			case '=':
				if(t[vlen(t) - 1].type == TTOP && t[vlen(t) - 1].val.op < OPSET)
					t[vlen(t) - 1].val.op += OPSET + 1, t[vlen(t) - 1].len ++, idx ++;
				else tok(TTOP, 1, .val = { .op = OPSET });
				continue;
			case '+': tok(TTOP, 1, .val = { .op = OPADD }); continue;
			case '-': tok(TTOP, 1, .val = { .op = OPSUB }); continue;
			case '*': tok(TTOP, 1, .val = { .op = OPMUL }); continue;
			case '/': tok(TTOP, 1, .val = { .op = OPDIV }); continue;
			case '%': tok(TTOP, 1, .val = { .op = OPMOD }); continue;
		}

		if(isalpha(str[idx])) {
			vstr sym = symb(str, idx);

			// If it's a keyword, parse the statement
			enum TokenType* token = hgets(keywords, sym);

			if(token) {
				switch(*token) {
					case DECL:

						// TODO: FUNCTIONS PLS FINISH THIS AND DON'T EXPECT THIS TO WORK
						if(sym[0] == 'f') {

							// Expect name after function
							tok(DECL, 2, .val = { .decl = FN });
							SKIP;
							if(!isalpha(str[idx])) throw("Expected function name after 'fn'.");
							
							vstr name = symb(str, idx);
							tok(IDENT, vlen(name), .val = { .s = name });
							vfree(name);

							SKIP;
							i32 paren = expect(str, idx, "(");
							if(paren < 0) throw("Expected '(' after function name in function declaration.");
							tok(ARGB, 1);

							while(isalpha(str[idx])) {
								SKIP;
								if(!isalpha(str[idx])) throw("Expected identifier after '%c' in function declaration.", str[idx - 1]);
								vstr name = symb(str, idx);
								tok(IDENT, vlen(name), .val = { .s = name });
								
								// For argument separators
								SKIP;
								if(str[idx] == ',') tok(ARGSEP, 1);
								vfree(name);
								SKIP;
							}

							i32 endparen = expect(str, idx, ")");
							if(endparen < 0) throw("Expected ')' after function arguments in function declaration.");
							tok(ARGE, 1);

							vfree(sym);
						} else if(sym[0] == 'l') {
							tok(DECL, 3, .val = { .decl = LET });
							SKIP;
							if(!isalpha(str[idx]) && str[idx] != '_') throw("Expected identifier after variable declaration, instead got '%c'", str[idx]);

							vstr name = symb(str, idx);
							tok(IDENT, vlen(name), .val = { .s = name });
							vfree(name); vfree(sym);
						}
						continue;
					case ELSE: {

						// Have to hack a tiny bit to get the `else if` to work
						u32 start = idx;
						idx += 4;
						SKIP;

						// Allocs a string for the `if`
						vstr maybeif = symb(str, idx);
						
						// Takes care of `else if`s
						if(strlen(maybeif) && !strcmp(maybeif, "if"))
							push(t, { .loc = start - 4, .type = ELSEIF, .len = idx - start + 4 + 2 });
						
						// Or backtracks if there's no if
						else push(t, { .loc = start - 4, .type = ELSE, .len = 4 });
						// Tokenizer can expression and the rest of the if separately.
						vfree(sym); vfree(maybeif);
						continue;
					}
					default:
						tok(*token, vlen(sym) /* Equivalent to strlen(sym) */,
							.val = { .s = sym });
						vfree(sym);
						continue;
				}
			} else {
				tok(IDENT, vlen(sym), .val = { .s = sym });
				vfree(sym);
				continue;
			}
		}

	end:
		if(!SKIP) idx++;
		continue;
		
	error:
		// We need to erase the whole line as if it didn't exist
		while(vlen(t) && t[vlen(t) - 1].type != EOS) pop(t);
		while(str[idx] && str[idx] != '\n') idx++;
		continue;
	}

	toks->toks = t;
}



static inline vstr symb(char* str, u32 idx) {
	vstr s = vnew();
	while(isalnum(str[idx]) || str[idx] == '_') push(s, str[(idx)++]);
	return vtostr(s);
}

static inline bool skip(char* s, u32* idx) {
	bool skipped = false;
	while(s[*idx] == ' ' || s[*idx] == '\n')
		skipped = true, (*idx)++;
	return skipped;
}
static inline u32 findeos(char* s, u32 idx) {
	while(s[idx]
		&& ((s[idx] == '/' && s[idx+1] == '/')
		|| s[idx] == ';' || s[idx] == '\n')) idx ++;
	return idx;
}


static inline i32 expect(char* s, u32 idx, char* e) {
	while(s[idx] == ' ' || s[idx] == '\n') idx++;

	// Since strlen takes C string, we need to put a 0 at the end of the string we need to compare to cut it off :(
	vstr tmp = strtov(e);
	for(int i = 0; s[i + idx] != 0 && i < vlen(tmp); i ++) if(s[i + idx] != tmp[i]) goto error;

	vfree(tmp);
	return idx;

error:
	vfree(tmp);
	return -1;
}


