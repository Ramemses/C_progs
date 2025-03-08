#include <stdio.h>
#include <stdlib.h>
//This algoritm founds the element which occurs in array more the len/2 times

int major(int* arr, unsigned length)
{
	int elem = arr[0];
	unsigned voices = 0;
	
	for (unsigned i = 1; i < length; i++)
	{
		if (arr[i] == elem)
			voices++;
		else if(voices == 0)
			elem = arr[i];
		else 
			voices--;
	}
	if (voices == 0)
		elem = -1;
	return elem;
}

int main(void)
{

	int arr[] = {1,3,4,5,6,7,8,5,3,2,2,7,7,7,7,7,7,7,4,5,6,5,6,7};
	unsigned length = sizeof(arr)/sizeof(*arr);
	int elem = major(arr, length);
	if (elem == -1)
		printf("There is no majority element\n");
	else
		printf("%d\n", elem);
	return 0 ;
}
