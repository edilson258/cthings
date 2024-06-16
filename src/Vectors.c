#include <stdlib.h>

#include "../include/Vector.h"

Vector_t Vector_new() {
  Vector_t vec = malloc(sizeof(Vector));
  vec->size = 0;
  vec->head = NULL;
  return vec;
}

/*
 * Function: Vector_isempty(Vector_t vec) -> int
 *
 * Checks if Vector `vec` is empty
 *
 * Parameters:
 *
 * - Vector_t vec: The vector to be checked if is empty
 *
 * Returns:
 *
 * - 1: when is empty
 * - 0: when is not empty
 *
 */
int Vector_isempty(Vector_t vec) { return vec->size == 0; }

/*
 * Function: Vector_push(Vector_t vec, Any_t elem)
 *
 * Will append `elem` to the end of the Vector `vec`
 *
 * `Note`: Vector is implemented as linked list. So, this operation is O(n)
 *
 * Parameters:
 *
 * - Vector_t vec: The vector to push on
 * - Any_t elem: The element to pushed
 *
 */
void Vector_push(Vector_t vec, Any_t elem) {
  if (Vector_isempty(vec)) {
    vec->head = Node_new(elem);
  } else [[clang::likely]] {
    Node_t tmp = vec->head;
    /*
     * O(n)
     *
     */
    while (tmp->next) {
      tmp = tmp->next;
    }
    tmp->next = Node_new(elem);
  }
  vec->size++;
}

/*
 * Typedef: MapFn
 *
 * Is a function signature expected by the `Vector_map` function
 *
 * `Note`: This function must clone the underlyning data
 *
 */
typedef Any_t (*MapFn)(Any_t vec_item);

/*
 * Typedef: ReduceFn
 *
 * Is a function signature expected by the `Vector_reduce` function
 *
 */
typedef void (*ReduceFn)(Any_t vec_item, Any_t acc);

/*
 * Typedef: FilterFn
 *
 * Is a function signature expected by the `Vector_filter` function
 *
 * `Note`: This function must clone the elements
 *
 */
typedef int (*FilterFn)(Any_t vec_item);

/*
 * Function: Vector_map(Vector_t vec, MapFn fn) -> Vector_t
 *
 * Will map each elem in the Vector `vec` to Map Function `fn` and then return
 * the resulting Vector
 *
 * `Note`: The MapFn `fn` must clone the elements
 *
 * Parameters:
 *
 * - Vector_t vec: The original vector
 * - MapFn fn: The map function
 *
 * Returns:
 *
 * - Vector_t: A new vector with mapped elements
 *
 */
Vector_t Vector_map(Vector_t vec, MapFn fn) {
  Vector_t new_vec = Vector_new();
  Node_t tmp = vec->head;
  while (tmp) {
    Vector_push(new_vec, fn(tmp->data));
    tmp = tmp->next;
  }
  return new_vec;
}

/*
 * Function: Vector_reduce(Vector_t vec, ReduceFn fn, Any_t acc) -> acc
 *
 * Will map each element of the Vector `vec` to the Reduce Function `fn` that
 * way reducing the elements into the Accumulator `acc`
 *
 * Parameters:
 *
 * - Vector_t vec: Vector of elements to be reduced
 * - ReduceFn fn: The reduce function
 * - Any_t acc: The Accumulator
 *
 * Returns:
 *
 * - Any_t acc: The accumulated result
 *
 */
void Vector_reduce(Vector_t vec, ReduceFn fn, Any_t acc) {
  Node_t tmp = vec->head;
  while (tmp) {
    fn(tmp->data, acc);
    tmp = tmp->next;
  }
}

/*
 * Function: Vector_filter(Vector_t vec, FilterFn fn) -> Vector_t
 *
 * Will filter the elements in Vector `vec` according to the Filter Function
 * `fn`
 *
 * Parameters:
 *
 * - Vector_t vec: A vector to be filtered
 * - FilterFn fn: A predicate function
 *
 * Returns:
 *
 * - Vector_t vec: A vector with filtered elements
 *
 */
Vector_t Vector_filter(Vector_t vec, FilterFn fn) {
  Vector_t filter_vec = Vector_new();

  Node_t tmp = vec->head;
  while (tmp) {
    if (fn(tmp->data)) {
      Vector_push(filter_vec, tmp->data);
    }
    tmp = tmp->next;
  }

  return filter_vec;
}
