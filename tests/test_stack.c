#include "../include/Stack.h"
#include "../include/Testlib.h"

TEST LIFO_property_on_push_and_pop() {
  Stack_t stack = Stack_new(3);
  Stack_push(stack, Int(69));
  Stack_push(stack, Int(420));
  ASSERT_EQ_INT(420, *((int *)Stack_pop(stack)));
}

TEST stack_is_full() {
  Stack_t stack = Stack_new(2);
  Stack_push(stack, Int(69));
  Stack_push(stack, Int(420));
  ASSERT_TRUE(Stack_is_full(stack));
}

int main() {
  TestSuite_t ts = TestSuite_new("Stack tests");
  TestSuite_add(ts, LIFO_property_on_push_and_pop);
  TestSuite_add(ts, stack_is_full);
  return TestSuite_run(ts);
}
