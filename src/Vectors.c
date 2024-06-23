#include <stdlib.h>

#include "../include/Vectors.h"

Vector_t Vector_new() {
  Vector_t vec = malloc(sizeof(Vector));
  vec->size = 0;
  vec->head = NULL;
  return vec;
}
int Vector_isempty(Vector_t vec) { return vec->size == 0; }

void Vector_push(Vector_t vec, Any_t elem) {
  if (Vector_isempty(vec)) {
    Node_t node = Node_new(elem);
    vec->head = node;
    vec->tail = node;
  } else {
    Node_t node = Node_new(elem);
    vec->tail->next = node;
    vec->tail = node;
  }
  vec->size++;
}

Vector_t Vector_map(Vector_t vec, MapFn fn) {
  Vector_t new_vec = Vector_new();
  Node_t tmp = vec->head;
  while (tmp) {
    Vector_push(new_vec, fn(tmp->data));
    tmp = tmp->next;
  }
  return new_vec;
}

void Vector_reduce(Vector_t vec, ReduceFn fn, Any_t acc) {
  Node_t tmp = vec->head;
  while (tmp) {
    fn(tmp->data, acc);
    tmp = tmp->next;
  }
}

Vector_t Vector_filter(Vector_t vec, FilterFn fn) {
  Vector_t filter_vec = Vector_new();

  Node_t tmp = vec->head;
  while (tmp) {
    if (fn(tmp->data)) {
      Vector_push(filter_vec, tmp->data);
    }
    tmp = tmp->next;
  }

  return filter_vec;
}

size_t Vector_len(Vector_t vec) { return vec->size; }

Any_t Vector_at(Vector_t vec, size_t index) {
  if (index < 0 || index >= vec->size) {
    return NULL;
  }

  Node_t tmp = vec->head;
  for (size_t i = 0; i < index; ++i) {
    tmp = tmp->next;
  }

  return tmp->data;
}

Any_t Vector_remove(Vector_t vec, size_t index) {
  if (index < 0 || index >= vec->size) {
    return NULL;
  }

  vec->size--;

  if (index == 0) {
    Node_t tmp = vec->head;
    vec->head = tmp->next;
    Any_t data = tmp->data;
    free(tmp);
    return data;
  }

  Node_t prev = vec->head;
  for (int i = 0; i < (index - 1); ++i) {
    prev = prev->next;
  }
  Node_t target = prev->next;
  prev->next = target->next;
  Any_t data = target->data;
  free(target);
  return data;
}
