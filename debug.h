#pragma once

#include "chunk.h"

void chunk_disassemble(chunk_t *chunk, const char *name);
size_t instruction_disassemble(chunk_t* chunk, size_t offset);
