#include <stdio.h>

#include "debug.h"
#include "value.h"

void chunk_disassemble(chunk_t *chunk, const char *name) {
  printf("== %s ==\n", name);

  for (size_t offset = 0; offset < chunk->count;) {
    offset = instruction_disassemble(chunk, offset);
  }
}

static size_t instruction_simple(const char *name, size_t offset) {
  printf("%s\n", name);

  return offset + 1;
}

static size_t instruction_constant(const char *name, chunk_t *chunk, size_t offset) {
  uint8_t constant = chunk->code[offset + 1];
  printf("%-16s %4d '", name, constant);
  value_print(chunk->constants.values[constant]);
  printf("'\n");
  return offset + 2;
}


size_t instruction_disassemble(chunk_t* chunk, size_t offset) {
  printf("%04lu ", offset);
  if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
    printf("   | ");
  } else {
    printf("%4d ", chunk->lines[offset]);
  }

  uint8_t instruction = chunk->code[offset];
  switch (instruction) {
    case OP_CONSTANT:
      return instruction_constant("OP_CONSTANT", chunk, offset);
    case OP_ADD:
      return instruction_simple("OP_ADD", offset);
    case OP_SUBTRACT:
      return instruction_simple("OP_SUBTRACT", offset);
    case OP_MULTIPLY:
      return instruction_simple("OP_MULTIPLY", offset);
    case OP_DIVIDE:
      return instruction_simple("OP_DIVIDE", offset);
    case OP_NEGATE:
      return instruction_simple("OP_NEGATE", offset);
    case OP_RETURN:
      return instruction_simple("OP_RETURN", offset);
    default:
      printf("Unknown opcode %d\n", instruction);
      return offset + 1;
  }
}
