#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_SIZE 4
#define ENTRY_PTR(index) (void *)(((char *)d->data) + (index) * d->tysz)

typedef struct dynamic_array {
  int data_size; //size of the array that's filled with data
  int capacity; //size of the array's available memory
  int tysz; //size of type of data we store
  void *data;
} darray;

void darray_init(darray *d, int tysz) {
  d->data_size = 0;
  d->capacity = INIT_SIZE;
  d->tysz = tysz;
  d->data = malloc(tysz * d->capacity);
}

darray* darray_new(int tysz) {
  darray *p = malloc(sizeof(struct dynamic_array));
  darray_init(p, tysz);
  return p;
}

int darray_len(darray *d) {
  return d->data_size;
}

void darray_grow(darray *d, int capacity) {
  void *data = realloc(d->data, d->tysz * capacity);
  if (data != NULL) {
    d->capacity = capacity;
    d->data = data;
  }
}

void darray_set(darray *d, int index, void *entry) {
  //d->data[index] = entry;
  memcpy(ENTRY_PTR(index), entry, d->tysz);
}

void* darray_get(darray *d, int index) {
  if (0 <= index && index < d->data_size) {
    return ENTRY_PTR(index);
  }
}

void darray_append(darray *d, void *entry) {
  if (d->data_size == d->capacity) {
    darray_grow(d, d->capacity * 2 * d->tysz);
  }
  darray_set(d, d->data_size++, entry);
}

void darray_pop(darray *d, int index) {
  if ((index < 0) || (index > d->data_size)) {
      printf("index out of range\n");
      return;
    }

  for(int i = index; i < d->data_size; i++) {
    darray_set(d, i, ENTRY_PTR(i+1));
  } d->data_size--;
}

// Given a darray d and function f : A -> B, where A is the type of data stored
// in d, return a new darray containing B's obtained by applying f to every
// element of d.
darray* darray_map(darray *d, void* (*funcp)(void*)) {
  darray* new = darray_new(d->tysz);
  for (int i = 0; i < d->data_size; i++) {
    darray_append(new, funcp(ENTRY_PTR(i)));
  }
  return new;
}

void darray_free(darray *d) {
  free(d->data);
}
