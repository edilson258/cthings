#include <stdio.h>
#include <stdlib.h>

#include "../include/Stack.h"

Stack_t Stack_new(size_t max_stack) {
  Stack_t stack = malloc(sizeof(Stack));
  stack->head = NULL;
  stack->size = 0;
  stack->max_stack = max_stack;
  return stack;
}

Boolean Stack_is_empty(Stack_t stack) { return stack->head == NULL; }
Boolean Stack_is_full(Stack_t stack) { return stack->size >= stack->max_stack; }

void Stack_push(Stack_t stack, Any_t data) {
  if (stack->max_stack <= -1 && Stack_is_full(stack)) {
    fprintf(stderr, "[Error]: StackOverFlow\n");
    exit(1);
  }
  Node_t node = Node_new(data);
  node->next = stack->head;
  stack->head = node;
  stack->size++;
}

Any_t Stack_pop(Stack_t stack) {
  if (Stack_is_empty(stack)) {
    fprintf(stderr, "[Error]: StackUnderFlow\n");
    exit(1);
  }
  Node_t tmp = stack->head;
  stack->head = tmp->next;
  stack->size--;
  Any_t data = tmp->data;
  free(tmp);
  return data;
}
