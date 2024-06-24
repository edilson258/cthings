#include <stdio.h>

#include "../include/Logger.h"

int main(void) {
  // Log to stdout
  Log(stdout, INFO, "User %s is online", "Edilson");
  Log(stdout, WARN, "Remaining %s of memory", "49762KB");
  Log(stdout, ERROR, "Couldn't connect to the database");

  // Log to a specific file
  FILE *file = fopen("LOGS", "a");
  Log(file, INFO, "User %s is online", "Edilson");
  Log(file, WARN, "Remaining %s of memory", "49762KB");
  Log(file, ERROR, "Couldn't connect to the database");
  return 0;
}
