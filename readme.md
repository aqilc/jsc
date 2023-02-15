# JSC

This project aims to make a programming language that's a hybrid of JS(or TS), C(and some other stuff I like), Rust and Python. I had the idea since JS was C like anyways, and I like a lot of the things JS does even though I disagree with other ideas. Also, since JS compilers kind of exist, it didn't sound too hard to make a simpler one.
Some goals are simplicity, one pass nature, ease of typing, and decent modern features.

The current name is temporary; these are a few other names I thought of: Luca, Mince, Letscript, Trip and K

### Goals of JSC

- Reduce LOC to write while also being a native language with native performance
	- Citing Rust, C++, and C. The LOC for many things in these languages is incredible.
- Compiles to assembly through every stage
	- Targetting Windows first, Mac next, and then Linux.
- Looks clean, and the syntax is simple and easy to get into
- Not too hard to get into for JS or Python people, maybe can be used for transition from learning C with a JS bg or vice versa.

- Lanugage Design:
	- Parsable in a single pass, no need to backtrack or anything
	- NONVERBOSE as much as possible, but never making anything confusing or ambiguous
		- Be familiar to users of other languages
	- Easy to type, easy to read
	- I plan to incorporate support for JSON and JS Objects as dicts

- Language Syntax:
	- Only postfix, binary, and tertiary ops (F for unary, no +val or \&val)
		- It's to fix things like `a ++++++ b` (`(a ++) + (++ b)`, is also hard to parse), still leaves `a +++ b` (`(a ++) + b`) possible but oh well
	- `{}` can be exchanged for `: expr`
		- If the block takes a return statement, like inside of a function (for things like `if`s) or in a function definition(`fn fname(): 3`), it is used as the return.
	- `;`s are optional when making a single statement in a line.

## Stage 1 of JSC

```rust
let a = 1u16 // ; optional
let b = 1000u8; // Compile time error: 1000 > u8 max
let c = 2.0e10u8; // yes
let d = 'c'u16 // u16, but converted from char so treated the same lol
let e = 'abcd' // Combines the utf8 values together into a number and puts it in to an int type for now. Complains if it's too big
let f = "hi" // All strings allocated on the stack

fn features() number {
	let a = 10
	let b = 2
	// In a function environment, omitting ; means returning the value except when you declare variables
	if a < 9: panic();
	for a:
		b *= 2;
	
	if a + b < 100 {
		// you can also have scopes or something lol
		print("too big")
		panic()
	}
	if comparison(a, b): b
	else a
}
// Generic function works for all numbers. Equivalent to fn comparison (a number, b number) 
fn comparison(a, b): a > b
fn typeandreturn() number: 4;
return features(); // return opcode for program

/* Non features in Stage 1:
	Strings, heap alloc, arrays, structs, objects, traits and ptrs.
	Oh yeah, you won't be yelled at for leaving out comment closer at the end of the file
```

#### Outside of syntax:
- Straight up assembly generation for all of that (although not the fastest assembly generation :P)
- VERY powerful generics and compiler conversions etc

## Stage 2 of JSC

- Introduces Errors
- Introduces JS **Objects** (dicts)
	- Corresponding type: `object`
	- and their derivative, **Arrays**
		- Corresponding type: `array`
- Introduces **Traits**
	- Defines a type of interface for types and 
- Introduces Structs, which are actually similar to classes and objects in JS, but can only set defined members and accessing undefined members results in an error
	- Can use strings to access members too.
		- Has to be wrapped in error handling <code>obj["x"]**?**</code>

```javascript
// Heap allocated array
let hi = []
hi.reduce((a, b) => a + b) // which has traits implemented internally, also anon funcs!!

let yes = str[].new() // Allocates an array of strings
let yes2 = array<str>.new()

let v = "string" // Heap allocated string, dk how heap allocation is going to work but we will have it :D
// Strings will implicitly store length and will function like arrays, similar to JS. Will hopefully be UTF-8 but we'll see ;-;

// OBJECTS POG
let obj = { bruh: "ez" };


// defines a struct
struct hello {
	hi str; bruh str?; yes u32, no;// In multi var declarations(with ,), the type of the first member's type is assumed for succeeding vars
	new(): hello { hi: "bruh" }
}

trait greeting { print(self) }
impl greeting for hello {
	print(self): print("hello " + )
}

hello.new().print() // 

fn func(hi str): print(hi + " world")
func("hello ")

/* Added features in Stage 2:
	Strings and arrays, which are similar to structs but structs aren't here yet so lol
```

## Stage 3

- Planned main focuses:
	- Modules
	- Packages
	- Compiler speed
	- Hot Reload

```javascript
// hello.jsc
fn hello({ lol }): print(lol);
hello { lol: 30 }

export hello;

// main.jsc
import hello from "hello.jsc" // Works like node, executes all of the code in hello then proceeds to do it here

```


## Language References

- https://dart.dev/samples
- https://github.com/vlang/v/blob/master/examples/mini_calculator.v
- Tutorial
	- https://sonictk.github.io/asm_tutorial/
