unsigned moveright(int *arr, int key, int last)
{
	if (last == 0)
		return last;
	while (last >= 1 && key < arr[last-1])
	{
		arr[last] = arr[last-1];
		last--;
	}

	return last;
}

void inssort(int* arr, unsigned length)
{
	for (unsigned i = 0; i < length; i++)	
	{
		int key = arr[i];
		unsigned pos = moveright(arr, key, i);
		arr[pos] = key;
	}
}

