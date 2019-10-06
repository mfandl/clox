#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "vm.h"

static VM vm;

static void stack_reset() {
  vm.stack_top = vm.stack;
}

void vm_init() {
  stack_reset();
}
void vm_free() {}

void vm_stack_push(value_t value) {
  *vm.stack_top = value;
  ++vm.stack_top;
}
value_t vm_stack_pop() {
  --vm.stack_top;
  return *vm.stack_top;
}

static interpret_result run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op) \
  do { \
    double b = vm_stack_pop(); \
    double a = vm_stack_pop(); \
    vm_stack_push(a op b); \
  } while (false)

  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    printf("          ");
    for (value_t *slot = vm.stack; slot < vm.stack_top; ++slot) {
      printf("[ ");
      value_print(*slot);
      printf(" ]");
    }
    printf("\n");
    instruction_disassemble(vm.chunk, (uint8_t)(vm.ip - vm.chunk->code));
#endif
    uint8_t instruction;
    switch (instruction = READ_BYTE()) {
      case OP_CONSTANT: {
        value_t constant = READ_CONSTANT();
        vm_stack_push(constant);
        printf("\n");
        break;
      }
      case OP_ADD:
        BINARY_OP(+);
        break;
      case OP_SUBTRACT:
        BINARY_OP(-);
        break;
      case OP_MULTIPLY:
        BINARY_OP(*);
        break;
      case OP_DIVIDE:
        BINARY_OP(/);
        break;
      case OP_NEGATE:
        vm_stack_push(-vm_stack_pop());
        break;
      case OP_RETURN:
        value_print(vm_stack_pop());
        printf("\n");
        return INTERPRET_OK;

    }
  }

#undef BINARY_OP
#undef READ_CONSTANT
#undef READ_BYTE
}

interpret_result vm_interpret(chunk_t *chunk) {
  vm.chunk = chunk;
  vm.ip = vm.chunk->code;
  return run();
}
