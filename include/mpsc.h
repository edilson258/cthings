#ifndef MPSC_H
#define MPSC_H

#include <pthread.h>

#include "queue.h"

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

#endif
