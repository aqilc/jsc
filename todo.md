
> **Key:** ![](https://img.shields.io/badge/-CDG-%23627ffa) = Codegen, ![](https://img.shields.io/badge/-TOK-%23fd5355) = Tokenizer

- [ ] ![](https://img.shields.io/badge/-TOK-%23fd5355) Add Variable declaration support to tokenizer
	- [x] ![](https://img.shields.io/badge/-TOK-%23fd5355) Add Keywords
	- [x] ![](https://img.shields.io/badge/-TOK-%23fd5355) Add Declarations
	- [x] ![](https://img.shields.io/badge/-TOK-%23fd5355) Add Identifiers
	- [x] ![](https://img.shields.io/badge/-TOK-%23fd5355) Add Operators
	- [ ] ![](https://img.shields.io/badge/-TOK-%23fd5355) Add End of Lines
	- [ ] ![](https://img.shields.io/badge/-TOK-%23fd5355) Write tests for all of the above
- [ ] ![](https://img.shields.io/badge/-CDG-%23627ffa) Error handling in Codegen
- [ ] ![](https://img.shields.io/badge/-CDG-%23627ffa) `return <int>;` to return opcode
- [ ] ![](https://img.shields.io/badge/-CDG-%23627ffa) Globals
	- [ ] ![](https://img.shields.io/badge/-CDG-%23627ffa) Generate DATA section
		- [ ] ![](https://img.shields.io/badge/-CDG-%23627ffa) Allocating strings in DATA
			- [ ] ![](https://img.shields.io/badge/-CDG-%23627ffa) Work out packing strlen and/or cap before string
- [ ] Function calls
	- [ ] ![](https://img.shields.io/badge/-TOK-%23fd5355) Function call tokenizing
		- [ ] ![](https://img.shields.io/badge/-TOK-%23fd5355) Argument list
		- [ ] ![](https://img.shields.io/badge/-TOK-%23fd5355) Argument types
			- [ ] ![](https://img.shields.io/badge/-TOK-%23fd5355) Default types
	- [ ] ![](https://img.shields.io/badge/-CDG-%23627ffa) Function argument allocation and input
	- [ ] ![](https://img.shields.io/badge/-CDG-%23627ffa) Stack alignment
		- [ ] ![](https://img.shields.io/badge/-CDG-%23627ffa) Counting the amount of stack needed for variables
		- [ ] ![](https://img.shields.io/badge/-CDG-%23627ffa) Preallocation for variables
	- [ ] ![](https://img.shields.io/badge/-CDG-%23627ffa) Predefined functions
		- [ ] `abort()`
		- [ ] `exit(exitcode int)`
- [ ] Print "hello world" in JSC through `print(str)`
	- [ ] ![](https://img.shields.io/badge/-CDG-%23627ffa) Native Functions
		- [ ] ![](https://img.shields.io/badge/-CDG-%23627ffa) Standardizing calling conventions
			- [ ] ![](https://img.shields.io/badge/-CDG-%23627ffa) Microsoft Calling Conventions (in readme)
			- [ ] ![](https://img.shields.io/badge/-CDG-%23627ffa) LIBSTDC/MSVCRT calling conventions.
	- [ ] ![](https://img.shields.io/badge/-CDG-%23627ffa) Linking to C functions
- [ ] String support
	- [ ] ![](https://img.shields.io/badge/-TOK-%23fd5355) Strings


> __Note__
> don't mind this
> **`TOK`**
> <svg width="30" height="16"><path fill="#fd5355" d="M0 0h30v16H0z"/><text x="3.5" y="12" fill="#fff" color="#fff" font-family="Roboto Mono" font-size="12" font-weight="bold">TOK</text></svg>
> <svg width="30" height="16"><rect width="30" height="16" fill="#fd5355"/><text font-size="14" font-weight="bold" color="white" font-family="Roboto Mono" x="2" y="13" fill="white">TOK</text></svg>
> ![](https://img.shields.io/badge/-TOK-%23fd5355)
