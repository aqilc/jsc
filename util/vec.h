#ifndef JSC_VEC_H
#define JSC_VEC_H

// #include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

struct vecdata {
	u32 used;
	u32 cap;
	u8 data[];
};
#define _DATA(x) ((struct vecdata*)(x) - 1)
#define vlen(x) (_DATA(x)->used / sizeof(*(x)))

// The normal push macro, pushes a value onto the obj
#define push(x, ...) (*(typeof(x))_push((void**)&(x), sizeof(*(x))) = (typeof(*x)) __VA_ARGS__)
// push(data, 5); expands to something like: *(int*)_push((void**) &data, 4) = (int) 5;

// String push aliases so u don't have to &
#define pushs(x, y) _pushs((void**) &(x), (y))
#define pushsf(x, ...) _pushsf((void**) &(x), __VA_ARGS__)

// Push the entirety of a vec onto another
#define pushv(x, y) memcpy(_push(&(x), _DATA(y)->used), y, _DATA(y)->used)

// push(x, ...) but basically for strings
// #define pushs(x, y) memcpy((char*)(_push((void**)&(x), strlen(y))), (y), strlen(y))
// pushs(data, "hello"); expands to something like: memcpy((char*)(_push((void**) &data, strlen("hello"))), "hello", strlen("hello"));

// The generic push macro, does not work :sob: pls find a way to make it work
// #define push(x, ...) _Generic((x), char*: memcpy((char*)(_push((void**)&(x), strlen(__VA_ARGS__))), __VA_ARGS__, strlen(__VA_ARGS__)),\
// 	default: (*(typeof(x))_push((void**)&(x), sizeof(*(x))) = (typeof(*x)) __VA_ARGS__))

// The variadic push macro, still in the works
// #define push(x, ...) (memcpy(_push((void**) &(x), sizeof((typeof(x)) { __VA_ARGS__ })), (typeof(x)) { __VA_ARGS__ }, sizeof((typeof(x)) { __VA_ARGS__ })))
// expands to: memcpy((int*)_push((void*) &data, 4), (((*data))[]) {5}, sizeof(((*data)[]) {5}));

#define pop(x) (_pop((x), sizeof(*(x))))

void* vnew();
void* vcat(void* a, void* b);
// void _alloc(struct vecdata** data, u8 size);
void _remove(void* v, u8 size, u32 pos);
void* _push(void** v, u8 size);
void _pushs(void** v, char* str);
void _pushsf(void** v, char* fmt, ...);
void* _pop(void* v, u8 size);

#endif
