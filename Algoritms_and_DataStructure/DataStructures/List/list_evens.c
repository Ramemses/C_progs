#include <stdio.h>
#include <stdlib.h>

typedef struct node_t{
	struct node_t* next;
	int data;
} Node;

typedef struct lst_t{
	Node* head;
	int length;
} OneLinkedList;

OneLinkedList* create_list()
{
	OneLinkedList* list = calloc(1, sizeof(OneLinkedList));	
	if (list == NULL) return NULL;

	list->length = 0;
	list->head = NULL;

	return list;
}

void push_front(OneLinkedList* list, int data)
{
	Node* node = calloc(1, sizeof(Node));
	if (node == NULL) return;

	node->data = data;
	node->next = list->head;
	list->head = node;

	list->length++;
}

void pop_front(OneLinkedList* list)
{
	if (list->head == NULL){
		printf("List is already empty");
	}	
	Node* node = list->head;
	list->head = list->head->next;
	free(node);
	list->length--;	

	if (list->length == 0)
		free(list);	
}

void print_list(OneLinkedList* list)
{
	if (list->head == NULL){
		printf("None\n");
		return;
	}
	Node* node = list->head;
	while (node != NULL){
		printf("%d ", node->data);
		node = node->next;
	}
	printf("\n");
}

void even_or_not(const char* filename, OneLinkedList *even, OneLinkedList* not_even)
{
	int n;
	FILE* f = fopen(filename, "r");
	if (f == NULL){
		perror("Error opening file");
		abort();
	}
	
	for(;;){
		int res = fscanf(f, "%d", &n);
		
		if (res == EOF)
			break;
		if (res != 1){
			perror("File has broken format");
			abort();	
		}	

		if (n % 2 == 0)
			push_front(even, n);
		else
			push_front(not_even, n);
		
	}

	fclose(f);

}

int main(int argc, char** argv)
{
	int n, i;
	OneLinkedList* even = create_list();
	OneLinkedList*  not_even = create_list();
	char* endptr;
	
	if (argc < 2){
		fprintf(stderr, "Call <%s>  <files...>", argv[0]);
		return 1;
	}
	
	for (int i = 1; i <argc; i++)
		even_or_not(argv[i], even, not_even);

	if (even->head == NULL){
		print_list(not_even);
		return 0;
	}
	if (not_even->head == NULL){
		print_list(even);
		return 0;
	}

	Node* node = even->head;
	while(node->next != NULL)
		node = node->next;
	node->next = not_even->head;
		
	print_list(even);
	
	return 0;
}
