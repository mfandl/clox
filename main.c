#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"


int main (void) {
  vm_init();
  chunk_t chunk;
  chunk_init(&chunk);
  size_t constant = chunk_constant_add(&chunk, 1.2);
  chunk_write(&chunk, OP_CONSTANT, 123);
  chunk_write(&chunk, (uint8_t) /* oh my :) */ constant, 123);

  constant = chunk_constant_add(&chunk, 3.4);
  chunk_write(&chunk, OP_CONSTANT, 123);
  chunk_write(&chunk, (uint8_t) /* oh my :) */constant, 123);

  chunk_write(&chunk, OP_ADD, 123);

  constant = chunk_constant_add(&chunk, 5.6);
  chunk_write(&chunk, OP_CONSTANT, 123);
  chunk_write(&chunk, (uint8_t) /* oh my :) */constant, 123);

  chunk_write(&chunk, OP_DIVIDE, 123);

  chunk_write(&chunk, OP_NEGATE, 123);
  chunk_write(&chunk, OP_RETURN, 123);
  chunk_disassemble(&chunk, "test chunk");
  vm_interpret(&chunk);
  vm_free();
  chunk_free(&chunk);
  return 0;
}
