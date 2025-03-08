#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void shuffle(int *arr, size_t length)
{
	for (size_t i = 0; i < length; i++)
	{
		size_t rand_index = rand() % length;
		int tmp = arr[length-i-1];
		arr[length-i-1] = arr[rand_index];
		arr[rand_index] = tmp;
	}
	
}
void show(int *arr, size_t length)
{
	for (size_t i =0; i < length; i++)
		printf("%d ", arr[i]);
	printf("\n");
}




int main(void)
{
	srand(time(NULL));
	int arr[] = {1,2,3,4,5,6,7,8,9,10,11};
	size_t length = sizeof(arr)/sizeof(*arr);
	
	for (size_t i = 0; i <length; i++)
	{
		shuffle(arr, length);
		show(arr, length);
	}
	

	return 0;
}
