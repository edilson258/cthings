# C Safe Channel (inspired by Rust's mpsc)

This is a header only library that
enables safe comunication between
threads through a
multiple producer single consumer channel.

<b>The main ideia is to have a channel in which
many threads may send messages to but
only one thread can receive from the channel.</b>

## Features
- [x] Powered by [pthreads](https://en.wikipedia.org/wiki/Pthreads)
- [x] Thread safe
- [x] Free waiting
- [ ] Separation between channel input `send` and output `revc`

## Usage

1. Download the `mpcs.h` header file

```shell
curl -O https://raw.githubusercontent.com/edilson258/mpsc/main/include/mpsc.h
```

2. Simple Example

```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MPSC_IMPLEMENTATION
#include "mpsc.h"

#define ONE_SEC_IN_MICRO_SEC 1000000

char *prepare_str_msg(char *str) {
  unsigned long str_len = strlen(str);
  char *message = malloc(sizeof(char) * (str_len + 1));
  strncpy(message, str, str_len);
  return message;
}

// first producer
void *producer_hello(void *arg) {
  Channel *chan = (Channel *)arg;
  // sleep for 1 sec to simulate some work
  usleep(ONE_SEC_IN_MICRO_SEC);
  // send the message through channel
  send(chan, prepare_str_msg("Hello"));
  return NULL;
}

// second producer
void *producer_world(void *arg) {
  Channel *chan = (Channel *)arg;
  // sleep for 3 sec to simulate some work
  usleep(ONE_SEC_IN_MICRO_SEC * 3);
  // send the message through channel
  send(chan, prepare_str_msg("World"));
  return NULL;
}

// The single receiver
void *receiver(void *arg) {
  Channel *chan = (Channel *)arg;
  for (int i = 0; i < 2; ++i) {
    char *msg = (char *)recv(chan);
    if (msg) {
      printf("Received: %s\n", msg);
      free(msg);
    }
  }
  return NULL;
}

int main(void) {
  Channel *chan = channel_init();

  pthread_t first_producer, second_producer, receiver_id;
  pthread_create(&first_producer, NULL, producer_hello, chan);
  pthread_create(&second_producer, NULL, producer_world, chan);
  pthread_create(&receiver_id, NULL, receiver, chan);
  pthread_join(first_producer, NULL);
  pthread_join(second_producer, NULL);
  pthread_join(receiver_id, NULL);

  return 0;
}
```

## Contribuitions

Feel free to fork and play with it. Pull requests are welcome!
