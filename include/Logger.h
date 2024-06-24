#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

#include "Common.h"

typedef enum {
  INFO = 0,
  WARN = 1,
  ERROR = 2,
} LogLevel;

/// Will convert a LogLevel enum entry to its respective string representation
#define LogLevel(level)                                                        \
  (level == INFO)    ? "\033[0;32mINFO\033[0m"                                 \
  : (level == WARN)  ? "\033[0;33mWARNING\033[0m"                              \
  : (level == ERROR) ? "\033[0;31mERROR\033[0m"                                \
                     : "UNKNOWN LOG LEVEL"
/**
 * Function: Log(FILE *file, LogLevel level, Str_t message, ...)
 *
 * will log a message to the specified file
 *
 */
void Log(FILE *file, LogLevel level, Str_t message, ...);

#endif // LOGGER_H
