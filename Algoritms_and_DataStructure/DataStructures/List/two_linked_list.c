#include <stdio.h>
#include <stdlib.h>


typedef struct node_t{
	int data;
	struct node_t* next;
	struct node_t* prev;	
} Node;

typedef struct list_t{
	Node* head;
	Node* tail;
} TwoLinkedList;



Node* create_node(int data)
{
	Node* node = calloc(1, sizeof(Node));
	if (node == NULL) return NULL;

	node->data = data;
	node->next = node->prev = NULL;

	return node;
}

TwoLinkedList* create_list()
{
	TwoLinkedList* t_list = calloc(1, sizeof(TwoLinkedList));
	if (t_list == NULL) return NULL;

	t_list->head = t_list->tail = NULL;
	return t_list;
}

void push_front(TwoLinkedList* t_list, int data)
{
	if (t_list == NULL){
		fprintf(stderr, "The list cannot be accessed by this pointer!\n");
		return;
	}

	Node* node = create_node(data);
	if (node == NULL) return;

	if (t_list->head == NULL){
		t_list->head = node;
		t_list->tail = node;
		return;
	}
	else if (t_list->head == t_list->tail){
		t_list->head = node;
		t_list->head->next = t_list->tail;
		t_list->tail->prev = t_list->head;
		return;
	}


	Node* tmp = t_list->head;

	t_list->head = node;
	tmp->prev = t_list->head;
	t_list->head->next = tmp;

}

void push_back(TwoLinkedList* t_list, int data)
{
	if (t_list == NULL){
		fprintf(stderr, "The list cannot be accessed by this pointer!\n");
		return;
	}

	Node* node = create_node(data);
	if (node == NULL) return;

	if (t_list->tail == NULL){
		t_list->head = node;
		t_list->tail = node;
		return;
	}
	else if (t_list->head == t_list->tail){
		t_list->tail = node;
		t_list->tail->prev = t_list->head;
		t_list->head->next = t_list->tail;
		return;
	}


	Node* tmp = t_list->tail;

	t_list->tail = node;
	tmp->next = t_list->tail;
	t_list->tail->prev = tmp;

}

int pop_front(TwoLinkedList* t_list)
{
	if (t_list == NULL){
		fprintf(stderr, "The list cannot be accessed by this pointer!\n");
		return;
	}

	int data;
	Node* tmp;

	if (t_list->head == NULL){
	   	 fprintf(stderr, "PopError: list is empty!\n");
		 return 0;
	}

	tmp = t_list->head;
	data = tmp->data;

	t_list->head = t_list->head->next;
	if (t_list->head == NULL) t_list->tail = NULL;
	
	free(tmp);
	return data;	
}


int pop_back(TwoLinkedList* t_list)
{
	if (t_list == NULL){
		fprintf(stderr, "The list cannot be accessed by this pointer!\n");
		return;
	}
	
	Node* tmp;
	int data;

	if (t_list->tail == NULL){
	   	 fprintf(stderr, "PopError: list is empty!\n");
		 return 0;
	}

	tmp = t_list->tail;
	data = tmp->data;

	t_list->tail = t_list->tail->prev;
	if (t_list->tail == NULL) t_list->head = NULL;
	
	free(tmp);
	return data;	
}


void show_list(TwoLinkedList* t_list)
{
	if (t_list == NULL){
		fprintf(stderr, "The list cannot be accessed by this pointer!\n");
		return;
	}

	if (t_list->head == NULL){
		printf("List is empty!\n");
		return;
	}
	Node* node = t_list->head;
	while (node != NULL){
		printf("%d ", node->data);
		node = node->next;
	}
	printf("\n");
}

void clear_list(TwoLinkedList* t_list)
{
	while (t_list->head != NULL){
		pop_front(t_list);
	}
}


void free_list(TwoLinkedList* t_list)
{
	clear_list(t_list);
	free(t_list);
}

