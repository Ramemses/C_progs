#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//---------------------------- DATA STRUCTURES ---------------------------
typedef struct node_t{
	int data;
	struct node_t* next;
}	StackNode;


typedef struct stack_t{
	StackNode* top;
} Stack;
//------------------------------------------------------------------


//--------------------- CONSTRUCTORS---------------------------------------
StackNode* create_node(int data)
{
	StackNode* node = calloc(1, sizeof(StackNode));
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
//------------------------------------------------------------------------


//-----------------------------------------METHODS-------------------------

//Sow top of stack without delete
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
	StackNode* node = create_node(data);
	if (node == NULL) return; 
	
	node->next = stack->top;
	stack->top = node;

}

int pop(Stack* stack)
{
	if (stack == NULL || stack->top == NULL) return INT_MIN;

	int data;
	StackNode* node = stack->top;
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

//Just prints elements or stack or message of empty stack
void show_stack(Stack* stack)
{	
	if (stack == NULL || stack->top == NULL){
		printf("Stack is empty!\n");
		return ;
	}

	StackNode* tmp = stack->top;
	while (tmp != NULL){
		printf("%d ", tmp->data);
		tmp = tmp->next;
	}
	printf("\n");

}

//Reverses the order of elements in stack
void stack_reverse(Stack* stack)
{
	if (stack == NULL || stack->top == NULL || stack->top->next == NULL){
		fprintf(stderr, "Nothing to reverse!\n");
		return ;
	}

	StackNode* fst = NULL;
	StackNode* snd = stack->top;

	while (snd != NULL){ //In each interation we reverse the pointer from second to first element
		StackNode* tmp = snd->next;
		snd->next = fst;
		fst = snd;
		snd = tmp;
	}
	stack->top = fst;
}

//---------------------------------------------------------------------------------


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


