#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/// This structure wraps the message in the Queue
typedef struct Node {
  void *data;
  struct Node *next;
} Node;

/// Will create an instace of Node and intiliaze it with default values
Node *node_init(void *data) {
  Node *node = malloc(sizeof(Node));
  if (node == NULL) {
    fprintf(stderr, "[Error]: Couldn't allocate space for message node: %s\n",
            strerror(errno));
    return NULL;
  }
  node->data = data;
  node->next = NULL;
  return node;
}

/// This structure represents a channel through which multiple
/// threads can pass and receive messages
typedef struct {
  Node *head;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
} Channel;

/// Will create an instace of Channel and intiliaze it with default values
Channel *channel_init(void) {
  Channel *chan = malloc(sizeof(Channel));
  chan->head = NULL;
  pthread_mutex_init(&chan->mutex, NULL);
  pthread_cond_init(&chan->cond, NULL);
  return chan;
}

int send(Channel *chan, void *message) {
  Node *node = node_init(message);
  if (node == NULL) {
    return -1;
  }

  pthread_mutex_lock(&chan->mutex);

  if (!chan->head) {
    chan->head = node;
  } else {
    node->next = chan->head;
    chan->head = node;
  }

  pthread_cond_signal(&chan->cond);
  pthread_mutex_unlock(&chan->mutex);
  return 0;
}

void *recv(Channel *chan) {
  pthread_mutex_lock(&chan->mutex);

  while (!chan->head) {
    pthread_cond_wait(&chan->cond, &chan->mutex);
  }

  Node *node = chan->head;
  void *data = node->data;
  chan->head = node->next;

  pthread_mutex_unlock(&chan->mutex);

  free(node);
  return data;
}

void *producer(void *arg) {
  Channel *chan = (Channel *)arg;
  for (int i = 0; i < 3; ++i) {
    int *data = malloc(sizeof(int));
    *data = 69;
    send(chan, data);
    usleep(1000000); // sleep for 1 sec
  }
  return NULL;
}

void *receiver(void *arg) {
  Channel *chan = (Channel *)arg;
  while (1) {
    int *msg = (int *)recv(chan);
    if (msg) {
      printf("Received: %d\n", *msg);
      free(msg);
    }
  }

  return NULL;
}

int main(void) {
  printf("Hello, Sea Man!\n");

  Channel *chan = channel_init();

  pthread_t p1, p2, receiver_id;
  pthread_create(&p1, NULL, producer, chan);
  pthread_create(&p2, NULL, producer, chan);
  pthread_create(&receiver_id, NULL, receiver, chan);
  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  pthread_join(receiver_id, NULL);

  return 0;
}
