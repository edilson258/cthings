#include <pthread.h>
#include <stdlib.h>

#include "../include/Vectors.h"

Vector_t Vector_new() {
  Vector_t vec = malloc(sizeof(Vector));
  vec->size = 0;
  vec->head = NULL;
  vec->tail = NULL;
  vec->head_iter = NULL;
  pthread_mutex_init(&vec->mutx, NULL);
  return vec;
}

Boolean Vector_is_empty(Vector_t vec) {
  pthread_mutex_lock(&vec->mutx);
  Boolean is_empty = vec->size == 0;
  pthread_mutex_unlock(&vec->mutx);
  return is_empty;
}

void Vector_push(Vector_t vec, Any_t elem) {
  if (Vector_is_empty(vec)) {
    Node_t node = Node_new(elem);
    pthread_mutex_lock(&vec->mutx);
    vec->head = node;
    vec->tail = node;
    vec->head_iter = node;
  } else {
    Node_t node = Node_new(elem);
    pthread_mutex_lock(&vec->mutx);
    vec->tail->next = node;
    vec->tail = node;
  }
  vec->size++;
  pthread_mutex_unlock(&vec->mutx);
}

Vector_t Vector_map(Vector_t vec, MapFn fn) {
  Vector_t new_vec = Vector_new();
  pthread_mutex_lock(&vec->mutx);
  Node_t tmp = vec->head;
  while (tmp) {
    Vector_push(new_vec, fn(tmp->data));
    tmp = tmp->next;
  }
  pthread_mutex_unlock(&vec->mutx);
  return new_vec;
}

void Vector_reduce(Vector_t vec, ReduceFn fn, Any_t acc) {
  pthread_mutex_lock(&vec->mutx);
  Node_t tmp = vec->head;
  while (tmp) {
    fn(tmp->data, acc);
    tmp = tmp->next;
  }
  pthread_mutex_unlock(&vec->mutx);
}

Vector_t Vector_filter(Vector_t vec, FilterFn fn) {
  Vector_t filter_vec = Vector_new();
  pthread_mutex_lock(&vec->mutx);
  Node_t tmp = vec->head;
  while (tmp) {
    if (fn(tmp->data)) {
      Vector_push(filter_vec, tmp->data);
    }
    tmp = tmp->next;
  }
  pthread_mutex_unlock(&vec->mutx);
  return filter_vec;
}

size_t Vector_len(Vector_t vec) {
  pthread_mutex_lock(&vec->mutx);
  size_t size = vec->size;
  pthread_mutex_unlock(&vec->mutx);
  return size;
}

Any_t Vector_at(Vector_t vec, size_t index) {
  if (index < 0 || index >= vec->size) {
    return NULL;
  }
  pthread_mutex_lock(&vec->mutx);
  Node_t tmp = vec->head;
  for (size_t i = 0; i < index; ++i) {
    tmp = tmp->next;
  }
  pthread_mutex_unlock(&vec->mutx);
  return tmp->data;
}

Any_t Vector_remove(Vector_t vec, size_t index) {
  if (index < 0 || index >= vec->size) {
    return NULL;
  }
  pthread_mutex_lock(&vec->mutx);
  vec->size--;
  if (index == 0) {
    Node_t tmp = vec->head;
    vec->head = tmp->next;
    vec->head_iter = tmp->next;
    Any_t data = tmp->data;
    free(tmp);
    pthread_mutex_unlock(&vec->mutx);
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
  pthread_mutex_unlock(&vec->mutx);
  return data;
}

Boolean Vector_iter(Vector_t vec, Any_t _Nullable *elem) {
  pthread_mutex_lock(&vec->mutx);
  if (!vec->head_iter) {
    pthread_mutex_unlock(&vec->mutx);
    return False;
  }
  *elem = vec->head_iter->data;
  vec->head_iter = vec->head_iter->next;
  pthread_mutex_unlock(&vec->mutx);
  return True;
}

void Vector_iter_reset(Vector_t vec) {
  pthread_mutex_lock(&vec->mutx);
  vec->head_iter = vec->head;
  pthread_mutex_unlock(&vec->mutx);
}
