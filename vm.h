#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct {
  chunk_t *chunk;
  uint8_t *ip;
  value_t stack[STACK_MAX];
  value_t *stack_top;
} VM;

typedef enum interpret_result {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} interpret_result;

void vm_init(void);
void vm_free(void);

interpret_result vm_interpret(chunk_t *chunk);

void vm_stack_push(value_t value);
value_t vm_stack_pop(void);

#endif
