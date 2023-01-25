#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "vec.h"

// Just callocs a vec lol
void* vnew() {
	return (struct vecdata*)calloc(1, sizeof(struct vecdata)) + 1; }

// Combines two vectors into a new vector
void* vcat(void* a, void* b) {
	void* v = vnew();
	_push(&v, vlen(b) + vlen(a));
	memcpy(v, a, _DATA(a)->used);
	memcpy(v, b, _DATA(b)->used);
	return v;
}

// Reallocs more size for the array, hopefully without moves o.o
void _alloc(struct vecdata** data, u8 size) {
	*data = realloc(*data, sizeof(struct vecdata) + (*data)->cap + size);
	(*data)->cap += size;
}

// Pushes more data onto the array, CAN CHANGE THE PTR U PASS INTO IT
void* _push(void** v, u8 size) {
	struct vecdata* data = _DATA(*v);

	// If the capacity is exceeded, alloc more
	data->used += size;
	if(data->cap < data->used)
		_alloc(&data, (size + data->used) - data->cap), *v = (data + 1);
	
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


void* _pop(void* v, u8 size) {
	_DATA(v)->used -= size; return _DATA(v)->data + _DATA(v)->used; }

// deletes data from the middle of the array
void _remove(void* v, u8 size, u32 pos) {
	memmove(_DATA(v) + pos, _DATA(v) + pos + size, _DATA(v)->used - pos - size);
	_DATA(v)->used -= size;
}


