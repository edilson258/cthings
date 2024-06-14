#ifndef MPSC_H
#define MPSC_H

#include <pthread.h>

#include "queue.h"

/// This structure represents a channel through which multiple
/// threads can pass and receive messages
typedef struct {
  Queue_t queue;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
} Channel;

typedef Channel *Channel_t;

Channel_t Channel_new(void);
/// Sends a message through the channel and wakes at least one thread
/// sleeping or waiting for some message
int Channel_send(Channel_t chan, void *message);
/// This functions receive a message from the channel
/// will take first avalible message in the Queue
/// if the channel is empty will block the current thread until some message be
/// send
void *Channel_recv(Channel_t chan);

#endif // MPSC_H
