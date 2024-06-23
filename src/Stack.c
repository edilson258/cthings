#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/Stack.h"

Stack_t Stack_new(size_t max_stack) {
  Stack_t stack = malloc(sizeof(Stack));
  stack->head = NULL;
  stack->size = 0;
  stack->max_stack = max_stack;
  pthread_mutex_init(&stack->mutx, NULL);
  return stack;
}

Boolean Stack_is_empty(Stack_t stack) {
  pthread_mutex_lock(&stack->mutx);
  Boolean is_empty = stack->head == NULL;
  pthread_mutex_unlock(&stack->mutx);
  return is_empty;
}

Boolean Stack_is_full(Stack_t stack) {
  pthread_mutex_lock(&stack->mutx);
  Boolean is_full = stack->size >= stack->max_stack;
  pthread_mutex_unlock(&stack->mutx);
  return is_full;
}

int Stack_push(Stack_t stack, Any_t data) {
  if (stack->max_stack <= -1 && Stack_is_full(stack)) {
    return -1;
  }
  Node_t node = Node_new(data);
  pthread_mutex_lock(&stack->mutx);
  node->next = stack->head;
  stack->head = node;
  stack->size++;
  pthread_mutex_unlock(&stack->mutx);
  return 0;
}

Any_t Stack_pop(Stack_t stack) {
  if (Stack_is_empty(stack)) {
    return NULL;
  }
  pthread_mutex_lock(&stack->mutx);
  Node_t tmp = stack->head;
  stack->head = tmp->next;
  stack->size--;
  Any_t data = tmp->data;
  free(tmp);
  pthread_mutex_unlock(&stack->mutx);
  return data;
}
