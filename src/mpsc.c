#include <stdlib.h>

#include "../include/mpsc.h"

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
