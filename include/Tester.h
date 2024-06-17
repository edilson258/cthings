#ifndef TESTER_H
#define TESTER_H

#include <stddef.h>

#include "../include/Common.h"

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
  size_t count;
  TEST_fn tests[5];
} Tester;

/*
 * Typedef: Tester_t
 *
 * A type alias for `Tester *`
 *
 */
typedef Tester *Tester_t;

/*
 * Function: Tester_new() -> Tester_t
 *
 * Will create a Test context
 *
 * Returns:
 *
 * - Tester_t: an instance of the Test context
 *
 */
Tester_t Tester_new();

/*
 * Function: Tester_add(Tester_t t, TEST_fn fn)
 *
 * Will append a test TEST_fn `fn` to the Test context `t`
 *
 * Parameters:
 *
 * - Tester_t t: The Test context
 * - TEST_fn fn: The test to be added in the context
 *
 */
void Tester_add(Tester_t t, TEST_fn fn);

/*
 * Function: Tester_run(Tester_t t)
 *
 * Will run all the tests inside of the Test context `t` and then print the
 * summary
 *
 * Parameters:
 *
 * - Tester_t t: The Test context
 *
 */
size_t Tester_run(Tester_t t);

/*
 * INTERNAL API
 *
 */

TEST __assert_equals_int__(int expected, int provided, char *file, char *fn,
                           int line);
TEST __assert_equals_struct__(Any_t expected, Any_t provided,
                              size_t struct_size, char *file, char *fn,
                              int line);
TEST __assert_true__(Boolean val, char *file, char *fn, int line);

/*
 *
 * TESTING INTERFACE
 *   => List of macros used to do assertion and expects
 *
 */

/// Checks if the provided ints are equal
#define ASSERT_EQUALS_INT(expected, provided)                                  \
  return __assert_equals_int__(expected, provided, (char *)__FILE__,           \
                               (char *)__FUNCTION__, __LINE__)

/// Checks if the provided structs are equal
#define ASSERT_EQUALS_STRUCT(expected, provided, struct_size)                  \
  return __assert_equals_struct__(expected, provided, struct_size,             \
                                  (char *)__FILE__, (char *)__FUNCTION__,      \
                                  __LINE__)

/// Expects val to be a Boolean `True`
#define ASSERT_TRUE(val)                                                       \
  return __assert_true__(val, (char *)__FILE__, (char *)__FUNCTION__, __LINE__)

#endif // TESTER_H
