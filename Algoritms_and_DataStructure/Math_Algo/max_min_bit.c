#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	unsigned long long num, n = 1;
	int max_bit = -1, min_bit = -1, cnt = 0;
	printf("Enter the number: ");
	int res  = scanf("%llu", &num);
	if (res != 1)
	{
		printf("Error input!\n");
		abort();
	}
	
	while (n <=num)
	{
		if ((num & n) != 0)
		{
			min_bit = cnt;
			break;
		}
		n = n << 1;
		cnt++;
	}
	while (n <= num)
	{		
		
		if ((num & n) != 0)	
			max_bit = cnt;
		n = n << 1;
		++cnt;
	}
	
	printf("%d %d\n", max_bit, min_bit);
	
	return 0;
}
