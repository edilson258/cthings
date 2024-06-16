#include <stdio.h>
#include <stdlib.h>

#include "../include/MPSC.h"
#include "../include/Queue.h"

Channel_t Channel_new() {
  Channel_t chan = malloc(sizeof(Channel));
  chan->queue = Queue_new();
  pthread_mutex_init(&chan->mutex, NULL);
  pthread_cond_init(&chan->cond, NULL);
  return chan;
}

int Channel_send(Channel_t chan, Any_t message) {
  pthread_mutex_lock(&chan->mutex);
  if (Queue_enqueue(chan->queue, message)) {
    pthread_mutex_unlock(&chan->mutex);
    return -1;
  }
  // tells at least one thread waiting about the new message
  pthread_cond_signal(&chan->cond);
  pthread_mutex_unlock(&chan->mutex);
  return 0;
}

Any_t Channel_recv(Channel_t chan) {
  pthread_mutex_lock(&chan->mutex);
  // block until get some message
  while (Queue_is_empty(chan->queue)) {
    pthread_cond_wait(&chan->cond, &chan->mutex);
  }
  Any_t message = Queue_dequeue(chan->queue);
  pthread_mutex_unlock(&chan->mutex);
  return message;
}
