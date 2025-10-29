#include "allocator.h"

#include <stdlib.h>

void *stdc_alloc_fn(void *ctx, size_t size) {
  (void) ctx;
  return malloc(size);
}

void stdc_free_fn(void *ctx, void *old) {
  (void) ctx;
  free(old);
}

struct allocator stdc_allocator(void) {
  return (struct allocator) {
    .ctx = NULL,
    .allocate = stdc_alloc_fn,
    .free = stdc_free_fn,
  };
}

void *a_malloc(struct allocator alloc, size_t size) {
  return alloc.allocate(alloc.ctx, size);
}

void a_free(struct allocator alloc, void *old) {
  alloc.free(alloc.ctx, old);
}

void *a_zero(void *ptr, size_t size) {
  for (unsigned char *i = ptr; i < (unsigned char*) ptr + size; i++) *i = 0;
  return ptr;
}
