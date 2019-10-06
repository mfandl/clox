#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
  OP_CONSTANT,
  OP_RETURN
} OpCode;

typedef struct chunk_t {
  size_t count;
  size_t capacity;
  uint8_t *code;
  value_array_t constants;
} chunk_t;

void chunk_init(chunk_t *chunk);
void chunk_free(chunk_t *chunk);
void chunk_write(chunk_t *chunk, uint8_t byte);

size_t chunk_constant_add(chunk_t *chunk, value_t value);

#endif
