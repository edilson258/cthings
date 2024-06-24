#ifndef STACK_H
#define STACK_H

#include <pthread.h>
#include <stddef.h>

#include "../include/Common.h"

/*
 * Typedef: Stack
 *
 * Represents the stack LIFO data structure
 *
 */
typedef struct {
  Node_t head;
  size_t size;
  size_t max_stack;
  pthread_mutex_t mutx;
} Stack;

/*
 * Typedef: Stack_t
 *
 * It's just a type alias of `Stack *`
 *
 */
typedef Stack *Stack_t;

/*
 * Function: Stack_new(size_t max_stack) -> Stack_t
 *
 * Will create a new instance of Stack_t
 *
 * Parameters:
 *
 * - `size_t max_stack`: The max number of elements a stack can old at once,
 * provide `-1` to have a limite less stack
 *
 * Returns:
 *
 / - `Stack_t`: The new instance of Stack
 *
 */
Stack_t Stack_new(size_t max_stack);

/*
 * Function: Stack_is_empty(Stack_t stack) -> Boolean
 *
 * Will check if the stack is empty or not
 *
 * Parameters:
 *
 * - `Stack_t stack`: The stack to know if its empty
 *
 * Returns:
 *
 * - `True`: if the stack `stack` is empty
 * - `False`: if the stack `stack` is not empty
 *
 */
Boolean Stack_is_empty(Stack_t stack);

/*
 * Function: Stack_is_full(Stack_t stack) -> Boolean
 *
 * Will check if the Stack `stack` is full or not
 *
 * Parameters:
 *
 * - `Stack_t stack`: The stack to check weather is full
 *
 * Returns:
 *
 * - `True`: if the the count of elements in the stack is equal to stack limit
 * - `False`: if the the countog elements in the stack is less than stack limit
 *
 */
Boolean Stack_is_full(Stack_t stack);

/*
 * Function: Stack_push(Stack_t stack, Any_t data)
 *
 * Will put the value `data` on top of stack `stack`, if the stack `stack` has
 * limit and its full the value `data` won't be pushed and a StackOverFlow error
 * will trigged
 *
 * Parameters:
 *  - `Stack_t stack`: The stack to push onto
 *  - `Any_t data`: The value to be pushed
 *
 */
int Stack_push(Stack_t stack, Any_t data);

/*
 * Function: Stack_pop(Stack_t stack) -> Any_t
 *
 * Will remove and return the value on top of the stack `stack`, if the stack is
 * empty a StackUnderFlow will be trigged and the program will exit
 * unseccessfuly
 *
 * Parameters:
 *
 * - `Stack_t stack`: The stack to pop from it
 *
 * Returns:
 *
 * - will return the value on top of the stack
 *
 */
Any_t Stack_pop(Stack_t stack);

#endif
