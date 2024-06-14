#include <stdio.h>
#include <stdlib.h>

#include "../include/MPSC.h"
#include "../include/Queue.h"

Channel *Channel_new(void) {
  Channel *chan = malloc(sizeof(Channel));
  chan->queue = Queue_new();
  pthread_mutex_init(&chan->mutex, NULL);
  pthread_cond_init(&chan->cond, NULL);
  return chan;
}

int Channel_send(Channel *chan, void *message) {
  pthread_mutex_lock(&chan->mutex);
  if (Queue_equeue(chan->queue, message)) {
    pthread_mutex_unlock(&chan->mutex);
    return -1;
  }
  // tells at least one thread waiting about the new message
  pthread_cond_signal(&chan->cond);
  pthread_mutex_unlock(&chan->mutex);
  return 0;
}

void *Channel_recv(Channel *chan) {
  pthread_mutex_lock(&chan->mutex);
  // block until get some message
  while (Queue_is_empty(chan->queue)) {
    pthread_cond_wait(&chan->cond, &chan->mutex);
  }
  void *message = Queue_dequeue(chan->queue);
  pthread_mutex_unlock(&chan->mutex);
  return message;
}
