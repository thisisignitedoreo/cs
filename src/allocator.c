#include "allocator.h"

#include <stdlib.h>

void *stdc_alloc_fn(void *ctx, void *old, size_t size) {
  (void) ctx;
  if (!size) { free(old); return NULL; }
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
