#ifndef QUEUE_H
#define QUEUE_H

/// A wrapper of the data
typedef struct Node {
  void *data;
  struct Node *next;
} Node;

typedef Node *Node_t;

/// A simple queue that managers any kind of data
typedef struct {
  Node_t head;
} Queue;

typedef Queue *Queue_t;

Queue_t Queue_new();
int Queue_is_empty(Queue_t queue);
void *Queue_dequeue(Queue_t queue);
int Queue_equeue(Queue_t queue, void *data);

Node_t Node_new(void *data);

#endif
