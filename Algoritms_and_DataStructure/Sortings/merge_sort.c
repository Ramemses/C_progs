#include <stdio.h>
#include <stdlib.h>


void merge(int *arr, int left, int mid, int right)
{
	int *ptr = malloc(sizeof(int) * (right+1)); //Memory alloc for sorting array
	
	int cnt = 0;//Counter for sorting array

	//Pointer for two parts of orignal array
	int *ptr1 = arr+left;
	int *ptr2 = arr+mid+1;
	
	//Merge two parts of original array in allocated memory	
	while (ptr2 <= arr+right || ptr1 <= arr+mid)
	{
		if (ptr2 > arr+right){
			*(ptr+cnt) = *ptr1;
			cnt++;
			ptr1++;
		}
		else if (ptr1 > arr+mid){
			*(ptr+cnt) = *ptr2;
			cnt++; ptr2++;	
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
	//Rewrite sorted array to the original one
	int j = 0, i = left;
	while ( j < cnt && i <= right)
	{
		arr[i] = ptr[j];
		i++;
		j++;
	}
	//Dont`t forget to free!	
	free(ptr);					
}

void merge_sort_impl(int *arr, int left , int right)
{
	if (left >= right) return;

	int mid = (left+right)/2;

	merge_sort_impl(arr, left, mid);
	merge_sort_impl(arr, mid+1, right);
	merge(arr, left, mid, right);
}

void merge_sort(int *arr, int length) {merge_sort_impl(arr, 0, length-1);}

