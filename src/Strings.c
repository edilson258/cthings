#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Strings.h"

String_t String_new(RawStr_t text) {
  unsigned long text_len = strlen(text);
  String_t string = malloc(sizeof(String));
  string->inner = malloc(sizeof(char) * (text_len + 1));
  memcpy(string->inner, text, text_len);
  string->inner[text_len] = 0;
  return string;
}

RawStr_t String_val(String_t string) { return string->inner; }

String_t String_clone(String_t src) { return String_new(src->inner); }

void String_drop(String_t string) {
  free(string->inner);
  free(string);
}

String_t String_ltrim(String_t string) {
  unsigned long cursor = 0;
  unsigned long length = strlen(string->inner);
  while (cursor < length && isspace(string->inner[cursor])) {
    cursor++;
  }
  String_t new_sting = String_new(string->inner + cursor);
  String_drop(string);
  return new_sting;
}

String_t String_rtrim(String_t string) {
  unsigned long cursor = strlen(string->inner);
  while (cursor >= 0 && isspace(string->inner[cursor - 1])) {
    cursor--;
  }
  string->inner[cursor] = '\0';
  String_t new_sting = String_new(string->inner);
  String_drop(string);
  return new_sting;
}

String_t String_trim(String_t string) {
  return String_rtrim(String_ltrim(string));
}

unsigned long String_len(String_t string) { return strlen(string->inner); }

String_t String_join(String_t lhs, String_t rhs) {
  unsigned long lhs_len = String_len(lhs);
  unsigned long rhs_len = String_len(rhs);
  char temp_str[lhs_len + rhs_len + 1];
  memcpy(temp_str, lhs->inner, lhs_len);
  memcpy(temp_str + lhs_len, rhs->inner, rhs_len);
  temp_str[lhs_len + rhs_len] = 0;
  return String_new(temp_str);
}

String_t String_join_by(String_t lhs, String_t rhs, RawStr_t delimiter) {
  unsigned long lhs_len = String_len(lhs);
  unsigned long rhs_len = String_len(rhs);
  unsigned long delimiter_len = strlen(delimiter);
  char temp_str[lhs_len + rhs_len + delimiter_len + 1];
  memcpy(temp_str, lhs->inner, lhs_len);
  memcpy(temp_str + lhs_len, delimiter, delimiter_len);
  memcpy(temp_str + (lhs_len + delimiter_len), rhs->inner, rhs_len);
  temp_str[lhs_len + rhs_len + delimiter_len] = 0;
  return String_new(temp_str);
}
