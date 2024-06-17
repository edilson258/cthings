#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Tester.h"

TestSuite_t TestSuite_new(Str_t title) {
  TestSuite_t ts = malloc(sizeof(TestSuite));
  ts->count = 0;
  ts->title = title;
  return ts;
}

void TestSuite_add(TestSuite_t ts, TEST_fn fn) {
  // append test
  ts->tests[ts->count++] = fn;
}

size_t TestSuite_run(TestSuite_t ts) {
  size_t oks = 0;
  size_t fails = 0;

  printf("\nRunning suite: %s\n\n", ts->title);

  for (int i = 0; i < ts->count; ++i) {
    if (ts->tests[i]() == PASS)
      oks++;
    else
      fails++;
  }

  printf("\nSummary for suite: %s\n", ts->title);
  printf("    [PASSED] %zu\n", oks);
  printf("    [FaILED] %zu\n", fails);

  return fails;
}

/*
 * INTERNAL API
 *
 */

TEST __assert_eq_int__(int expected, int provided, char *file, char *fn,
                       int line) {
  if (expected == provided) {
    printf("[\033[32m PASS \033[0m] %s:%d %s\n", file, line, fn);
    return PASS;
  }

  fprintf(stderr,
          "[\033[31m FAIL \033[0m] %s:%d: %s EXPECTED: %d PROVIDED: %d\n", file,
          line, fn, expected, provided);
  return FAIL;
}

TEST __assert_eq_struct__(Any_t expected, Any_t provided, size_t struct_size,
                          char *file, char *fn, int line) {
  if (0 == memcmp(expected, provided, struct_size)) {
    printf("[\033[32m PASS \033[0m] %s:%d %s\n", file, line, fn);
    return PASS;
  }
  fprintf(stderr, "[\033[31m FAIL \033[0m] %s:%d: %s: structs are not equal\n",
          file, line, fn);
  return FAIL;
}

TEST __assert_true__(Boolean val, char *file, char *fn, int line) {
  if (val != False) {
    printf("[\033[32m PASS \033[0m] %s:%d %s\n", file, line, fn);
    return PASS;
  }

  fprintf(stderr, "[\033[31m FAIL \033[0m] %s:%d: %s: expects True\n", file,
          line, fn);
  return FAIL;
}
