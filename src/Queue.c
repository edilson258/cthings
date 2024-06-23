#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/Queue.h"

Queue_t Queue_new() {
  Queue_t queue = malloc(sizeof(Queue));
  if (queue == NULL) {
    fprintf(stderr, "[Error]: Couldn't allocate space for message node: %s\n",
            strerror(errno));
    return NULL;
  }
  queue->head = NULL;
  queue->size = 0;
  pthread_mutex_init(&queue->mutx, NULL);
  return queue;
}

Boolean Queue_is_empty(Queue_t queue) {
  pthread_mutex_lock(&queue->mutx);
  Boolean is_empty = queue->head == NULL;
  pthread_mutex_unlock(&queue->mutx);
  return is_empty;
}

Any_t Queue_dequeue(Queue_t queue) {
  if (Queue_is_empty(queue)) {
    return NULL;
  }
  pthread_mutex_lock(&queue->mutx);
  Node_t tmp = queue->head;
  queue->head = tmp->next;
  Any_t data = tmp->data;
  free(tmp);
  queue->size--;
  pthread_mutex_unlock(&queue->mutx);
  return data;
}

int Queue_enqueue(Queue_t queue, Any_t data) {
  Node_t node = Node_new(data);
  if (node == NULL) {
    return -1;
  }
  pthread_mutex_lock(&queue->mutx);
  if (!queue->head) {
    queue->head = node;
    queue->tail = node;
  } else {
    queue->tail->next = node;
    queue->tail = node;
  }
  queue->size++;
  pthread_mutex_unlock(&queue->mutx);
  return 0;
}

size_t Queue_size(Queue_t queue) {
  pthread_mutex_lock(&queue->mutx);
  size_t queue_size = queue->size;
  pthread_mutex_unlock(&queue->mutx);
  return queue_size;
}
