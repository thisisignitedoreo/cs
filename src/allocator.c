#include "allocator.h"

#include <stdlib.h>

void *stdc_alloc_fn(void *ctx, void *old, size_t size) {
  (void) ctx;
  if (size == 0) { free(old); return NULL; }
  return realloc(old, size);
}

struct allocator stdc_allocator(void) {
  return (struct allocator) {
    .ctx = NULL,
    .allocate = stdc_alloc_fn,
  };
}

void *a_malloc(struct allocator alloc, size_t size) {
  return alloc.allocate(alloc.ctx, NULL, size);
}

void *a_realloc(struct allocator alloc, void *old, size_t size) {
  return alloc.allocate(alloc.ctx, old, size);
}

void a_free(struct allocator alloc, void *old) {
  alloc.allocate(alloc.ctx, old, 0);
}

void *a_zero(void *ptr, size_t size) {
  for (unsigned char *i = ptr; i < (unsigned char*) ptr + size; i++) *i = 0;
  return ptr;
}

void *a_memset(void *ptr, uint8_t byte, size_t size) {
  for (unsigned char *i = ptr; i < (unsigned char*) ptr + size; i++) *i = byte;
  return ptr;
}

void *a_memcpy(void *dst, void *src, size_t size) {
  for (size_t i = 0; i < size; i++) ((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
  return dst;  
}
