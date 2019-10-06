#include "common.h"
#include "chunk.h"
#include "debug.h"


int main (void) {
  chunk_t chunk;
  chunk_init(&chunk);
  chunk_write(&chunk, OP_RETURN, 123);
  chunk_write(&chunk, OP_RETURN, 123);
  size_t constant = chunk_constant_add(&chunk, 1.2);
  chunk_write(&chunk, OP_CONSTANT, 123);
  chunk_write(&chunk, (uint8_t) /* oh my :) */ constant, 123);
  chunk_disassemble(&chunk, "test chunk");
  chunk_free(&chunk);
  return 0;
}
