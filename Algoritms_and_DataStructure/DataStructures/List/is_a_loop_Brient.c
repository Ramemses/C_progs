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

int is_second(int cnt)
{
	while (cnt % 2 == 0) cnt /= 2;
	
	if (cnt == 1) return 1;
	return 0;
}

int is_a_loop(Node* top)
{
	int cnt = 1;
	Node* ptr1 = top;
	Node* ptr2 = top;
	
	while(ptr1 != NULL && ptr2 != NULL){
		if (is_second(cnt))
			ptr1 = ptr2;
		ptr2 = ptr2->next;
		cnt++;	

		if (ptr1 == ptr2)
			return 1;
	}

	return 0;
}





int main(void)
{
	Node *top = create_list();

	top = push_front(top, 4);	
	top = push_front(top, 2);	
	top = push_front(top, 1);	
	top = push_front(top, 0);	
	top = push_front(top, 3);	
	top = push_front(top, 5);	


	int res = is_a_loop(top);
	printf("%d\n", res);

	return 0;
}


