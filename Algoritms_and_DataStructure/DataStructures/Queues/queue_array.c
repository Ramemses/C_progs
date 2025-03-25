#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct queue_t{
	int head;
	int tail;
	int count;
	int length;
	int* arr;
} Queue;


char is_full(Queue* queue) {return queue->count == queue->length;}
char is_empty(Queue* queue) {return queue->count == 0;}


Queue* create_queue(int size)
{
	Queue* queue = calloc(1, sizeof(Queue));
	if (queue == NULL) return NULL;

	queue->arr = malloc(sizeof(int) * size);
	if (queue->arr == NULL) return NULL;

	queue->tail = queue->head = 0;
	queue->length = size;	
	queue->count = 0;

	return queue;
}



void enqueue(Queue* queue, int x)
{
	if (is_full(queue)){
		fprintf(stderr, "The queue is full!\n");
		return ;
	}

	queue->arr[queue->tail] = x;
	queue->tail = (queue->tail + 1) % queue->length;

	queue->count += 1;
}


int dequeue(Queue* queue)
{
	if (is_empty(queue)){
		fprintf(stderr, "The queue is empty!\n");
		return INT_MIN;
	}

	int x = queue->arr[queue->head];
	queue->head = (queue->head + 1) % queue->length;

	queue->count -= 1;
	return x;
	
}

void show_queue(Queue* queue)
{
	int head = queue->head;	

	for (int i = 0;i < queue->count; i++){
		printf("%d ", queue->arr[head]);
		head = (head + 1) % queue->length;
	}	

	printf("\n");
}

void show_params(Queue* queue)
{
	printf("Tail = %d\n", queue->tail);
	printf("Head = %d\n", queue->head);
	printf("Count = %d\n", queue->count);
	printf("Length = %d\n", queue->length);

}

void clear_queue(Queue* queue)
{
	while (!(is_empty(queue)))
		dequeue(queue);
}

void free_queue(Queue* queue)
{
	free(queue->arr);
	free(queue);
}


