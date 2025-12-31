#ifndef _ALLOCATOR_H
#define _ALLOCATOR_H

#include <stddef.h>
#include <stdint.h>

struct allocator {
  void *ctx;
  void *(*allocate)(void*, void*, size_t);
};

struct allocator stdc_allocator(void);

void *a_malloc(struct allocator alloc, size_t size);
void *a_realloc(struct allocator alloc, void *old, size_t size);
void a_free(struct allocator alloc, void *old);

void *a_zero(void *ptr, size_t size);
void *a_memset(void *ptr, uint8_t byte, size_t size);
void *a_memcpy(void *dst, void *src, size_t size);

char *a_sprintf(struct allocator alloc, const char *fmt, ...);

#define a_struct(a, t) (a_zero(a_malloc((a), sizeof(t)), sizeof(t)))
#define a_struct_fao(a, t, s) (a_zero(a_malloc((a), sizeof(t) + (s)), sizeof(t)))

#endif /* _ALLOCATOR_H */
