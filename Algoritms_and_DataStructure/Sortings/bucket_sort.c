#include <stdio.h>
#include <stdlib.h>




typedef struct node_t{
	struct node_t* next;
	int data;
} Node;

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


void print_list(Node* top)
{
	if (top == NULL){
		printf("None\n");
		return;
	}

	Node* node = top;
	while (node != NULL){
		printf("%d ", node->data);
		node = node->next;
	}
	printf("0 ");
}

void free_list(Node* top){
	while (top != NULL)
	top = pop_front(top);
}

int find_max(int *arr, int length){
	int maximum = arr[0];
	for(int i = 1; i < length; i++)
		if (maximum < arr[i])
			maximum = arr[i];
	return maximum;
}

Node* append_sort(Node* top, int data)
{
		
	Node* node = calloc(1, sizeof(Node));
	if (node == NULL) return top;
	node->data = data;	

	if (top == NULL) return node;
	if (top->next == NULL && top->data < node->data){	
		top->next = node;
		return top;
	}	

	if (top->data > node->data) return push_front(top, data);
	
	Node* ptr = top;
	while (ptr != NULL && ptr->next != NULL && node->data > ptr->next->data)
		ptr = ptr->next;
	
	if (ptr->next == NULL || ptr == NULL){
		ptr->next = node;
		return top;
	}
	
	node->next = ptr->next;
	ptr->next = node;
	
	return top;
	
}


int main(void)
{
	

	int n;
	printf("Введите размер массива: ");
	int res = scanf("%d", &n);

	int* arr = malloc(sizeof(int) * n);
	if (arr == NULL){
	   	fprintf(stderr, "Ошибка выделения памяти по массив\n");
	    return 1;
	}

	printf("Введите элементы массива:\n");
	for (int i = 0; i < n; i++){
		if (scanf("%d", &arr[i]) !=  1){
			return 1;
		}
	}

	int max = find_max(arr, n);
	int range = (max/n) + 1;	

	Node** node_arr = malloc(n*sizeof(Node*));
	if (node_arr == NULL){
		fprintf(stderr, "Ошибка выделения памяти\n");
		return 1;
	}	


	for (int i = 0; i < n; i++)
		node_arr[i] = NULL;
		
	for (int i = 0; i < n; i++){
		int index = arr[i] / range;
		
		node_arr[index] = append_sort(node_arr[index], arr[i]);
	}



	
    	for (int i = 0; i < n; i++) {
	        free_list(node_arr[i]);
	    }
	free(node_arr);
    	free(arr);
	
	return 0;
}	

