#include <stdio.h>
#include <stdlib.h>

#include "../include/MPSC.h"
#include "../include/Queue.h"

/*
 * Function: Channel_new() -> Channel_t
 *
 * Will create a new instance of `Channel` and returns it's pointer
 *
 * Returns:
 *
 * - Channel_t: a pointer to the created channel
 *
 */
Channel_t Channel_new() {
  Channel_t chan = malloc(sizeof(Channel));
  chan->queue = Queue_new();
  pthread_mutex_init(&chan->mutex, NULL);
  pthread_cond_init(&chan->cond, NULL);
  return chan;
}

/*
 * Function: Channel_send(Channel_t chan, Any_t message) -> int
 *
 * Will put the message `message` on the Channel `chan` and in case of error
 * will be printed in the stdout
 *
 * Parameters:
 *
 * - Channel_t chan: The channel where to put the message `message`
 * - Any_t message: The message to bet put on the Channel `chan`
 *
 * Returns:
 *
 * - 0: On success
 * - -1: On error
 *
 */
int Channel_send(Channel_t chan, Any_t message) {
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

/*
 * Function: Channel_recv(Channel_t chan) -> Any_t
 *
 * Will read a message from the channel `chan`. If the channel is empty, the
 * current thread will blocked until some message be avalible
 *
 * `Note`: The read message will be popped out from the channel, thus, each
 * channel should have a Single Consumer to avoid loss of information
 *
 *
 * Parameters:
 *
 * - Channel_t chan: The channel where the message will be read
 *
 * Returns:
 *
 * - Any_t: a message read from channel `chan`
 *
 */
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
