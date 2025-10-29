#ifndef _ARENA_H
#define _ARENA_H

#include <stdint.h>
#include "allocator.h"

struct region {
  size_t size, cursor, last;
  struct region *previous;
  unsigned char data[];
};

struct arena {
  struct allocator toplevel;
  size_t page_size;
  struct region *last;
};

struct allocator arena_new(struct allocator toplevel, size_t page_size);
void arena_free(struct allocator arena);

#endif /* _ARENA_H */
