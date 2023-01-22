#ifndef JSC_VEC_H
#define JSC_VEC_H

#include <stdlib.h>
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
// expands to something like: *(int*)_push((void*) &data, 4) = (int) 5;

// The variadic push macro, still in the works
// #define push(x, ...) (memcpy(_push((void**) &(x), sizeof((typeof(x)) { __VA_ARGS__ })), (typeof(x)) { __VA_ARGS__ }, sizeof((typeof(x)) { __VA_ARGS__ })))
// expands to: memcpy((int*)_push((void*) &data, 4), (((*data))[]) {5}, sizeof(((*data)[]) {5}));

#define pop(x) (_pop((x), sizeof(*(x))))

void* vnew();
// void _alloc(struct vecdata** data, u8 size);
void _remove(void* v, u8 size, u32 pos);
void* _push(void** v, u8 size);
void* _pop(void* v, u8 size);

#endif
