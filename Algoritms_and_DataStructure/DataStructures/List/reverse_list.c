#include <stdio.h>
#include <stdlib.h> 


typedef struct node_t{
	int data;
	struct node_t* next;
} Node;


Node* create_list()
{
	Node* top = NULL;
	return top;
}

Node* push_front(Node* top, int data)
{
	Node* node = calloc(1, sizeof(Node));
	if (node == NULL) return top;
	
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

void free_list(Node* top)
{
	while(top != NULL)
		top = pop_front(top);	
}



void print_list(Node* top)
{
	if (top == NULL){
		printf("list is empty!\n");
		return;
	}
	Node* node = top;
	while(node != NULL){
		printf("%d ", node->data);
		node = node->next;
	}
	printf("\n");
}

Node* reverse_list_rec(Node* top)
{
	if (top == NULL) return NULL;
	if (top->next == NULL) return top;
	
	Node* node = reverse_list_rec(top->next);
	top->next->next = top;
	top->next = NULL;

	return node;
}

Node* reverse_list_iter(Node* top)
{
	if (top == NULL) return NULL;
	if (top->next == NULL) return top;	

	Node* ptr1 = top;
	Node* ptr2 = top->next;
	top->next = NULL;


	while (ptr2 != NULL){
		Node* tmp = ptr2->next;
		ptr2->next = ptr1;
		ptr1 = ptr2;
		ptr2 = tmp;	
	}

	return ptr1;
}




int main(void)
{
	Node* lst = create_list();

	lst = push_front(lst, 4);
	lst = push_front(lst, 3);
	lst = push_front(lst, 2);
	lst = push_front(lst, 1);
	print_list(lst);
	
	lst = reverse_list_rec(lst);
	print_list(lst);
	
	lst = reverse_list_iter(lst);
	print_list(lst);

	free_list(lst);
}
