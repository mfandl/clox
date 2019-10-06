#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"

typedef struct {
  chunk_t* chunk;
} VM;

void vm_init(void);
void vm_free(void);

#endif
