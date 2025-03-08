#include <stdio.h>
#include <stdlib.h>

int maxim(int* arr, unsigned length)
{
	int maximum = arr[0];
	for(unsigned i = 1; i < length; i++)
		if (arr[i] > maximum)
			maximum = arr[i];
	return maximum;
}
int minim(int* arr, unsigned length)
{
	int minimum = arr[0];
	for(unsigned i = 1; i < length; i++)
		if (arr[i] < minimum)
			minimum = arr[i];
	return minimum;
}
void count_sort(int* arr, unsigned length)
{
	int min = minim(arr, length);
	int max = maxim(arr, length);
	int* t_arr = calloc(max - min + 1, sizeof(int));
	
	for (unsigned i = 0; i < length; i++)
		t_arr[arr[i]-min] += 1;

	for (unsigned i = 0, j = 0; j < length && i < max-min+1;)
	{
		if(t_arr[i] == 0){
			i++;
			continue;
		}
		arr[j] = i+min;
		t_arr[i]--;
		j++;		
	}

	free(t_arr);
}

void show(int* arr, unsigned length)
{
	for (unsigned i = 0; i < length; i++)
		printf("%d ", arr[i]);
	printf("\n");
}


int main(void)
{

	int arr[] = {5,3,5,6,7,4,3,6,8,5,4,3,3,7,8,3,5};
	unsigned length = sizeof(arr)/sizeof(*arr);
	show(arr, length);
	count_sort(arr, length);
	show(arr, length);


	return 0;
}
