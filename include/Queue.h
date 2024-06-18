#ifndef QUEUE_H
#define QUEUE_H

#include "Common.h"
#include <stddef.h>

/*
 * Structure: Queue
 *
 * Represents a queue data structure.
 *
 * Members:
 * - Node_t head: Pointer to the head of the queue.
 */
typedef struct {
  Node_t head;
  size_t size;
} Queue;

typedef Queue *Queue_t;

/*
 * Function: Queue_new() -> Queue_t
 *
 * Creates and initializes a new queue.
 *
 * Returns:
 * - Queue_t: Pointer to the newly created queue, or NULL if allocation fails.
 */
Queue_t Queue_new();

/*
 * Function: Queue_is_empty(Queue_t queue) -> int
 *
 * Checks if the queue is empty.
 *
 * Parameters:
 * - Queue_t queue: Pointer to the queue to check.
 *
 * Returns:
 * - int: 1 if the queue is empty, 0 otherwise.
 */
int Queue_is_empty(Queue_t queue);

/*
 * Function: Queue_dequeue(Queue_t queue) -> void*
 *
 * Removes and returns the data from the front of the queue.
 *
 * Parameters:
 * - Queue_t queue: Pointer to the queue from which to dequeue.
 *
 * Returns:
 * - void*: Pointer to the data removed from the queue, or NULL if the queue is
 * empty.
 */
void *Queue_dequeue(Queue_t queue);

/*
 * Function: Queue_enqueue(Queue_t queue, void *data) -> int
 *
 * Enqueues data at the end of the queue.
 *
 * Parameters:
 * - Queue_t queue: Pointer to the queue to which data is to be enqueued.
 * - void *data: Pointer to the data to be enqueued.
 *
 * Returns:
 * - int: 0 on success, -1 if allocation fails when creating a new node.
 */
int Queue_enqueue(Queue_t queue, Any_t data);

/*
 * Function: Queue_size(Queue_t queue) -> size_t
 *
 * Will return the number of elements in the Queue `queue`
 *
 * Parameters:
 *
 * - Queue_t queue: The queue to know its size
 *
 * Returns:
 *
 * - size_t: The number of elements in the Queue `queue`
 *
 */
size_t Queue_size(Queue_t queue);

#endif // QUEUE_H
