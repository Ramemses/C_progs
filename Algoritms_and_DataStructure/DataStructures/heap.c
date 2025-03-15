#include <stdio.h>
#include <stdlib.h>


typedef struct heap_t{
	int heap_size;
	int* heap;
} Heap; 


int parent(int pos) {return pos/2;}
int left(int pos) {return pos*2 + 1;}
int right(int pos) {return pos*2 + 2;}


Heap* create_heap()
{
	Heap* heap = calloc(1, sizeof(Heap));
	if (heap == NULL) return NULL;
	heap->heap = NULL;
	heap->heap_size = 0;
}

void max_heapify(Heap* heap, int pos)
{
	int l = left(pos);
	int r = right(pos);
	int largest = pos;

	if (r < heap->heap_size && heap->heap[r] >= heap->heap[largest]) largest = r;
	if (l < heap->heap_size && heap->heap[l] >= heap->heap[largest]) largest = l;


	if (largest != pos){
		int tmp = heap->heap[largest];

		heap->heap[largest] = heap->heap[pos];
		heap->heap[pos] = tmp;

		max_heapify(heap, largest);
	}
}

void build_max_heap(Heap* heap, int* arr, int length)
{
	heap->heap = arr;
	heap->heap_size = length;
	
	for (int i = length/2; i >= 0; i--){
		max_heapify(heap, i);
		
	}
}

void heap_sort(int* arr, int length)
{
	int tmp;
	Heap* heap = create_heap();
	if (heap == NULL){
		fprintf(stderr, "Error creating the heap!\n");
		return ;
	}
	build_max_heap(heap, arr, length);
	for (int i = heap->heap_size; i > 0; i--){
		tmp = heap->heap[0];
		heap->heap[0] = heap->heap[heap->heap_size-1];
		heap->heap[heap->heap_size-1] = tmp;

		heap->heap_size -= 1;
		max_heapify(heap, 0);		
	}
	
	free(heap);

}


void show_heap(Heap* heap)
{
	for (int i = 0; i < heap->heap_size; i++){
		printf("%d ", heap->heap[i]);
	}
	printf("\n");
}

int main(void)
{
	int arr[] = {5, 3, 17, 10, 84, 19, 6, 22, 9};
	int length = sizeof(arr)/sizeof(*arr);

	Heap* heap = create_heap();
	if (heap == NULL){
		fprintf(stderr, "Error creating heap!\n");
		return 1;
	}

	
	build_max_heap(heap, arr, length);
	show_heap(heap);
	heap_sort(arr, length);
	show_heap(heap);

	return 0;
}
