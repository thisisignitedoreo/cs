#include "arena.h"

struct region *region_new(struct allocator alloc, size_t page_size, struct region *link) {
  struct region *region = a_zero(a_malloc(alloc, sizeof(struct region) + page_size), sizeof(struct region));
  region->size = page_size;
  region->cursor = 0;
  region->previous = link;
  return region;
}

struct region *region_free(struct allocator alloc, struct region *region) {
  struct region *previous = region->previous;
  a_free(alloc, region);
  return previous;
}

void *arena_alloc_fn(void *ctx, void *old, size_t size) {
  struct arena *arena_ctx = ctx;
  if (size) {
    if (old == &arena_ctx->last->data[arena_ctx->last->last]) arena_ctx->last->cursor = arena_ctx->last->last;
    
    if (arena_ctx->last->size - arena_ctx->last->cursor < size) {
      arena_ctx->last = region_new(arena_ctx->toplevel, size > arena_ctx->page_size ? size : arena_ctx->page_size, arena_ctx->last);
    }
    void *ptr = &arena_ctx->last->data[arena_ctx->last->cursor];
    arena_ctx->last->last = arena_ctx->last->cursor;
    arena_ctx->last->cursor += size;
    return ptr;
  } else {
    if (old == &arena_ctx->last->data[arena_ctx->last->last]) arena_ctx->last->cursor = arena_ctx->last->last;
  }
  return NULL;
}

struct allocator arena_new(struct allocator toplevel, size_t page_size) {
  struct arena *arena = a_struct(toplevel, struct arena);
  arena->toplevel = toplevel;
  arena->page_size = page_size;
  arena->last = region_new(toplevel, page_size, NULL);
  return (struct allocator) {
    .ctx = arena,
    .allocate = arena_alloc_fn,
  };
}

void arena_free(struct allocator arena) {
  struct arena *arena_ctx = arena.ctx;
  struct region *current = arena_ctx->last;
  while (current) current = region_free(arena_ctx->toplevel, current);
}
