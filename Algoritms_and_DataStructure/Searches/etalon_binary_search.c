int comparing_for_int(const void* a, const void* b) //Example of comparator (*comp)(const* void, const* void)
{	
	const int* ia = (const int*)a;
	const int* ib = (const int*)b;
	if (*ia > *ib) return 1;
	if (*ia < *ib) return -1;
	return 0;
}


void*  b_search(const void *key, const void* arr, unsigned length, unsigned size, int (*comp)(const void*, const void*))
{
	unsigned last = length-1, first = 0, mid;
	int result;	
	void* current; // ptr for comparing elements in array with key(searched element)
	while (last != first)
	{
		mid = (last+first)/2;
		current = arr+size*mid;
		result = comp(current, key); //Found the element
		if (result == 0)
			return current;		
		else if(result == 1) // elem < arr[mid]
			last = mid-1;
		else if (result == -1) // elem > arr[mid]
			first = mid+1;

	}
	//If not found the element in loop
	mid = (last+first)/2;
	current = arr+size*mid;
	result = comp(current, key);

	return (result == 0) ? current : (void*)0; // Found or not found the element

}

