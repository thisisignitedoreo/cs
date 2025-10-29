#ifndef _ALLOCATOR_H
#define _ALLOCATOR_H

#include <stddef.h>

struct allocator {
  void *ctx;
  void *(*allocate)(void*, size_t);
  void (*free)(void*, void*);
};

struct allocator stdc_allocator(void);

void *a_malloc(struct allocator alloc, size_t size);
void a_free(struct allocator alloc, void *old);

void *a_zero(void *ptr, size_t size);

#define a_struct(a, t) (a_zero(a_malloc((a), sizeof(t)), sizeof(t)))
#define a_struct_fao(a, t, s) (a_zero(a_malloc((a), sizeof(t) + (s)), sizeof(t)))

#endif /* _ALLOCATOR_H */
