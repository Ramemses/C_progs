#include <stdlib.h>
#include <assert.h>

unsigned partition(int* arr, unsigned low, unsigned high)
{
    int tmp;
    unsigned key = low; 
    low = low + 1;

    while (low <= high) 
    {
        if (arr[low] <= arr[key]) {
            low++;
	    continue;
        }        
        if (arr[high] >=  arr[key]) {
            high--;
	    continue;
        }
            assert(arr[low] > arr[high]);
         
	    tmp = arr[low];
            arr[low] = arr[high];
            arr[high] = tmp;
    }

    tmp = arr[key];
    arr[key] = arr[high];
    arr[high] = tmp;

    return high; 
}

void q_sort_i(int *arr, unsigned low, unsigned high)
{
	if (low >= high)
		return;
	unsigned pi = partition(arr, low, high);
	if (pi > low) q_sort_i(arr, low, pi-1);
	q_sort_i(arr, pi+1, high);
}
void q_sort(int* arr, unsigned length) {q_sort_i(arr, 0u, length-1);}






