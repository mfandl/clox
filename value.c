#include <stdio.h>

#include "memory.h"
#include "value.h"

void value_print(value_t value) {
  printf("%g", value);
}

void value_array_init(value_array_t *array) {
  *array = (value_array_t) {
    .values = NULL,
    .capacity = 0,
    .count = 0
  };
}

void value_array_write(value_array_t *array, value_t value) {
  if (array->capacity < array->count + 1) {
    size_t capacity_old = array->capacity;
    array->capacity = GROW_CAPACITY(capacity_old);
    array->values = GROW_ARRAY(array->values, value_t, capacity_old, array->capacity);
  }

  array->values[array->count] = value;
  ++array->count;
}

void value_array_free(value_array_t *array) {
  FREE_ARRAY(array->values, array->capacity);
  value_array_init(array);
}
