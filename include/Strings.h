#ifndef STRINGS_H
#define STRINGS_H

#include <pthread.h>
#include <stddef.h>

#include "Common.h"

typedef struct String {
  /* Private field should only be accessed by internal API */
  char *inner;
  size_t length;
  pthread_mutex_t mutx;
} String;

/* Syntax sugar for `String *` */
typedef String *String_t;

/*
 * Function: String(text)
 *
 * Create a stack String instance initialized with the provided text.
 *
 * Parameters:
 *   text - Pointer to the C-style string to initialize the String with.
 *
 * Returns:
 *   The created String instance.
 */
#define String(text)                                                           \
  ({                                                                           \
    String string = {.inner = text};                                           \
    string;                                                                    \
  })

/*
 * Function: String_new(text)
 *
 * Create a new heap-allocated String instance initialized with the provided
 * text.
 *
 * Parameters:
 *   text - Pointer to the C-style string to initialize the String with.
 *
 * Returns:
 *   Pointer to the newly allocated String instance, or NULL if allocation
 * fails.
 *
 */
String_t String_new(Str_t text);

/*
 * Function: String_drop(string)
 *
 * Clean up (free memory) allocated for the String instance.
 *
 * Parameters:
 *   string - Pointer to the String instance to be cleaned up.
 *
 * Returns:
 *
 *   0 on success and -1 on error
 *
 */
int String_drop(String_t string);

/*
 * Function: String_val(string)
 *
 * Returns the raw C-style string (`char *`) stored inside the String.
 *
 * Parameters:
 *   string - Pointer to the String instance.
 *
 * Returns:
 *   Pointer to the C-style string contained within the String.
 *
 */
Str_t String_val(String_t string);

/*
 * Function: String_clone(src)
 *
 * Create and return a deep copy of the source String instance.
 *
 * Parameters:
 *   src - Pointer to the source String instance to be cloned.
 *
 * Returns:
 *   Pointer to the newly created deep copy of the source String instance.
 *
 */
String_t String_clone(String_t src);

/*
 * Function: String_ltrim(string)
 *
 * Remove leading whitespaces (including `\t, \f, \n, ...`) from the String.
 *
 * Parameters:
 *   string - Pointer to the String instance to be left-trimmed.
 *
 * Returns:
 *   Pointer to the left-trimmed String instance.
 *
 */
String_t String_ltrim(String_t string);

/*
 * Function: String_rtrim(string)
 *
 * Remove trailing whitespaces (including `\t, \f, \n, ...`) from the String.
 *
 * Parameters:
 *   string - Pointer to the String instance to be right-trimmed.
 *
 * Returns:
 *   Pointer to the right-trimmed String instance.
 *
 */
String_t String_rtrim(String_t string);

/*
 * Function: String_trim(string)
 *
 * Remove leading and trailing whitespaces (including `\t, \f, \n, ...`) from
 * the String.
 *
 * Parameters:
 *   string - Pointer to the String instance to be trimmed.
 *
 * Returns:
 *   Pointer to the trimmed String instance.
 *
 */
String_t String_trim(String_t string);

/*
 * Function: String_len(string)
 *
 * Returns the length of the C-style string stored inside the String instance.
 *
 * Parameters:
 *   string - Pointer to the String instance.
 *
 * Returns:
 *   Length of the C-style string stored inside the String.
 *
 */
size_t String_len(String_t string);

/*
 * Function: String_join(lhs, rhs)
 *
 * Join two String instances together and return a new String instance
 * containing the concatenated result.
 *
 * Parameters:
 *   lhs - Pointer to the left-hand side String instance.
 *   rhs - Pointer to the right-hand side String instance.
 *
 * Returns:
 *   Pointer to the newly created String instance containing the concatenated
 * result.
 *
 */
String_t String_join(String_t lhs, String_t rhs);

/*
 * Function: String_join_by(lhs, rhs, delimiter)
 *
 * Join two String instances together with a delimiter and return a new String
 * instance containing the concatenated result.
 *
 * Parameters:
 *   lhs - Pointer to the left-hand side String instance.
 *   rhs - Pointer to the right-hand side String instance.
 *   delimiter - Pointer to the delimiter C-style string to be used in between
 * lhs and rhs.
 *
 * Returns:
 *   Pointer to the newly created String instance containing the concatenated
 * result with the delimiter.
 *
 */
String_t String_join_by(String_t lhs, String_t rhs, Str_t delimiter);

#endif // STRINGS_H
