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


T pop_node(Node_t **head) {
    Node_t *out = *head;
    T value;
    if (*head == 0){
        exit(STACK_UNDERFLOW);
    }
    *head = (*head)->next;
    value = out->value;
    free(out);
    return value;
}

void push_node(Node_t **head, T value) {
    Node_t *tmp = malloc(sizeof(Node_t));
    tmp->next = *head;
    tmp->value = value;
    *head = tmp;
}

T peek_node(const Node_t* head) {
    if (head == 0) {
        exit(STACK_UNDERFLOW);
    }
    return head->value;
}


int is_empty_node(const Node_t *head) {
    int size = 0;
    while (head) {
        size++;
        head = head->next;
    }
    return !size;
}