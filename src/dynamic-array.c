#include "dynamic-array.h"

void *_da_new(struct allocator alloc, size_t stride) {
  struct da_header *da = a_struct_fao(alloc, struct da_header, stride * DA_DEFAULT_CAP);
  da->stride = stride;
  da->capacity = DA_DEFAULT_CAP;
  return (void*) (da + 1);
}
