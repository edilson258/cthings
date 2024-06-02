#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MPSC_IMPLEMENTATION
#include "../include/mpsc.h"

#define ONE_SEC_IN_MICRO_SEC 1000000

char *prepare_str_msg(char *str) {
  unsigned long str_len = strlen(str);
  char *message = malloc(sizeof(char) * (str_len + 1));
  strncpy(message, str, str_len);
  return message;
}

void *producer_hello(void *arg) {
  Channel *chan = (Channel *)arg;
  // sleep for 1 sec to simulate some work
  usleep(ONE_SEC_IN_MICRO_SEC);
  // send the message through channel
  send(chan, prepare_str_msg("Hello"));
  return NULL;
}

void *producer_world(void *arg) {
  Channel *chan = (Channel *)arg;
  // sleep for 3 sec to simulate some work
  usleep(ONE_SEC_IN_MICRO_SEC * 3);
  // send the message through channel
  send(chan, prepare_str_msg("World"));
  return NULL;
}

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
