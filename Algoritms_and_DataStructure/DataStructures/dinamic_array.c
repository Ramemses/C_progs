#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// D_ARR STRUCTURE
typedef struct d_array{
	unsigned capacity;
	unsigned length;
	int* array;
} DinamicArray;

// CONSTRUCTOR
DinamicArray* create_array(unsigned capacity)
{
	DinamicArray* d_array = calloc(1, sizeof(DinamicArray));
	if (d_array == NULL) return NULL;
		
	d_array->array = calloc(capacity, sizeof(int));
	if (d_array->array == NULL){
		fprintf(stderr, "Error: cannot alocated memory for array elements\n");
		free(d_array);
		return NULL;
	}
	d_array->length = 0;
	d_array->capacity = capacity;
	return d_array;
	
}

//GETTERS
unsigned get_capacity(DinamicArray* d_array) {return d_array->capacity;}
unsigned get_length(DinamicArray* d_array) {return d_array->length;}


//RESIZE METHOD
int resize_arr(DinamicArray* d_array)
{
	d_array->capacity *= 2;

	int* ptr = realloc(d_array->array, sizeof(int)*d_array->capacity);
	if (ptr != NULL){
		d_array->array = ptr;
		return 0;
	}

	ptr = calloc(d_array->capacity, sizeof(int)*d_array->capacity);
	if (ptr == NULL) return 1;

	for (unsigned i = 0; i < d_array->length; i++)
		ptr[i] = d_array->array[i];
	free(d_array->array);
	d_array->array = ptr;
	
	return 0;
}

//DATA METHODS
void append(DinamicArray* d_array, int data)
{
	while (d_array->length >= d_array->capacity){
		int result =  resize_arr(d_array);
		if (result != 0) return;
	}

	d_array->array[d_array->length++] = data;
}

void insert(DinamicArray* d_array, int data, unsigned pos)
{
	while (d_array->length >= d_array->capacity){
		int result = resize_arr(d_array);
		if (result != 0) return;
	}
	
	for (unsigned i = d_array->length; i > pos; i--){
		d_array->array[i] = d_array->array[i-1];
	}
	d_array->array[pos] = data;
	d_array->length++;
}

int pop(DinamicArray* d_array, unsigned pos)
{
	if (pos >= d_array->length){
		fprintf(stderr, "IndexError: the index is out of range\n");
		return INT_MIN;
	}
	
	int data = d_array->array[pos];
	for (int i = pos; i < d_array->length-1; i++) 
		d_array->array[i] = d_array->array[i+1];
	d_array->length -= 1;
	

	return data;
}

//INTERFACE FUNCTION FOR PRINT ELEMENTS OF D_ARR
void show_arr(DinamicArray* d_array)
{
	for (unsigned i = 0; i < d_array->length; i++)
		printf("%d ", d_array->array[i]);
	printf("\n");
}


