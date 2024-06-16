#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Common.h"

Node_t Node_new(void *data) {
  Node_t node = (Node_t)malloc(sizeof(Node));
  if (node == NULL) {
    fprintf(stderr, "[Error]: Couldn't allocate space for a node: %s\n",
            strerror(errno));
    return NULL;
  }
  node->data = data;
  node->next = NULL;
  return node;
}

int *Int(int immediate) {
  int *out = malloc(sizeof(int));
  memcpy(out, &immediate, sizeof(int));
  return out;
}

char *Str(char *immediate) {
  char *out = malloc(sizeof(char) * strlen(immediate) + 1);
  memcpy(out, immediate, strlen(immediate));
  out[strlen(immediate)] = 0;
  return out;
}
