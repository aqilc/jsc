#include "vec.h"

// Just callocs a vec lol
void* new_vec() {
	return (struct vecdata*)calloc(1, sizeof(struct vecdata)) + 1; }

// Reallocs more size for the array, hopefully without moves o.o
void _alloc(struct vecdata** data, u8 size) {
	*data = realloc(*data, sizeof(struct vecdata) + (*data)->cap + size);
	(*data)->cap += size;
}

// Pushes more data onto the array
void* _push(void** v, u8 size) {
	struct vecdata* data = _DATA(*v);

	// If the capacity is exceeded, alloc more
	if(data->cap < data->used + size)
		_alloc(&data, (size + data->used) - data->cap), *v = (data + 1);

	data->used += size;
	return data->data + data->used - size;
}

void* _pop(void* v, u8 size) {
	_DATA(v)->used -= size; return _DATA(v)->data + _DATA(v)->used; }

// deletes data from the middle of the array
void _remove(void* v, u8 size, u32 pos) {
	memmove(_DATA(v) + pos, _DATA(v) + pos + size, _DATA(v)->used - pos - size);
	_DATA(v)->used -= size;
}


