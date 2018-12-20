#define STACK_UNDERFLOW -1
#define STACK_OVERFLOW -2
#define MAX_SIZE 1000


typedef int T;

typedef struct Node_tag {
    T value;
    struct Node_tag * next;
} Node_t;




typedef struct Stack_tag{
	T data[MAX_SIZE];
	int size;
} Stack_t;

void push(Stack_t *stack, T value);

T peek(Stack_t *stack);

T pop(Stack_t *stack);

int is_empty(Stack_t *stack);

T pop_node(Node_t **head);

void push_node(Node_t **head, T value);

T peek_node(const Node_t* head);

int is_empty_node(const Node_t *head);
