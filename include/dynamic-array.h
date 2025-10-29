#ifndef _DYNAMIC_ARRAY_H
#define _DYNAMIC_ARRAY_H

#include "allocator.h"

#define DA_DEFAULT_CAP 8

struct da_header {
  struct allocator alloc;
  size_t size, stride, capacity;
};

#define DA_HEADER(a) ((struct da_header*)(((char*)(a))-sizeof(struct da_header)))

void *_da_new(struct allocator alloc, size_t stride);
#define da_new(a, t) ((t*)_da_new((a), sizeof(t)))
#define da_push(a, e) do {						\
  if (DA_HEADER(*(a))->size == DA_HEADER(*(a))->capacity) {		\
    int old_size = DA_HEADER(*(a))->capacity + sizeof(da_header);	\
    int new_size = DA_HEADER(*(a))->capacity * 2 + sizeof(da_header);	\
    void *w = a_malloc(allocator, new_size);				\
    a_memcpy(w, DA_HEADER(*(a)), old_size);				\
    *a = (char*) w + sizeof(da_header);					\
  }									\
  *(a)[DA_HEADER(*(a))->size++] = e;					\
  } while (0)
#define da_pop(a) (*a)[DA_HEADER(*(a))->size--]
#define da_free(a) do {				\
  a_free(DA_HEADER(*(a))->alloc, *(a));		\
  *a = NULL;					\
  } while (0)

#endif /* _DYNAMIC_ARRAY_H */
