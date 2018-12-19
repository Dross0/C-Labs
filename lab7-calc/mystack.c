#include "mystack.h"

void push(Stack_t *stack, T value){
	if (stack->size == MAX_SIZE)
		exit(STACK_OVERFLOW);
	stack->data[stack->size++] = value;
}

T peek(Stack_t *stack){
	if (stack->size == 0)
		return STACK_UNDERFLOW;
	return stack->data[stack->size-1];
}

T pop(Stack_t *stack){
	if (stack->size == 0)
		return STACK_UNDERFLOW;
	stack->size--;
	return stack->data[stack->size];
}

int is_empty(Stack_t *stack){
	return !stack->size;
}

