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
int get_digits(int el)
{
	int d = 0;
	while (el > 0){
		d++;
		el/=10;
	}
	return d;
}
void part_sort(int *arr, unsigned length, int expn)
{
	int output[length];
	int b[10] = {0};
	
	for(int i = 0; i < length; ++i)
		b[(arr[i]/expn)%10]++;	

	for(int i = 1; i < 10; ++i)
		b[i] += b[i-1];

	for(int i = length-1; i >= 0; --i){
		int d =( arr[i]/expn)%10;
		output[b[d] - 1] = arr[i];
		b[d]--;
	}
	for (int i = 0; i < length; ++i)
		arr[i] = output[i];
	
}
void radix_sort(int* arr, unsigned length)
{
	int m =  maxim(arr, length);
	
	for (int expn = 1; m/expn > 0; expn*=10){
		part_sort(arr, length, expn);
	}
}


void show(int* arr, unsigned length)
{
	for (unsigned i = 0; i < length; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int main(void)
{
	int arr[] = {126, 670, 343, 432, 316, 173, 556, 348};
	unsigned length = sizeof(arr)/sizeof(*arr);
	show(arr, length);
	radix_sort(arr, length);
	show(arr, length);

	return 0;
}
