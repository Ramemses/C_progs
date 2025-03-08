#include <stdio.h>
#include <stdlib.h>

void swap(int* arr, int first, int second)
{
	int tmp = arr[first];
	arr[first] = arr[second];
	arr[second] = tmp;
}
void heapify(int* arr, int heap_size, int i)
{
	int s = i;
	int left = 2*i + 1;
	int right = 2*i + 2;
	if (left < heap_size && arr[left] > arr[s]) s = left;

	if (right < heap_size && arr[right] > arr[s]) s = right;

	if (s != i){
		swap(arr, i, s);
		heapify(arr, heap_size, s);	
	}
}
void buildheap(int* arr, int length)
{
	int heap_size = length;
	for (int i = heap_size/2; i >= 0; i--)
		heapify(arr, heap_size, i);
}
void heapsort(int* arr, int length)
{
	buildheap(arr, length);
	for (int i = length-1; i >= 0; i--){
		swap(arr, i, 0);
		heapify(arr, i, 0);
	}
}

