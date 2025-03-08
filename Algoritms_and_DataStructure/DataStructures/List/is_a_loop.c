#include <stdio.h>
#include <stdlib.h>


typedef struct list_t{
	int data;
	struct list_t* next;
} Node;

Node* create_list(){

	Node* node = malloc(sizeof(Node));
	if (node == NULL) return NULL;

	return node;	
}


Node* push_front(Node* top, int data)
{
	Node* node = malloc(sizeof(Node));
	if (node == NULL) return NULL;
	
	node->next = top;
	node->data = data;

	return node;
}

Node* pop_front(Node* top)
{
	if (top == NULL) return NULL;
	
	Node* node = top;
	top = top->next;	
	free(node);
	
	return top;
}

void print_list(Node* top)
{
	Node* node = top;
	while (node != NULL){
		printf("%d ", node->data);
		node = node->next;
	}
	printf("\n");
}

void free_list(Node* top)
{
	while(top != NULL)
		top = pop_front(top);

}

int is_a_loop(Node* top)
{
	Node* ptr1 = top;
	Node* ptr2 = top;
	
	while(ptr2 != NULL){
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
		if (ptr2 == NULL) return 0;
			
		ptr2 = ptr2->next;
		if (ptr1 == ptr2) return 1;
	}

	return 0;
}



int main(void)
{
	Node* lst = create_list();
	
	lst = push_front(lst, 5);
	lst = push_front(lst, 5);
	lst = push_front(lst, 5);
	lst = push_front(lst, 2);
	lst = push_front(lst, 0);
	lst = push_front(lst, 2);
	lst = push_front(lst, 0);
	lst = push_front(lst, 2);
	lst = push_front(lst, 0);


	int res = is_a_loop(lst);
	printf("%d\n", res);

	free_list(lst);
}
