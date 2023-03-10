/*
 * vec.c v1.0.0 - Aqil Contractor @AqilCont 2023
 * Licenced under Attribution-NonCommercial-ShareAlike 3.0
 *
 * This file includes all of the source for the Vector library macros and functions.
 * Compile this separately into a .o, .obj, .a, .dll or .lib and link into your project to use it appropriately.
 */

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "vec.h"

// Just callocs a vec lol
void* vnew() { return (struct vecdata_*)calloc(1, sizeof(struct vecdata_)) + 1; }

// Combines two vectors into a new vector (USE THIS FOR STRING VECS INSTEAD OF _PUSHS PLS I BEG)
void* vcat(void* a, void* b) {
	void* v = vnew();
	push_(&v, vlen(b) + vlen(a));
	memcpy(v, a, _DATA(a)->used);
	memcpy(v + _DATA(a)->used, b, _DATA(b)->used);
	return v;
}

char vcmp(void* a, void* b) {
	u32 len = vlen(a);
	if(len != vlen(b)) return 1;
	u32 idx = 0;
	while (idx < len) if(((char*)a)[idx] != ((char*)b)[idx]) return 1; else idx ++;
	return 0;
}

char* strtov(char* s) {
	char* v = vnew();
	pushs_((void**) &v, s);
	return v;
}

char* vtostr_(void** v) {
	*(char*)push_(v, 1) = 0;
	_DATA(*v)->used --;
	return *v;
}

void vclear_(void** v) {
	struct vecdata_* data = realloc((struct vecdata_*) *v - 1, sizeof(struct vecdata_));
	*v = data + 1;
	data->cap = 0;
	data->used = 0;
}

void vfree(void* v) { free(_DATA(v)); }


// Reallocs more size for the array, hopefully without moves o.o
void* alloc_(struct vecdata_* data, u32 size) {
	data->used += size;
	if(data->cap < data->used) {
		data->cap += data->used - data->cap;
		return (struct vecdata_*)realloc(data, sizeof(struct vecdata_) + data->cap) + 1;
	}
	return data + 1;
}

// Pushes more data onto the array, CAN CHANGE THE PTR U PASS INTO IT
void* push_(void** v, u32 size) {
	struct vecdata_* data = _DATA(*v = alloc_(_DATA(*v), size));
	return data->data + data->used - size;
}

// Allocates memory for a string and then pushes
void pushs_(void** v, char* str) {
	u32 len = strlen(str);
	memcpy(push_(v, len), str, len);
}

// Gets length of formatted string to allocate from vector first, and then basically writes to the ptr returned by push
void pushsf_(void** v, char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	va_list args2;
	va_start(args2, fmt);
	u32 len = vsnprintf(NULL, 0, fmt, args);
	vsnprintf(push_(v, len), len, fmt, args2);
	va_end(args);
	va_end(args2);
}

void pushn_(void** v, u32 n, u32 size, void* thing) {
	char* place = push_(v, n * size);
	if(size == 1) memset(place, *((char*) thing), size);
	else for(int i = 0; i < n; i ++) memcpy(place + size * i, thing, size);
}

void* pop_(void* v, u32 size) { _DATA(v)->used -= size; return _DATA(v)->data + _DATA(v)->used; }

// Adds an element at the start of the vector, ALSO CHANGES PTR
void* unshift_(void** v, u32 size) {
	memmove((*v = alloc_(_DATA(*v), size)) + size, *v, vlen(*v));
	return *v;
}


// Deletes data from the middle of the array
void remove_(void* v, u32 size, u32 pos) {
	memmove(_DATA(v) + pos, _DATA(v) + pos + size, _DATA(v)->used - pos - size);
	_DATA(v)->used -= size;
}

