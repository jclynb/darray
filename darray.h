#ifndef DARRAY
#define DARRAY

struct dynamic_array {
  int data_size;
  int capacity;
  int tysz; // size of the type of data we store
  void *data;
};

void                      darray_init(struct dynamic_array*, int);
struct dynamic_array*     darray_new(int);
int                       darray_len(struct dynamic_array*);
void                      darray_grow(struct dynamic_array*, int);
void                      darray_set(struct dynamic_array*, int, void*);
void*                     darray_get(struct dynamic_array*, int);
void                      darray_append(struct dynamic_array*, void*);
void                      darray_pop(struct dynamic_array*, void*);
struct dynamic_array*     darray_map(struct dynamic_array*, void* (*funcp)(void*));
void                      darray_free(struct dynamic_array*);

#endif
