#ifndef QUEUE_H
#define QUEUE_H

/// This structure wraps the message in a linked list node to be stored in the
/// messages queue
typedef struct Node {
  void *message;
  struct Node *next;
} Node;

/// This struct holds the head of the queue of messages and some other metadata
/// about the queue
typedef struct {
  Node *head;
} MessagesQueue;

MessagesQueue *queue_init();
Node *node_init(void *message);
void *dequeue(MessagesQueue *q);
int enqueue(MessagesQueue *q, void *message);
int is_queue_empty(MessagesQueue *q);

#endif
