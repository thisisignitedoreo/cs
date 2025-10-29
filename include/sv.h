#ifndef _SV_H
#define _SV_H

#include <string.h>
#include <stdbool.h>

struct sv {
  const char *data;
  int size;
};

#define SV(w) ((struct sv) { .data = (w), .size = strlen((w)) })
#define SVr(w, s) ((struct sv) { .data = (w), .size = (s) })
#define SVc(w) ((struct sv) { .data = (w), .size = sizeof(w)-1 })

#define SV_FMT "%.*s"
#define SVf(s) s.size, s.data

bool sv_equal(struct sv a, struct sv b);

#endif /* _SV_H */
