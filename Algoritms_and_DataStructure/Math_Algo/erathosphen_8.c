#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>



struct sieve{
	unsigned long long size;	
	char* ptr_sieve;
};

int is_prime(unsigned long long x, struct sieve* s)
{
	if (x == 2 || x == 3) return 1;
	if ( (x % 2 == 0) || (x % 3 == 0) || (x < 2)) return 0;
	
	unsigned long long index = x / 8;
	unsigned long long  bit_index = x % 8;
	
	if ( ((s->ptr_sieve[index] >> bit_index) & 1) == 0)
		return 1;
	return 0;
}

void set_prime(unsigned long long x, struct sieve* s)
{
	unsigned long long index = x/8, bit_index = x % 8;
	s->ptr_sieve[index] |= (1 << bit_index);

}

void init_sieve(unsigned long long cnt, struct sieve* ptr)
{
	ptr->size = cnt/8 + cnt%8;
	ptr->ptr_sieve = (char*)calloc(ptr->size, sizeof(char));
	if (ptr->ptr_sieve == NULL) return;
		

	for (int i = 2; i*i <= cnt; i++)
	{
		if (is_prime(i, ptr) == 1)
			for (int j = i*i; j <= cnt; j+=i)
				set_prime(j, ptr);	
	}
}


void free_sieve(struct sieve* s)
{
	free(s->ptr_sieve);
	s->ptr_sieve = 0;
	s->size = 0;
}

int main(void)
{
	struct sieve* ptr_sieve = calloc(1, sizeof(struct sieve));
	if (ptr_sieve == NULL) return 0;
	unsigned long long length, cnt = 0;
	printf("Enter the number: ");
	int res = scanf("%llu", &length);
	if (res != 1)
	{
		printf("Error input!");
		abort();
	}
	
	
	init_sieve(length, ptr_sieve);
	
	for (int i =0; i <= length; i++)
	{	
		char flag = is_prime(i, ptr_sieve);
		if (flag == 1) cnt++;
		printf("%d %hhd\n", i, flag);
	}
	printf("Prime number: %lld\n\n", cnt);	
	
	free_sieve(ptr_sieve);
	return 0;
};	
