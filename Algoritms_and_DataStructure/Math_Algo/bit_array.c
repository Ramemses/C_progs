#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	int count, res; //Count of numbers and res of scanf()
	int bit, index, bit_index;
	char n = 1;
	printf("Enter the count of numbers: ");
	res = scanf("%d", &count);
	if (res != 1) //Check scanf() work
	{
		printf("Error input!\n\n");
		abort();
	}

	
	char *bit_arr = malloc(sizeof(char) * count);
	if (bit_arr == NULL) //Check memory allocation
	{
		printf("Error memory allocate");
		abort();
	}
	
	for (int i = 0; i < count; ++i)	
	{
		res = scanf("%hhd", bit_arr+i);
		if (res != 1)  //Check scanf() work for each number
		{
			printf("Error input!\n\n");
			abort();	
		}
	}

	res = scanf("%d", &bit); //Trying to read a number of changing bit
	if (res != 1) //Check scanf() work
	{
		printf("Error input!\n");
		abort();
	}

	index = bit / 8; //Number undex
	bit_index = bit % 8; // Bit index
		
	bit_arr[index] = bit_arr[index] & (~(n << bit_index));
	
	for (int i = 0; i < count; i++)
		printf("%hhd ", bit_arr[i]); //cout all numbers after changing bit
	printf("\n");
	


	return 0;
}	
