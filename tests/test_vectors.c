#include "../include/Testlib.h"
#include "../include/Vectors.h"

TEST test_vector_length() {
  Vector_t vec = Vector_new();
  Vector_push(vec, Int(69));
  Vector_push(vec, Int(420));
  ASSERT_EQ_INT(2, Vector_len(vec));
}

TEST check_if_pushed_elems_are_modified() {
  Vector_t vec = Vector_new();
  Str_t pushed_str = Str("Hello!");
  Vector_push(vec, pushed_str);
  Str_t received_str = Vector_at(vec, 0);
  ASSERT_EQ_STR(pushed_str, received_str);
}

TEST test_index_out_of_bound() {
  Vector_t vec = Vector_new();
  Vector_push(vec, Int(69));
  ASSERT_NULL_POINTER(Vector_at(vec, 1));
}

struct Person {
  int age;
};

void people_age_acc(Any_t person, Any_t acc) {
  struct Person *p = person;
  *(int *)acc += p->age;
}

TEST test_vector_reduce() {
  struct Person p = {.age = 69};
  struct Person p2 = {.age = 420};

  Vector_t people = Vector_new();
  Vector_push(people, &p);
  Vector_push(people, &p2);

  int age_acc = 0;
  Vector_reduce(people, people_age_acc, &age_acc);
  ASSERT_EQ_INT(p.age + p2.age, age_acc);
}

int main() {
  TestSuite_t ts = TestSuite_new("Vectors tests");

  TestSuite_add(ts, test_vector_length);
  TestSuite_add(ts, check_if_pushed_elems_are_modified);
  TestSuite_add(ts, test_index_out_of_bound);
  TestSuite_add(ts, test_vector_reduce);

  return TestSuite_run(ts);
}
