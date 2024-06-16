#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Common.h"

/*
 * Function: Node_new(Any_t data) -> Node_t
 *
 * Will returns the `data` and returns it wrapped in a `Node_t`
 *
 * Parameters:
 *
 * - Any_t data: a data to be wrapped
 *
 * Returns:
 *
 * - Node_t: a node that wraps the `data`
 *
 */
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

/*
 * Function: Int(int immediate) -> int*
 *
 * Will allocate the integer value `immediate` on the heap and return the
 * pointer
 *
 * Parameters:
 *
 * - int immediate: an immediate int value
 *
 * Returns:
 *
 * - int *: a pointer to the heap allocated integer `immediate`
 *
 */
int *Int(int immediate) {
  int *out = malloc(sizeof(int));
  memcpy(out, &immediate, sizeof(int));
  return out;
}

/*
 * Function: Str(char* immediate) -> char*
 *
 * Will allocate the string value `immediate` on the heap and return the
 * pointer
 *
 * Parameters:
 *
 * - char* immediate: an immediate string value
 *
 * Returns:
 *
 * - char *: a pointer to the heap allocated string `immediate`
 *
 */
char *Str(char *immediate) {
  char *out = malloc(sizeof(char) * strlen(immediate) + 1);
  memcpy(out, immediate, strlen(immediate));
  out[strlen(immediate)] = 0;
  return out;
}
