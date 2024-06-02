#ifndef MPSC_H
#define MPSC_H

#include <pthread.h>

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

/// This structure represents a channel through which multiple
/// threads can pass and receive messages
typedef struct {
  MessagesQueue *queue;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
} Channel;

Channel *channel_init(void);
/// Sends a message through the channel and wakes at least one thread
/// sleeping or waiting for some message
int send(Channel *chan, void *message);
/// This functions receive a message from the channel
/// will take first avalible message in the Queue
/// if the channel is empty will block the current thread until some message be
/// send
void *recv(Channel *chan);
MessagesQueue *queue_init();
Node *node_init(void *message);
void *dequeue(MessagesQueue *q);
int enqueue(MessagesQueue *q, void *message);
int is_queue_empty(MessagesQueue *q);

#ifdef MPSC_IMPLEMENTATION

#include <errno.h>
#include <stdio.h>

Channel *channel_init(void) {
  Channel *chan = malloc(sizeof(Channel));
  chan->queue = queue_init();
  pthread_mutex_init(&chan->mutex, NULL);
  pthread_cond_init(&chan->cond, NULL);
  return chan;
}

int send(Channel *chan, void *message) {
  pthread_mutex_lock(&chan->mutex);
  if (enqueue(chan->queue, message)) {
    pthread_mutex_unlock(&chan->mutex);
    return -1;
  }
  // tells at least one thread waiting about the new message
  pthread_cond_signal(&chan->cond);
  pthread_mutex_unlock(&chan->mutex);
  return 0;
}

void *recv(Channel *chan) {
  pthread_mutex_lock(&chan->mutex);
  // block until get some message
  while (is_queue_empty(chan->queue)) {
    pthread_cond_wait(&chan->cond, &chan->mutex);
  }
  void *message = dequeue(chan->queue);
  pthread_mutex_unlock(&chan->mutex);
  return message;
}

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

#endif // MPSC_IMPLEMENTATION
#endif // MPSC_H
