#include <stdio.h>
#include <stdlib.h>


unsigned long long fibonachi_mod(unsigned long long n, unsigned long long d)
{
	unsigned long long second = 1, first = 0;
	if (n < 2)
		return n;
	for(unsigned long long i = 2; i <= n; i++)
	{
		unsigned long long tmp = first;
		first = second % d;
		second = (first + tmp) % d;
	}
	return second;

}

int main(void)
{
	int res;
	
	unsigned long long fib, n,d ;
	printf("Введите число последовательности и её модуль:  ");
	
	res = scanf("%llu%llu", &n, &d);
	if (res != 2)
	{
		printf("Ошибка ввода\n");
		return 0;
	}

	fib = fibonachi_mod(n, d);
	printf("Фибоначи по модулю %llu: %llu\n", n, fib);

	return 0;
}
