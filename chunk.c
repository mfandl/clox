#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void chunk_init(chunk_t *chunk) {
  *chunk = (chunk_t) {
    .count = 0,
    .capacity = 0,
    .code = NULL,
    .lines = NULL
  };
  value_array_init(&chunk->constants);
}

void chunk_free(chunk_t *chunk) {
  FREE_ARRAY(chunk->code, chunk->capacity);
  FREE_ARRAY(chunk->lines, chunk->capacity);
  value_array_free(&chunk->constants);
  chunk_init(chunk);
}

void chunk_write(chunk_t *chunk, uint8_t byte, uint16_t line) {
  if (chunk->capacity < chunk->count + 1) {
    size_t c_old = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(c_old);
    chunk->code = GROW_ARRAY(chunk->code, uint8_t, c_old, chunk->capacity);
    chunk->lines = GROW_ARRAY(chunk->lines, uint16_t, c_old, chunk->capacity);
  }

  chunk->code[chunk->count] = byte;
  chunk->lines[chunk->count] = line;
  ++chunk->count;
}

size_t chunk_constant_add(chunk_t *chunk, value_t value) {
  value_array_write(&chunk->constants, value);
  return chunk->constants.count - 1;
}
