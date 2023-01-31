#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "vec.h"

// Just callocs a vec lol
void* vnew() {
	return (struct vecdata*)calloc(1, sizeof(struct vecdata)) + 1; }

// Combines two vectors into a new vector (USE THIS FOR STRING VECS INSTEAD OF _PUSHS PLS I BEG)
void* vcat(void* a, void* b) {
	void* v = vnew();
	_push(&v, vlen(b) + vlen(a));
	memcpy(v, a, _DATA(a)->used);
	memcpy(v + _DATA(a)->used, b, _DATA(b)->used);
	return v;
}

void vfree(void* v) { free(_DATA(v)); }

// Reallocs more size for the array, hopefully without moves o.o
void* _alloc(struct vecdata* data, u16 size) {
	data->used += size;
	if(data->cap < data->used) {
		data->cap += data->used - data->cap;
		return (struct vecdata*)realloc(data, sizeof(struct vecdata) + data->cap) + 1;
	}
	return data + 1;
}

// Pushes more data onto the array, CAN CHANGE THE PTR U PASS INTO IT
void* _push(void** v, u16 size) {
	struct vecdata* data = _DATA(*v);
	data = _DATA(*v = _alloc(data, size));
	return data->data + data->used - size;
}

// Allocates memory for a string and then pushes
void _pushs(void** v, char* str) {
	u32 len = strlen(str);
	memcpy(_push(v, len), str, len);
}

// Gets length of formatted string to allocate from vector first, and then basically writes to the ptr returned by push
void _pushsf(void** v, char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	u32 len = vsnprintf(NULL, 0, fmt, args);
	vsnprintf(_push((void**) v, len), len, fmt, args);
}

// Adds an element at the start of the vector, ALSO CHANGES PTR
void* _unshift(void** v, u16 size) {
	memmove((*v = _alloc(_DATA(*v), size)) + size, *v, vlen(*v));
	return *v;
}


void* _pop(void* v, u16 size) {
	_DATA(v)->used -= size; return _DATA(v)->data + _DATA(v)->used; }

// deletes data from the middle of the array
void _remove(void* v, u16 size, u32 pos) {
	memmove(_DATA(v) + pos, _DATA(v) + pos + size, _DATA(v)->used - pos - size);
	_DATA(v)->used -= size;
}


