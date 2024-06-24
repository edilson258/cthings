#include <stdio.h>

#include "../include/Stack.h"

int main(void) {
  Stack_t stack = Stack_new(2);
  Stack_push(stack, Str("Hello"));
  Stack_push(stack, Str("World"));
  Str_t data = Stack_pop(stack);
  printf("%s\n", data);
  return 0;
}
