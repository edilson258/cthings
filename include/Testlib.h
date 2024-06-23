#ifndef TEST_LIBRARY_H
#define TEST_LIBRARY_H

#include <stddef.h>

#include "Common.h"

typedef void (*TestBody)();

struct Test {
  Str_t name;
  TestBody body;
  Boolean has_failed;
};

struct TestSuite {
  Str_t name;
  size_t cap;
  size_t count;
  size_t fails_count;
  struct Test **tests;
  struct Test *curr_test;
};

extern struct TestSuite *global_test_suite_object;

/*
 * INTERNAL API
 *
 */

void setup_global_test_suite_object(Str_t file);
struct Test *Test_new(Str_t name, TestBody body);
void register_test(Str_t name, TestBody body, Str_t filename);

/*
 * Public API
 *
 */

Boolean __assert_null__(Any_t expression, int line_number);
Boolean __assert_true__(Boolean expression, int line_number);
Boolean __assert_false__(Boolean expression, int line_number);
Boolean __assert_eq_int__(int expected, int provided, int line_number);
Boolean __assert_neq_int__(int expected, int provided, int line_number);
Boolean __assert_eq_str__(Str_t expected, Str_t provided, int line_number);
Boolean __assert_eq_struct__(Any_t expected, Any_t provided, int line_number);

/// Create a new test case
#define TEST(name)                                                             \
  static void test_##name();                                                   \
  static void __attribute__((constructor)) register_test_##name() {            \
    register_test(#name, test_##name, __FILE_NAME__);                          \
  }                                                                            \
  static void test_##name()

#define ASSERT_NULL(expression)                                                \
  if (!(__assert_null__((expression), __LINE__))) {                            \
    return;                                                                    \
  }

#define ASSERT_TRUE(expression)                                                \
  if (!(__assert_true__((expression), __LINE__))) {                            \
    return;                                                                    \
  }

#define ASSERT_FALSE(expression)                                               \
  if (!(__assert_false__((expression), __LINE__))) {                           \
    return;                                                                    \
  }

#define ASSERT_EQ_INT(expected, provided)                                      \
  if (!(__assert_eq_int__((expected), (provided), __LINE__))) {                \
    return;                                                                    \
  }

#define ASSERT_NEQ_INT(expected, provided)                                     \
  if (!(__assert_neq_int__((expected), (provided), __LINE__))) {               \
    return;                                                                    \
  }

#define ASSERT_EQ_STR(expected, provided)                                      \
  if (!(__assert_eq_str__((expected), (provided), __LINE__))) {                \
    return;                                                                    \
  }

#define ASSERT_EQ_STRUCT(expected, provided)                                   \
  if (!(__assert_eq_struct__((expected), (provided), __LINE__))) {             \
    return;                                                                    \
  }

/// Will run all `TEST()` cases and returns the fails count
size_t RUN_ALL_TESTS();

#endif // TEST_LIBRARY_H