- Windows Calling Conventions:
	- https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention?view=msvc-170
- COOL OPTIMIZATIONS POG: https://www.youtube.com/watch?v=VMpSYJ_7aYM
- Malloc in NASM on windows:
	- https://github.com/miguelperes/custom-malloc
	- https://steemit.com/programming/@orangeflash81/dynamic-memory-allocation-on-windows-in-nasm
- Academic references:
	- https://mcs.utm.utoronto.ca/~peters43/369/
- Different assembly syntaxes:
	- https://c.compiler-explorer.com/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1AB9U8lILUAV2LJ2HAPQAqANQAVAJ4AHTC4/XiFzQsFwRMYkxSFxIXWlQmdBdDF0xVVi96ADoXJwcAUg0AQTxBFwUARysmCIgSghcGKxYAShc8gHYAIQLClz6XCIIbBgamnNGWPIBmbqKOgBEejmb9TgBWXgZNXlROAGEygLs2gCYpnlICbeaVgGsJADZMh5fXt9f21Y5JTe3SXY4vAUIA0l2upDgsCQaBYXjo4XIlBhcPoxBQwC4JxOpCwADc8HYAGp4TAAdwA8j4ttxeDRaARwsCIAAjP7MkrVDycC7s5jEDzk5naTDIK400gwtiCckMWhcjhaHGYFiGYDiBW8fARUV4XGYYEa0ipEVWBnc3h1TC0P60PDM4icvYYeyKgjEPAsc0rKgGYAKYlkymMc0yQQiMTsKSh%2BRKNR/XRcfSqkCmYzmW3M4GQFaoLwEPACA1Aq0i/MCSiMdBO2hNLaJysAGRKmAAck1meE9F5UApCAWGNXa12e32BE2GK3253E0p6DqBEICNUCIOWHWLCX5wxF8vx5OWB20TOl8QV6ga2u9AoTwQ922D9OVpYbHYJCtrRwNqRqYqAS5VAAHA8AC0DySC4wDIMgLiYpkJwuBAuCEDEeRnFwzS8GKWg3KQ9xcE87yES8nwfj835/ACQIgmCGorJCiAoKgsLwmQFAQMiLEoNULAYlioJ4gSmABhSVIhnSDLEEyrKGrynIhrJ/KCsKoohpKjAEDKcp/FgKpGOqipaqWur6n8xrIKa9gXJaH6KhmDr8k6WB/G6Hpenwvr%2BiSInBuK/BhqI4hRn5MYqOohq6NiBhGCmZj6HaWYQDmeb9kWG5zmWWwQJWq7ro2zb3oew69hlOVFaODB3lOR5pUZC43qVM6bhlO6npVD7Vdey4NRYN5tYV6EWEckbvusvyGn%2BhQAEoALIQVBMEnHBCG2o0qitIh%2BBEIEqHnBhNHYXcjzPER7wkZwZE/jsnBUaCWHLBCMAMRxqKIuxTEop2yAsHgXizrxJz8Zg%2BJEl5QbUhc4mMpQ0mKgp8o8hyilCqWqlMVKGmyvKBnKqq%2Bmang2r5nqBqKmZFkhtZNp2vZHiOS6mHup6NLeh5wlg2JsjhoF0jBYooXxiAUxJtFqbpvF8BJRlqWzrVmXZeeQ71gw6B9dOpDdsV/bdRr5Wqx1TX9i1Z4XuuMtbkbetXvVCuXseu75VVb6DS%2Bw1fF%2Bl3/JwLjfb9CFWq0kHQbBi0aAhSFbacu2Ydch34cdJ0fF8F0UddFjUXddGPRA0LvSxr3PZ9ChTAAnBoqj/YDwNCaDom%2BXQElSWyiPw7wcNKSj4pqdKmPaTjen0ziBNGcTpmqCaZripThp2Y6zrOYzbk%2Bkwfps7XEOcwFkY87IfNxuFIDSFFJixRmCWSylqdmxlFbK91eUTgVas6yVNvrs//aW416WG9bJtXgbdV7YP0dnbU83VOqtQdu1J2z5bCuw/O7FOHAyglzLnNIOi0Q5h02ihNCe0M6xwIgnROpExq/kvuncE9Fs6MWYi9NiBc0TIDiAIYA1RkAIDAhXJUVdV4%2BQhvXKGLIm58hbqQNuyMVKdzRupTSWNNR9zVAPQyOoR6GjJhPKyggrRU3tLPJyhoXJMx4CzZenlAxr1pBvCMEht6CF3mFRUug1jC2PmmOKmYJb/GSoWS%2BAC5a31fnoe%2B%2B5%2BrqxHC/P%2BiZ35jigWEq%2BP8upBK/rLC2cS1YQONorHqQDQmPmdnAp2CCyFXWQSwow7DOHgUDgtOCmRQ4bWQttPB0daKEPjsQsCScSme0BGnW6McvgnB6ZRfaywVh6kkv2A%2BQA%3D%3D
