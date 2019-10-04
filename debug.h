#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

void chunk_disassemble(chunk_t *chunk, const char *name);
uint32_t instruction_disassemble(chunk_t* chunk, uint32_t offset);

#endif
