CC := gcc
CFLAGS := -Wall -Wextra -Werror -pedantic -std=c99 -Iinclude $(CFLAGS)

OBJS = $(patsubst src/%.c,build/%.o,$(wildcard src/*.c))

all: build/libcs.a
.PHONY: all clean

clean:
	rm -rf build

build:
	mkdir -p build

build/%.o: src/%.c | $(wildcard include/*) build
	$(CC) $(CFLAGS) -c -o $@ $<

build/libcs.a: $(OBJS) build
	$(AR) rcs $@ $(OBJS)
