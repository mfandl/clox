#include <stdio.h>

#include "debug.h"

void chunk_disassemble(chunk_t *chunk, const char *name) {
  printf("== %s ==\n", name);

  for (size_t offset = 0; offset < chunk->count;) {
    offset = instruction_disassemble(chunk, offset);
  }
}

static uint32_t instruction_simple(const char *name, uint32_t offset) {
  printf("%s\n", name);
  return offset + 1;
}

uint32_t instruction_disassemble(chunk_t* chunk, uint32_t offset) {
  printf("%04d ", offset);

  uint8_t instruction = chunk->code[offset];
  switch (instruction) {
    case OP_RETURN:
      return instruction_simple("OP_RETURN", offset);
    default:
      printf("Unknown opcode %d\n", instruction);
      return offset + 1;
  }
}
