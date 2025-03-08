#include <stdio.h>




void print_converted(unsigned n, unsigned y)
{	
	if (n == 0)
		return;
	print_converted(n/y, y);
	printf("%u", n%y);
}

int main(void)
{
	unsigned int a, s;
	printf("Enter the number and sytem: ");
	int res = scanf("%u%u", &a, &s);
	
	if (res != 2)
	{
		printf("Error input!");	
		return 0;
	}
	
	print_converted(a, s);		
	printf("\n");	

	return 0;


}
