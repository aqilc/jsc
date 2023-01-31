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

struct vecdata {
	u32 used;
	u32 cap;
	u8 data[];
};
#define _DATA(x) ((struct vecdata*)(x) - 1)
#define vlen(x) (_DATA(x)->used / sizeof(*(x)))

// The normal push macro, pushes a value onto the obj
#define push(x, ...) (*(typeof(x))push_((void**)&(x), sizeof(*(x))) = (typeof(*x)) __VA_ARGS__)
// push(data, 5); expands to something like: *(int*)push_((void**) &data, 4) = (int) 5;

// String push aliases so u don't have to &
#define pushs(x, y) pushs_((void**) &(x), (y))
#define pushsf(x, ...) pushsf_((void**) &(x), __VA_ARGS__)

// Push the entirety of a vec onto another
#define pushv(x, y) memcpy(push_(&(x), _DATA(y)->used), y, _DATA(y)->used)

// Add values to the beginning of the vec
#define unshift(x, ...) (*(typeof(x))unshift_((void**)&(x), sizeof(*(x))) = (typeof(*x)) __VA_ARGS__)

// Simplifies vclear calls
#define vclear(v) vclear_((void**)&(v))

// push(x, ...) but basically for strings
// #define pushs(x, y) memcpy((char*)(push_((void**)&(x), strlen(y))), (y), strlen(y))
// pushs(data, "hello"); expands to something like: memcpy((char*)(push_((void**) &data, strlen("hello"))), "hello", strlen("hello"));

// The generic push macro, does not work :sob: pls find a way to make it work
// #define push(x, ...) _Generic((x), char*: memcpy((char*)(push_((void**)&(x), strlen(__VA_ARGS__))), __VA_ARGS__, strlen(__VA_ARGS__)),\
// 	default: (*(typeof(x))push_((void**)&(x), sizeof(*(x))) = (typeof(*x)) __VA_ARGS__))

// The variadic push macro, still in the works
// #define push(x, ...) (memcpy(push_((void**) &(x), sizeof((typeof(x)) { __VA_ARGS__ })), (typeof(x)) { __VA_ARGS__ }, sizeof((typeof(x)) { __VA_ARGS__ })))
// expands to: memcpy((int*)push_((void*) &data, 4), (((*data))[]) {5}, sizeof(((*data)[]) {5}));

#define pop(x) (pop_((x), sizeof(*(x))))

void* vnew();
void* vcat(void* a, void* b);
void vfree(void* v);
void vclear_(void** v);
// void _alloc(struct vecdata** data, u8 size);
void remove_(void* v, u16 size, u32 pos);
void* push_(void** v, u16 size);
void pushs_(void** v, char* str);
void pushsf_(void** v, char* fmt, ...);
void* unshift_(void** v, u16 size);
void* pop_(void* v, u16 size);

#endif
