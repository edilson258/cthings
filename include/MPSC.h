#ifndef MPSC_H
#define MPSC_H

#include <pthread.h>

#include "Common.h"
#include "Queue.h"

/*
 * Typedef: Channel
 *
 * Represents a Multiple Producer Single Consumer thread-safe channel, where
 * many threads can put messages but only one thread should read the messages.
 *
 */
typedef struct {
  Queue_t queue;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
} Channel;

/*
 * Typedef: Channel_t
 *
 * Is just a wrapper of `Channel *`
 *
 */
typedef Channel *Channel_t;

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
Channel_t Channel_new();

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
int Channel_send(Channel_t chan, Any_t message);

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
Any_t Channel_recv(Channel_t chan);

#endif // MPSC_H
