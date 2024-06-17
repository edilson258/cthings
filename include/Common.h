#ifndef COMMON_H
#define COMMON_H

/*
 * Typedef: Any_t
 *
 * Is just a wrapper of `void *`
 *
 */
typedef void *Any_t;

/*
 * Typedef: Node
 *
 * A wrapper of data on dynamic growing structures
 *
 */
typedef struct Node {
  void *data;
  struct Node *next;
} Node;

/*
 * Typedef: Node_t
 *
 * Is type alias of `Node *`
 *
 */
typedef Node *Node_t;

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
Node_t Node_new(Any_t data);

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
int *Int(int immediate);

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
char *Str(char *immediate);

/// Boolean Type
typedef enum {
  False = 0,
  True = 1,
} Boolean;

/// Convert a Boolean val to corresponding text
#define Boolean(x) x == False ? "False" : "True"

/*
 * Typedef: Str_t
 *
 * A type alias of 'char *'
 *
 */
typedef char *Str_t;

#endif // COMMON_H
