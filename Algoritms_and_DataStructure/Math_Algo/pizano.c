#include <stdio.h>



int fibonachi_mod(int n ,int p)
{
	int first = 0, second =1;
	if (n <2)	
		return n;
	for (int i = 2; i <= n; i++)
	{
		int tmp = first;	
		first = second % p;
		second = (first + tmp) % p;
	}
	return second;
}



int pizano(int p)
{
	int length = 2;
	int previous = 2, current = 3;
	while (fibonachi_mod(previous, p) != 0 || fibonachi_mod(current, p) != 1)
	{
		previous++;
		current++;
		length++;
	}

	return length;
} 
			


int main(void)
{
	int p, result_length;
	int res;
	printf("Etner the mod number:  ");
	res = scanf("%d", &p);
	if (res != 1)
	{
		printf("Error input!\n");
		return 0;
	}

	result_length = pizano(p);

	printf("Pizano preiod for mod %d = %d\n" ,p , result_length);

	return 0;
}


	
	

