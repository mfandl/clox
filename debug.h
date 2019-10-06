#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

void chunk_disassemble(chunk_t *chunk, const char *name);
size_t instruction_disassemble(chunk_t* chunk, size_t offset);

#endif
