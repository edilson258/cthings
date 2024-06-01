#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/mpsc.h"

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
  for (int i = 0; i < 6; ++i) {
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
