#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void chunk_init(chunk_t *chunk) {
  *chunk = (chunk_t) {
    .count = 0,
    .capacity = 0,
    .code = NULL
  };
}

void chunk_free(chunk_t *chunk) {
  FREE_ARRAY(chunk->code, chunk->capacity);
  chunk_init(chunk);
}

void chunk_write(chunk_t *chunk, uint8_t byte) {
  if (chunk->capacity < chunk->count + 1) {
    int c_old = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(c_old);
    chunk->code = GROW_ARRAY(chunk->code, uint8_t, c_old, chunk->capacity);
  }

  chunk->code[chunk->count] = byte;
  ++chunk->count;
}
