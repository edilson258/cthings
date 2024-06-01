#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/queue.h"

int is_queue_empty(MessagesQueue *q) { return q->head == NULL; }

MessagesQueue *queue_init() {
  MessagesQueue *queue = malloc(sizeof(MessagesQueue));
  if (queue == NULL) {
    fprintf(stderr, "[Error]: Couldn't allocate space for message node: %s\n",
            strerror(errno));
    return NULL;
  }
  queue->head = NULL;
  return queue;
}

Node *node_init(void *message) {
  Node *node = malloc(sizeof(Node));
  if (node == NULL) {
    fprintf(stderr, "[Error]: Couldn't allocate space for a node: %s\n",
            strerror(errno));
    return NULL;
  }
  node->message = message;
  node->next = NULL;
  return node;
}

/// This function will push a new message at the end of the queue, once the
/// queue is a linked list the complexity might be O(n)
int enqueue(MessagesQueue *q, void *message) {
  Node *node = node_init(message);
  if (node == NULL) {
    return -1;
  }

  if (!q->head) {
    q->head = node;
  } else {
    /*
     * O(n)
     */
    Node *tmp = q->head;
    while (tmp->next)
      tmp = tmp->next;
    tmp->next = node;
  }
  return 0;
}

void *dequeue(MessagesQueue *q) {
  if (is_queue_empty(q)) {
    return NULL;
  }
  Node *node = q->head;
  q->head = node->next;
  void *message = node->message;
  free(node);
  return message;
}
