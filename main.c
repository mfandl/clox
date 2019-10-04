#include "common.h"
#include "chunk.h"
#include "debug.h"


int main (void) {
  chunk_t chunk;
  chunk_init(&chunk);
  chunk_write(&chunk, OP_RETURN);
  chunk_write(&chunk, OP_RETURN);
  chunk_disassemble(&chunk, "test chunk");
  chunk_free(&chunk);
  return 0;
}
