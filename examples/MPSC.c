#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/Common.h"
#include "../include/MPSC.h"
#include "../include/Strings.h"

#define ONE_SEC_IN_MICRO_SEC 1000000

Any_t producer_hello(Any_t arg) {
  Channel_t chan = (Channel_t)arg;
  // sleep for 1 sec to simulate some work
  usleep(ONE_SEC_IN_MICRO_SEC);
  // send the message through channel
  String_t message = String_new("Hello");
  Channel_send(chan, message);
  return NULL;
}

Any_t producer_world(Any_t arg) {
  Channel_t chan = (Channel_t)arg;
  // sleep for 3 sec to simulate some work
  usleep(ONE_SEC_IN_MICRO_SEC * 3);
  // send the message through channel
  String_t message = String_new("World");
  Channel_send(chan, message);
  return NULL;
}

Any_t receiver(Any_t arg) {
  Channel_t chan = (Channel_t)arg;
  for (int i = 0; i < 2; ++i) {
    // block current thread until get some message
    String_t message = (String_t)Channel_recv(chan);
    if (message) {
      printf("Received: %s\n", String_val(message));
      String_drop(message);
    }
  }
  return NULL;
}

int main(void) {
  Channel_t chan = Channel_new();
  pthread_t first_producer, second_producer, receiver_id;
  pthread_create(&first_producer, NULL, producer_hello, chan);
  pthread_create(&second_producer, NULL, producer_world, chan);
  pthread_create(&receiver_id, NULL, receiver, chan);
  pthread_join(first_producer, NULL);
  pthread_join(second_producer, NULL);
  pthread_join(receiver_id, NULL);
  return 0;
}
