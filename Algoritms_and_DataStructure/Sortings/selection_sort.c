int search(int const  *arr, unsigned length, unsigned pos)
{
	int min_index = pos;
	for (unsigned i = pos+1; i < length; i++)
		if(arr[i] < arr[min_index])		
			min_index = i;
	return min_index;
}	

void swap(int *v1, int *v2)
{
	int tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;	
}


void selsort(int *arr, unsigned length)
{
	for (unsigned i = 0; i < length; i++)
		swap(&arr[i], &arr[search(arr, length, i)]);
}

