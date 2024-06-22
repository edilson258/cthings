#include "../include/Stack.h"
#include "../include/Testlib.h"

TEST(ensureStackIsFull) {
  Stack_t stack = Stack_new(2);
  Stack_push(stack, Int(69));
  Stack_push(stack, Int(420));

  ASSERT_TRUE(Stack_is_full(stack));
}

TEST(ensurePushedElemsAreNotModified) {
  Stack_t stack = Stack_new(2);
  Stack_push(stack, Int(69));
  Stack_push(stack, Int(420));

  ASSERT_EQ_INT(420, *(int *)Stack_pop(stack));
  ASSERT_EQ_INT(69, *(int *)Stack_pop(stack));
}

int main(void) { return RUN_ALL_TESTS(); }
