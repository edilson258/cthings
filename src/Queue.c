#include <errno.h>
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
  return queue;
}

int Queue_is_empty(Queue_t queue) { return queue->head == NULL; }

void *Queue_dequeue(Queue_t queue) {
  if (Queue_is_empty(queue)) {
    return NULL;
  }
  Node_t node = queue->head;
  queue->head = node->next;
  void *message = node->data;
  free(node);
  return message;
}

int Queue_equeue(Queue_t queue, void *data) {
  Node_t node = Node_new(data);
  if (node == NULL) {
    return -1;
  }

  if (!queue->head) {
    queue->head = node;
  } else {
    /*
     * O(n)
     */
    Node_t tmp = queue->head;
    while (tmp->next)
      tmp = tmp->next;
    tmp->next = node;
  }
  return 0;
}
