#ifndef JSC_VEC_H
#define JSC_VEC_H

// #include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

struct vecdata_ {
	u32 used;
	u32 cap;
	u8 data[];
};
#define _DATA(x) ((struct vecdata_*)(x) - 1)
#define vlen(x) (_DATA(x)->used / sizeof(*(x)))

// The normal push macro, pushes a value onto the obj
#define push(x, ...) (*(typeof(x))push_((void**)&(x), sizeof(*(x))) = (typeof(*x)) __VA_ARGS__)
// push(data, 5); expands to something like: *(int*)push_((void**) &data, 4) = (int) 5;

// Push n items onto the vector, so we can allocate more space at once
#define pushn(x, n, y) /*_Generic(*(x), */pushn_((void**) &(x), (n), sizeof(*(x)), &((typeof(*(x))) {y}))//)
// One for structs since that prev one didn't work for structs
#define pushnst(x, n, y) pushn_((void**) &(x), (n), sizeof(*(x)), &((typeof(*(x))) y))

// String push aliases so u don't have to &
#define pushs(x, y) pushs_((void**) &(x), (y))
#define pushsf(x, ...) pushsf_((void**) &(x), __VA_ARGS__)


// Push the entirety of a vec onto another
#define pushv(x, y) memcpy(push_(&(x), _DATA(y)->used), y, _DATA(y)->used)

// Add values to the beginning of the vec
#define unshift(x, ...) (*(typeof(x))unshift_((void**)&(x), sizeof(*(x))) = (typeof(*x)) __VA_ARGS__)

// Simplifies vclear calls
#define vclear(v) vclear_((void**)&(v))

// Pops off the last element and returns it
#define pop(x) (pop_((x), sizeof(*(x))))

// push(x, ...) but basically for strings
// #define pushs(x, y) memcpy((char*)(push_((void**)&(x), strlen(y))), (y), strlen(y))
// pushs(data, "hello"); expands to something like: memcpy((char*)(push_((void**) &data, strlen("hello"))), "hello", strlen("hello"));

// The generic push macro, does not work :sob: pls find a way to make it work
// #define push(x, ...) _Generic((x), char*: memcpy((char*)(push_((void**)&(x), strlen(__VA_ARGS__))), __VA_ARGS__, strlen(__VA_ARGS__)),\
// 	default: (*(typeof(x))push_((void**)&(x), sizeof(*(x))) = (typeof(*x)) __VA_ARGS__))

// The variadic push macro, still in the works
// #define push(x, ...) (memcpy(push_((void**) &(x), sizeof((typeof(x)) { __VA_ARGS__ })), (typeof(x)) { __VA_ARGS__ }, sizeof((typeof(x)) { __VA_ARGS__ })))
// expands to: memcpy((int*)push_((void*) &data, 4), (((*data))[]) {5}, sizeof(((*data)[]) {5}));


// All you need to get started with this vector lib!
void* vnew();

// Returns a *new* concatenated vector, use `pushv` if you don't want a new vec :D
void* vcat(void* a, void* b);
void vfree(void* v);
void vclear_(void** v);
// void _alloc(struct vecdata_** data, u8 size);
void remove_(void* v, u32 size, u32 pos);
void* push_(void** v, u32 size);
void pushs_(void** v, char* str);
void pushsf_(void** v, char* fmt, ...);
void pushn_(void** v, u32 n, u32 size, void* thing);
void* unshift_(void** v, u32 size);
void* pop_(void* v, u32 size);

#endif
