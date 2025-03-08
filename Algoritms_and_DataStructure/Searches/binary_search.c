int comparing(const void* a, const void* b)
{	
	const int* ia = (const int*)a;
	const int* ib = (const int*)b;
	if (*ia > *ib) return 1;
	if (*ia < *ib) return -1;
	return 0;
}


int b_search(const void *arr, unsigned length, unsigned size, int elem, int (*comp)(const void*, const void*))
{
	unsigned last = length-1, first = 0, mid;
	const void *ptr = &elem;
	int result;	

	while (last != first)
	{
		mid = (last+first)/2;
		result = comp(arr+size*mid, ptr);
		if (result == 0)
			return mid;		
		else if(result == 1)
			last = mid-1;
		else if (result == -1)
			first = mid+1;

	}
	mid = (last+first)/2;
	result = comp(arr+size*mid, ptr);

	return (result == 0) ? mid : -1;

}


