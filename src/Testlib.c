#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Testlib.h"

#define MAX_TESTS_PER_SUITE 50

/// The instance of TestSuite that represents a suite of test
/// every file that contains `TEST()` cases is considered a test suite
struct TestSuite *global_test_suite_object = NULL;

void setup_global_test_suite_object(Str_t filename) {
  global_test_suite_object = malloc(sizeof(struct TestSuite));
  global_test_suite_object->name = filename;
  global_test_suite_object->curr_test = NULL;
  global_test_suite_object->cap = MAX_TESTS_PER_SUITE;
  global_test_suite_object->count = 0;
  global_test_suite_object->fails_count = 0;
  global_test_suite_object->tests =
      malloc(sizeof(struct Test *) * MAX_TESTS_PER_SUITE);
}

struct Test *Test_new(Str_t name, TestBody body) {
  struct Test *test = malloc(sizeof(struct Test));
  test->name = name;
  test->body = body;
  test->has_failed = False;
  return test;
}

void register_test(Str_t name, TestBody body, Str_t filename) {
  // @TODO: check bounds of global_test_suite_object

  if (!global_test_suite_object) {
    setup_global_test_suite_object(filename);
  }
  global_test_suite_object->tests[global_test_suite_object->count++] =
      Test_new(name, body);
}

void log_fail(int line_number, Str_t formatter, ...) {
  fprintf(stderr, "[\033[31m FAILED \033[0m] %s:%s:%d: ",
          global_test_suite_object->name,
          global_test_suite_object->curr_test->name, line_number);

  va_list args;
  va_start(args, formatter);
  vfprintf(stderr, formatter, args);
  va_end(args);

  fprintf(stderr, "\n");
}

Boolean __assert_null__(Any_t expression, int line_number) {
  if (expression) {
    log_fail(line_number, "expects \"NULL\"");
    global_test_suite_object->curr_test->has_failed = True;
    return False;
  }
  return True;
}

Boolean __assert_true__(Boolean expression, int line_number) {
  if (!expression) {
    log_fail(line_number, "expects \"True\"");
    global_test_suite_object->curr_test->has_failed = True;
    return False;
  }
  return True;
}

Boolean __assert_false__(Boolean expression, int line_number) {
  if (expression) {
    log_fail(line_number, "expects \"False\"");
    global_test_suite_object->curr_test->has_failed = True;
    return False;
  }
  return True;
}

Boolean __assert_eq_int__(int expected, int provided, int line_number) {
  if (expected != provided) {
    log_fail(line_number, "expects \"%d\" but found \"%d\"", expected,
             provided);
    global_test_suite_object->curr_test->has_failed = True;
    return False;
  }
  return True;
}

Boolean __assert_neq_int__(int expected, int provided, int line_number) {
  if (expected == provided) {
    log_fail(line_number, "expects \"%d\" and \"%d\" to be different", expected,
             provided);
    global_test_suite_object->curr_test->has_failed = True;
    return False;
  }
  return True;
}

Boolean __assert_eq_str__(Str_t expected, Str_t provided, int line_number) {
  if (strcmp(expected, provided) != 0) {
    log_fail(line_number, "expects \"%s\" but found \"%s\"", expected,
             provided);
    global_test_suite_object->curr_test->has_failed = True;
    return False;
  }
  return True;
}

Boolean __assert_eq_struct__(Any_t expected, Any_t provided, int line_number) {
  if (memcmp(expected, provided, sizeof(expected)) != 0) {
    log_fail(line_number, "provided struct is not equal to expected");
    global_test_suite_object->curr_test->has_failed = True;
    return False;
  }
  return True;
}

size_t RUN_ALL_TESTS() {
  size_t fails_count = 0;
  for (size_t i = 0; i < global_test_suite_object->count; ++i) {
    global_test_suite_object->curr_test = global_test_suite_object->tests[i];
    global_test_suite_object->tests[i]->body(); // Test invocation
    if (global_test_suite_object->curr_test->has_failed) {
      fails_count++;
      continue;
    }
    printf("[\033[32m PASSED \033[0m] %s:%s\n", global_test_suite_object->name,
           global_test_suite_object->curr_test->name);
  }
  return fails_count;
}
