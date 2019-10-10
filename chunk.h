#pragma once

#include "common.h"
#include "value.h"

typedef enum {
  OP_CONSTANT,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_NEGATE,
  OP_RETURN
} OpCode;

typedef struct chunk_t {
  size_t count;
  size_t capacity;
  uint8_t *code;
  uint16_t *lines;
  value_array_t constants;
} chunk_t;

void chunk_init(chunk_t *chunk);
void chunk_free(chunk_t *chunk);
void chunk_write(chunk_t *chunk, uint8_t byte, uint16_t line);

size_t chunk_constant_add(chunk_t *chunk, value_t value);
