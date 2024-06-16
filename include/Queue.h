#ifndef QUEUE_H
#define QUEUE_H

#include "Common.h"

typedef struct {
  Node_t head;
} Queue;

typedef Queue *Queue_t;

Queue_t Queue_new();
int Queue_is_empty(Queue_t queue);
void *Queue_dequeue(Queue_t queue);
int Queue_equeue(Queue_t queue, void *data);

#endif
