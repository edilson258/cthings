#ifndef VECTORS_H
#define VECTORS_H

#include <stddef.h>

#include "Common.h"

/*
 * Typedef: Vector
 *
 * Represents a 1-D Vector
 *
 * `Note`: Every vector operations don't make any kind of memory allocation
 * or deallocation of the elements data. Thus, the developer must take care of
 * that to avoid corruptions of the stored element's data
 *
 */
typedef struct {
  // Head of the linked list
  Node_t head;

  // number of elements
  size_t size;
} Vector;

/*
 * Typedef: Vector_t
 *
 * Is just a type alias for `Vector *`
 *
 */
typedef Vector *Vector_t;

/*
 * Function: Vector_new() -> Vector_t
 *
 * Will create a new `Vector` instance on the heap
 *
 * Returns:
 *
 * -`Vector_t` a pointer to the Vector
 *
 */
Vector_t Vector_new();

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
int Vector_isempty(Vector_t vec);

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
void Vector_push(Vector_t vec, Any_t elem);

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
Vector_t Vector_map(Vector_t vec, MapFn fn);

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
void Vector_reduce(Vector_t vec, ReduceFn fn, Any_t acc);

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
Vector_t Vector_filter(Vector_t vec, FilterFn fn);

/*
 * Function: Vector_len(Vector_t vec) -> size_t
 *
 * Will return the length of the Vector `vec`
 *
 * Parameters:
 *
 * - Vector_t vec: The vector to get its length
 *
 * Returns:
 *
 * - size_t: the length of the vector `vec`
 *
 */
size_t Vector_len(Vector_t vec);

/*
 * Function: Vector_at(Vector_t vec, size_t index) -> Any_t
 *
 * Will return the element in the index `index`, in case of out of bound `NULL`
 * will be returned
 *
 * `Note`: The element returned still pointed by the vector, the developer
 * should clone it before any modification to avoid data corruptions
 *
 * Parameters:
 *
 * - Vector_t vec: The Vector that holds the element to be indexed
 * - size_t index: The positio of the element in the vector
 *
 * Returns:
 *
 * - 'Any_t': the element or NULL in case of out of bound
 *
 */
Any_t Vector_at(Vector_t vec, size_t index);

#endif // VECTORS_H
