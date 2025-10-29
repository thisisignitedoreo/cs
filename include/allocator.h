#ifndef _ALLOCATOR_H
#define _ALLOCATOR_H

#include <stddef.h>

struct allocator {
  void *ctx;
  void *(*allocate)(void*, void*, size_t);
};

struct allocator stdc_allocator(void);

void *a_malloc(struct allocator alloc, size_t size);
void *a_realloc(struct allocator alloc, void *old, size_t size);
void a_free(struct allocator alloc, void *old);

void *a_zero(void *ptr, size_t size);

#define a_struct(a, t) (a_zero(a_malloc((a), sizeof(t)), sizeof(t)))

#endif /* _ALLOCATOR_H */
