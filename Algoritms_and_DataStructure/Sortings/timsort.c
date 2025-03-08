#include <stdio.h>
#include <stdlib.h>


unsigned moveright(int* arr, int key, int last)
{
	if (last == 0)
		return last;
	while (last >= 1 && key < arr[last-1]){
		arr[last] = arr[last-1];
		last--;	
	}		
	return last;
}
void inssort(int* arr, int left, int right)
{
	for (int i = left; i <= right; i++){
		int key = arr[i];
		int pos = moveright(arr, key, i);
		arr[pos] = key;
	}
}



void merge(int* arr, int left, int mid, int right)
{
	int *ptr1 = arr+left;
	int *ptr2 = arr+mid+1;
	
	int* ptr = malloc(sizeof(int) * (right-left+1));
	int cnt = 0;

	while (ptr1 <= arr+mid || ptr2 <= arr+right){
		if (ptr1 > arr+mid){
			*(ptr+cnt) = *ptr2;
			cnt++; ptr2++;
		}
		else if (ptr2 > arr+right){
			*(ptr+cnt) = *ptr1;
			cnt++; ptr1++;
		}
		else if (*ptr2 < *ptr1){
			*(ptr+cnt) = *ptr2; cnt++;
			ptr2++; 
		}
		else{
			*(ptr+cnt) = *ptr1; cnt++;
			ptr1++; 
		}
	}

	for (int i = 0; i < cnt; i++)
		*(arr+left+i) = *(ptr+i);
	
	free(ptr);
}

void timsort_impl(int* arr, int left, int right){
	if (left >= right - 10){
		inssort(arr, left, right);
		return;	
	}
	int mid = (left+right)/2;
	timsort_impl(arr, left, mid);
	timsort_impl(arr, mid+1, right);
	merge(arr, left, mid, right);		
}


void timsort(int* arr, unsigned length){ timsort_impl(arr, 0, length-1); }

void show(int *arr, unsigned length)
{
	for (unsigned i = 0; i < length; i++)
		printf("%d ", arr[i]);
	printf("\n");
}



