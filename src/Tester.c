#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Tester.h"

Tester_t Tester_new() {
  Tester_t t = malloc(sizeof(Tester));
  t->count = 0;
  return t;
}

void Tester_add(Tester_t t, TEST_fn fn) {
  // append test
  t->tests[t->count++] = fn;
}

size_t Tester_run(Tester_t t) {
  size_t oks = 0;
  size_t fails = 0;

  for (int i = 0; i < t->count; ++i) {
    if (t->tests[i]() == PASS)
      oks++;
    else
      fails++;
  }

  printf("\nSummary:\n");
  printf("    [PASSED] %zu\n", oks);
  printf("    [FaILED] %zu\n", fails);

  return fails;
}

/*
 *
 * INTERNAL API
 *
 */

TEST __assert_equals_int__(int expected, int provided, char *file, char *fn,
                           int line) {
  if (expected == provided) {
    printf("[PASS] %s:%d %s\n", file, line, fn);
    return PASS;
  }

  fprintf(stderr, "[FAIL] %s:%d: %s EXPECTED: %d PROVIDED: %d\n", file, line,
          fn, expected, provided);
  return FAIL;
}

TEST __assert_equals_struct__(Any_t expected, Any_t provided,
                              size_t struct_size, char *file, char *fn,
                              int line) {
  if (0 == memcmp(expected, provided, struct_size)) {
    printf("[PASS] %s:%d %s\n", file, line, fn);
    return PASS;
  }
  fprintf(stderr, "[FAIL] %s:%d: %s: structs are not equal\n", file, line, fn);
  return FAIL;
}

TEST __assert_true__(Boolean val, char *file, char *fn, int line) {
  if (val != False) {
    printf("[PASS] %s:%d %s\n", file, line, fn);
    return PASS;
  }

  fprintf(stderr, "[FAIL] %s:%d: %s: False is not True\n", file, line, fn);
  return FAIL;
}
