#include "../include/Testlib.h"
#include "../include/Vectors.h"

TEST(vectorLengthAfterPushAndRemoveElems) {
  Vector_t vec = Vector_new();
  Vector_push(vec, Int(69));
  Vector_push(vec, Int(420));

  ASSERT_EQ_INT(2, Vector_len(vec));

  Vector_remove(vec, 1);

  ASSERT_EQ_INT(1, Vector_len(vec));
}

TEST(ensurePushedElemsAreNotModified) {
  Vector_t vec = Vector_new();

  Str_t pushed_str = Str("Hello!");
  Str_t other_pushed_str = Str("Hi Mon!");
  Vector_push(vec, pushed_str);
  Vector_push(vec, other_pushed_str);

  Str_t received_str = Vector_at(vec, 0);
  Str_t other_received_str = Vector_at(vec, 1);

  ASSERT_EQ_STR(pushed_str, received_str);
  ASSERT_EQ_STR(other_pushed_str, other_received_str);
}

TEST(accessElemOutOfBound) {
  Vector_t vec = Vector_new();
  Vector_push(vec, Int(69));

  // access elem out of bound
  ASSERT_NULL(Vector_at(vec, 1));
}

TEST(vectorRemoveFunction) {
  Vector_t vec = Vector_new();
  Vector_push(vec, Int(69));

  // remove out of bound
  ASSERT_NULL(Vector_remove(vec, 1));

  ASSERT_EQ_INT(69, *(int *)Vector_remove(vec, 0));
}

struct Person {
  int age;
};

void people_age_acc(Any_t person, Any_t acc) {
  struct Person *p = person;
  *(int *)acc += p->age;
}

TEST(vectorReduceFunction) {
  struct Person p = {.age = 69};
  struct Person p2 = {.age = 420};

  Vector_t people = Vector_new();
  Vector_push(people, &p);
  Vector_push(people, &p2);

  ASSERT_EQ_INT(2, Vector_len(people));

  int age_acc = 0;
  Vector_reduce(people, people_age_acc, &age_acc);

  ASSERT_EQ_INT(p.age + p2.age, age_acc);
}

TEST(stressTest) {
  Vector_t vec = Vector_new();

  for (int i = 0; i < 300000; ++i) {
    Vector_push(vec, Int(1024 * i));
  }

  ASSERT_EQ_INT(300000, Vector_len(vec));
  ASSERT_EQ_INT(1024 * 50, *(int *)Vector_at(vec, 50));

  for (int i = 0; i < 150000; ++i) {
    Vector_remove(vec, 0);
  }

  ASSERT_EQ_INT(150000, Vector_len(vec));
}

int main() { return RUN_ALL_TESTS(); }
