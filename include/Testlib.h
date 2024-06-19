#ifndef TESTER_H
#define TESTER_H

#include <stddef.h>

#include "Common.h"

/*
 * Typedef: TEST
 *
 * Represents a test result
 *
 */
typedef enum {
  PASS = 0,
  FAIL = 1,
} TEST;

/*
 * Typedef: TEST_fn
 *
 * The signature of a test function
 *
 */
typedef TEST (*TEST_fn)(void);

/*
 * Typedef: Tester
 *
 * A Test context
 *
 */
typedef struct {
  Str_t title;
  size_t count;
  TEST_fn tests[5];
} TestSuite;

/*
 * Typedef: TestSuite
 *
 * A type alias for `Tester *`
 *
 */
typedef TestSuite *TestSuite_t;

/*
 * Function: TestSuite_new(Str_t title) -> TestSuite_t
 *
 * Will create a new suite of tests
 *
 * Parameters:
 *
 * - Str_t title: The title of the suite tests
 *
 * Returns:
 *
 * - TestSuite_t: a test suite
 *
 */
TestSuite_t TestSuite_new(Str_t title);

/*
 * Function: TestSuite_add(TestSuite_t ts, TEST_fn fn)
 *
 * Will append the test function `fn` to the suite of tests  `ts`
 *
 * Parameters:
 *
 * - TestSuite ts: The suite of test
 * - TEST_fn fn: The test to be added in the suite
 *
 */
void TestSuite_add(TestSuite_t ts, TEST_fn fn);

/*
 * Function: Tester_run(TestSuite ts)
 *
 * Will run all the tests inside of the suite of tests `ts` and then print the
 * summary
 *
 * Parameters:
 *
 * - TestSuite_t ts: The suite of tests
 *
 */
size_t TestSuite_run(TestSuite_t ts);

/*
 * INTERNAL API
 *
 */

TEST __assert_eq_int__(int expected, int provided, char *file, char *fn,
                       int line);
TEST __assert_eq_str__(Str_t expected, Str_t provided, Str_t file, Str_t fn,
                       int line);
TEST __assert_eq_struct__(Any_t expected, Any_t provided, size_t struct_size,
                          char *file, char *fn, int line);
TEST __assert_true__(Boolean val, char *file, char *fn, int line);
TEST __assert_null_pointer__(Any_t nullp, char *file, char *fn, int line);

/*
 *
 * TESTING INTERFACE
 *   => List of macros used to do assertion and expects
 *
 */

/// Checks if the provided ints are equal
#define ASSERT_EQ_INT(expected, provided)                                      \
  return __assert_eq_int__(expected, provided, (char *)__FILE__,               \
                           (char *)__FUNCTION__, __LINE__)

/// Checks if the provided strs are equal
#define ASSERT_EQ_STR(expected, provided)                                      \
  return __assert_eq_str__(expected, provided, (char *)__FILE__,               \
                           (char *)__FUNCTION__, __LINE__)

/// Checks if the provided structs are equal
#define ASSERT_EQ_STRUCT(expected, provided, struct_size)                      \
  return __assert_eq_struct__(expected, provided, struct_size,                 \
                              (char *)__FILE__, (char *)__FUNCTION__,          \
                              __LINE__)

/// Expects val to be a Boolean `True`
#define ASSERT_TRUE(val)                                                       \
  return __assert_true__(val, (char *)__FILE__, (char *)__FUNCTION__, __LINE__)

/// Expects val to be a `NULL`
#define ASSERT_NULL_POINTER(nullp)                                             \
  return __assert_null_pointer__(nullp, (char *)__FILE__,                      \
                                 (char *)__FUNCTION__, __LINE__)

#endif // TESTER_H
