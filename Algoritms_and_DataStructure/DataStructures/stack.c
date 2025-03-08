#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct node_t{
	int data;
	struct node_t* next;
}	Node;


typedef struct stack_t{
	Node* top;
} Stack;


Node* create_node(int data)
{
	Node* node = calloc(1, sizeof(Node));
	if (node == NULL) return NULL;

	node->data = data;
	node->next = NULL;

	return node;
}


Stack* create_stack()
{
	Stack* stack = calloc(1, sizeof(Stack));
	if (stack == NULL) return NULL;

	stack->top = NULL;
	return stack;
}

void peek(Stack* stack)
{
	if (stack == NULL){
		fprintf(stderr, "Stack is not initialized!\n");
		return;
	}
	if (stack->top == NULL){
		printf("Stack has no elements!\n");
		return;
	}

	printf("Top_data = %d\n", stack->top->data);

}
void push(Stack* stack, int data)
{
	Node* node = create_node(data);
	if (node == NULL) return; 
	
	node->next = stack->top;
	stack->top = node;

}

int pop(Stack* stack)
{
	if (stack == NULL || stack->top == NULL) return INT_MIN;

	int data;
	Node* node = stack->top;
	stack->top = stack->top->next;
	
	data = node->data;
	free(node);
	
	return data;
}

void clear_stack(Stack* stack)
{
	if (stack == NULL) return;

	while (stack->top != NULL){
		pop(stack);
	}
}


void show_stack(Stack* stack)
{	
	if (stack == NULL || stack->top == NULL){
		printf("Stack is empty!\n");
		return ;
	}

	Node* tmp = stack->top;
	while (tmp != NULL){
		printf("%d ", tmp->data);
		tmp = tmp->next;
	}
	printf("\n");

}

void stack_reverse(Stack* stack)
{
	if (stack == NULL || stack->top == NULL || stack->top->next == NULL){
		fprintf(stderr, "Nothing to reverse!\n");
		return ;
	}

	Node* fst = NULL;
	Node* snd = stack->top;

	while (snd != NULL){
		Node* tmp = snd->next;
		snd->next = fst;
		fst = snd;
		snd = tmp;
	}
	stack->top = fst;
	

}


int main(void)
{
	Stack* st = create_stack();

	push(st, 4);
	push(st, 3);
	push(st, 111);
	peek(st);

	clear_stack(st);

	show_stack(st);
	stack_reverse(st);
	show_stack(st);
	return 0;
}


