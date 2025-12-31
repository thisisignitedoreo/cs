#ifndef _DYNAMIC_ARRAY_H
#define _DYNAMIC_ARRAY_H

#include "allocator.h"

#define DA_DEFAULT_CAP 8

struct da_header {
  struct allocator alloc;
  size_t size, stride, capacity;
};

#define DA_HEADER(a) ((struct da_header*) (a) - 1)

void *_da_new(struct allocator alloc, size_t stride);
#define da_new(a, t) ((t*)_da_new((a), sizeof(t)))
#define da_push(a, e) do {						\
    if (DA_HEADER(*(a))->size == DA_HEADER(*(a))->capacity) {		\
      int new_size = DA_HEADER(*(a))->capacity * DA_HEADER(*(a))->stride * 2 + sizeof(struct da_header); \
      *(void**)(a) = (void*) ((struct da_header*) a_realloc(DA_HEADER(*(a))->alloc, DA_HEADER(*(a)), new_size) + 1); \
      DA_HEADER(*(a))->capacity *= 2;					\
    }									\
    (*(a))[DA_HEADER(*(a))->size++] = e;				\
  } while (0)
#define da_reserve(a, e) do {						\
    size_t old_size = DA_HEADER(*(a))->capacity;			\
    size_t new_size = old_size;						\
    while (new_size < DA_HEADER(*(a))->size + e) new_size *= 2;		\
    if (new_size > old_size) {						\
      size_t full_new_size = new_size * DA_HEADER(*(a))->stride + sizeof(struct da_header); \
      *(void**)(a) = (void*) ((struct da_header*) a_realloc(DA_HEADER(*(a))->alloc, DA_HEADER(*(a)), full_new_size) + 1); \
      DA_HEADER(*(a))->capacity = new_size;				\
    }									\
    DA_HEADER(*(a))->size += e;						\
  } while (0)
#define da_pop(a) ((*(a))[--DA_HEADER(*(a))->size])
#define da_free(a) do {					\
    a_free(DA_HEADER(*(a))->alloc, DA_HEADER(*(a)));	\
    *a = NULL;						\
  } while (0)
#define da_size(a) (DA_HEADER(*(a))->size)
#define da_capacity(a) (DA_HEADER(*(a))->capacity)

#endif /* _DYNAMIC_ARRAY_H */
