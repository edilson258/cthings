#include <ctype.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Strings.h"

String_t String_new(Str_t text) {
  size_t text_len = strlen(text);
  String_t string = malloc(sizeof(String));
  string->inner = malloc(sizeof(char) * (text_len + 1));
  memcpy(string->inner, text, text_len);
  string->inner[text_len] = 0;
  string->length = strlen(string->inner);
  pthread_mutex_init(&string->mutx, NULL);
  return string;
}

Str_t String_val(String_t string) {
  pthread_mutex_lock(&string->mutx);
  Str_t inner = string->inner;
  pthread_mutex_unlock(&string->mutx);
  return inner;
}

String_t String_clone(String_t src) {
  pthread_mutex_lock(&src->mutx);
  String_t cloned = String_new(src->inner);
  pthread_mutex_unlock(&src->mutx);
  return cloned;
}

int String_drop(String_t string) {
  free(string->inner);
  // might crash
  pthread_mutex_destroy(&string->mutx);
  free(string);
  return 0;
}

String_t String_ltrim(String_t string) {
  pthread_mutex_lock(&string->mutx);
  size_t cursor = 0;
  while (cursor < string->length && isspace(string->inner[cursor])) {
    cursor++;
  }
  String_t new_sting = String_new(string->inner + cursor);
  String_drop(string);
  pthread_mutex_unlock(&string->mutx);
  return new_sting;
}

String_t String_rtrim(String_t string) {
  pthread_mutex_lock(&string->mutx);
  size_t cursor = string->length;
  while (cursor >= 0 && isspace(string->inner[cursor - 1])) {
    cursor--;
  }
  string->inner[cursor] = '\0';
  String_t new_sting = String_new(string->inner);
  String_drop(string);
  pthread_mutex_unlock(&string->mutx);
  return new_sting;
}

String_t String_trim(String_t string) {
  return String_rtrim(String_ltrim(string));
}

size_t String_len(String_t string) {
  pthread_mutex_lock(&string->mutx);
  size_t len = string->length;
  pthread_mutex_unlock(&string->mutx);
  return len;
}

String_t String_join(String_t lhs, String_t rhs) {
  pthread_mutex_lock(&lhs->mutx);
  pthread_mutex_lock(&rhs->mutx);
  size_t lhs_len = lhs->length;
  size_t rhs_len = rhs->length;
  char temp_str[lhs_len + rhs_len + 1];
  memcpy(temp_str, lhs->inner, lhs_len);
  memcpy(temp_str + lhs_len, rhs->inner, rhs_len);
  temp_str[lhs_len + rhs_len] = 0;
  pthread_mutex_unlock(&lhs->mutx);
  pthread_mutex_unlock(&rhs->mutx);
  return String_new(temp_str);
}

String_t String_join_by(String_t lhs, String_t rhs, Str_t delimiter) {
  pthread_mutex_lock(&lhs->mutx);
  pthread_mutex_lock(&rhs->mutx);
  size_t lhs_len = lhs->length;
  size_t rhs_len = rhs->length;
  size_t delimiter_len = strlen(delimiter);
  char temp_str[lhs_len + rhs_len + delimiter_len + 1];
  memcpy(temp_str, lhs->inner, lhs_len);
  memcpy(temp_str + lhs_len, delimiter, delimiter_len);
  memcpy(temp_str + (lhs_len + delimiter_len), rhs->inner, rhs_len);
  temp_str[lhs_len + rhs_len + delimiter_len] = 0;
  pthread_mutex_unlock(&lhs->mutx);
  pthread_mutex_unlock(&rhs->mutx);
  return String_new(temp_str);
}
