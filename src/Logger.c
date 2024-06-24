#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/Common.h"
#include "../include/Logger.h"

Str_t datetime_str() {
  time_t current_time;
  time(&current_time);
  struct tm *local_time = localtime(&current_time);
  char *time_str = malloc(sizeof(char) * 20);
  strftime(time_str, 19, "%Y-%m-%d %H:%M:%S", local_time);
  return time_str;
}

void Log(FILE *file, LogLevel level, Str_t message, ...) {
  fprintf(file, "[%s] %s ", datetime_str(), LogLevel(level));
  va_list args;
  va_start(args, message);
  vfprintf(file, message, args);
  va_end(args);
  fprintf(file, "\n");
}
