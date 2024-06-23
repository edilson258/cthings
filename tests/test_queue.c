#include <pthread.h>

#include "../include/Queue.h"
#include "../include/Testlib.h"

TEST(ensureQueueIsEmpty) {
  Queue_t q = Queue_new();
  ASSERT_TRUE(Queue_is_empty(q));
  Queue_enqueue(q, Int(69));
  Queue_dequeue(q);
  ASSERT_TRUE(Queue_is_empty(q));
}

TEST(stressTesting) {
  Queue_t q = Queue_new();
  for (int i = 1; i <= 50000; ++i) {
    Queue_enqueue(q, Int(i));
  }

  ASSERT_EQ_INT(50000, (int)Queue_size(q));

  for (int i = 1; i <= 50000; ++i) {
    ASSERT_EQ_INT(i, *(int *)Queue_dequeue(q));
  }

  ASSERT_TRUE(Queue_is_empty(q));

  for (int i = 1; i <= 100000; i += 10) {
    Queue_enqueue(q, Int(i));
    ASSERT_EQ_INT(i, *(int *)Queue_dequeue(q));
  }
}

/*
 * Multi-Thread testing
 */

Any_t process_1(Any_t arg) {
  Queue_t q = arg;
  Queue_enqueue(q, Str("From process_1"));
  return NULL;
}

Any_t process_2(Any_t arg) {
  Queue_t q = arg;
  Queue_enqueue(q, Str("From process_2"));
  return NULL;
}

Any_t process_3(Any_t arg) {
  Queue_t q = arg;
  Queue_enqueue(q, Str("From process_3"));
  return NULL;
}

TEST(behaviorOnMultiThreadedScenario) {
  Queue_t q = Queue_new();

  pthread_t p1;
  pthread_create(&p1, NULL, process_1, q);
  pthread_join(p1, NULL);

  ASSERT_EQ_INT(1, (int)Queue_size(q));
  ASSERT_EQ_STR("From process_1", (Str_t)Queue_dequeue(q));

  pthread_t p2;
  pthread_create(&p2, NULL, process_2, q);
  pthread_join(p2, NULL);

  pthread_t p3;
  pthread_create(&p3, NULL, process_3, q);
  pthread_join(p3, NULL);

  ASSERT_EQ_INT(2, (int)Queue_size(q));

  Queue_dequeue(q); // From process_2

  ASSERT_EQ_STR("From process_3", (Str_t)Queue_dequeue(q));
}

int main(void) { return RUN_ALL_TESTS(); }
