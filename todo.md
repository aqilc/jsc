
**Key:** `CDG` = Codegen, `TOK` = Tokenizer

- [ ] **`TOK`** Add Variable declaration support to tokenizer
	- [x] **`TOK`** Add Keywords
	- [ ] **`TOK`** Add Declarations
	- [ ] **`TOK`** Add Identifiers
	- [ ] **`TOK`** Add Operators
	- [ ] **`TOK`** Add End of Lines
	- [ ] **`TOK`** Write tests for all of the above
- [ ] **`CDG`** Draw out plans for error handling in Codegen
- [ ] **`CDG`** Generate DATA section
	- [ ] **`TOK`** Strings
	- [ ] **`CDG`** Allocating strings in DATA
		- [ ] **`CDG`** Work out packing strlen and/or cap before string
- [ ] Print "hello world" in JSC
	- [ ] **`TOK`** Function calls
	- [ ] **`CDG`** Function argument allocation and input
	- [ ] **`CDG`** Stack alignment
		- [ ] **`CDG`** Counting the amount of stack needed for variables
		- [ ] **`CDG`** Preallocation for variables
	- [ ] **`CDG`** Predefined functions
		- [ ] **`CDG`** `print(str)`
