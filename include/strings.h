#ifndef STRINGS_H
#define STRINGS_H

typedef struct String {
  /// private field should only accessed by internal API
  char *inner;
} String;

/// A Syntax sugar for `String *`
typedef String *String_t;
/// A Syntax sugar for `char *`
typedef char *RawStr_t;

/// Create a stack String instance
#define String(text)                                                           \
  ({                                                                           \
    String string = {.inner = text};                                           \
    string;                                                                    \
  })

/// Will create a new instance of string on the heap
String_t String_new(RawStr_t text);
/// Will clean up the string
void String_drop(String_t string);
/// Returns the raw value `char *`
RawStr_t String_val(String_t string);
/// Returns a deep copy of the original string.
String_t String_clone(String_t src);
/// cuts off all the whitespaces including `\t,\f,\n,...` in the beggining of
/// the string
String_t String_ltrim(String_t string);
/// cuts off all the trailing whitespaces including `\t,\f,\n,...`
String_t String_rtrim(String_t string);
/// cuts off all the whitespaces including `\t,\f,\n,...` in the beggining and
/// in the end
String_t String_trim(String_t string);
/// Returns the `length` of the wrapped `char *` string
unsigned long String_len(String_t string);
/// Joins two strings together and returns the full sting without modifying the
/// original strings
String_t String_join(String_t lhs, String_t rhs);
/// Same as `String_join(x,y)` but with a `delimiter`
String_t String_join_by(String_t lhs, String_t rhs, RawStr_t delimiter);
#endif
