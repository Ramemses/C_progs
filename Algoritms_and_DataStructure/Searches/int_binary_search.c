int b_search(int *arr, unsigned length, int elem)
{
	unsigned last = length-1;
	unsigned first = 0;
	unsigned mid;
	while (first != last)
	{
		mid = (last+first)/2;
		if (arr[mid] == elem)
			return mid;
		if (arr[mid] > elem)
			last = mid-1;
		else if (arr[mid] < elem)
			first = mid+1;
	}	
	return (arr[mid] == elem) ? mid : -1;
}





