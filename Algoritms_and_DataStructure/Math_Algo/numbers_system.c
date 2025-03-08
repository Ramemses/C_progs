#include <stdio.h>

#if 0
unsigned long long pow_mod(unsigned long long  n, unsigned long long k, unsigned long long m)
{
	unsigned long long  mult = n % m;
	unsigned long long prod = 1;
	while (k > 0)
	{
		if (k % 2 == 1)
		{
			prod = (prod * mult) % m;
			k -= 1;
		}
		mult = (mult * mult) % m;  
		k/=2;
	}
	return prod;

}
#endif //Возведение в степень по модулю


// Обычное возведение в степень
unsigned long long just_pow(unsigned long long n, unsigned long long  k)
{
	unsigned long long prod = 1;
	unsigned long long mult = n;
	
	while (k > 0)
	{
		if (k % 2 == 1)
		{
			prod = prod * mult; k -=1;
		}
		mult = mult * mult; k/=2;
	}
	
	return prod;
}	

//Возведение в сверхстепень по модулю
unsigned long long super_pow_mod(unsigned  long long n, unsigned long long  k, unsigned long long m)
{
	unsigned long long res = 1;
	unsigned long long mult = n;
	
	while (k > 0)
	{
		if (k % 2 == 1)
		{
			res = just_pow(mult, n) % m ;
			k-=1;
		}
		mult = just_pow(mult, mult) % m;
		k/=2;
	}

	return res;		
}



int main(void)
{
	
	unsigned long long a,b,c;
	printf("Enter the number (n, k ,m): ");
	int res = scanf("%llu%llu%llu", &a, &b,  &c);
	if (res != 3)
	{
		printf("Error input!");	
		return 0;
	}
	
#if 0	
	unsigned product = pow_mod(a,b1,c);
	printf("The pow_mod = %u\n", product);
#endif

	unsigned long long super_product = super_pow_mod(a, b, c);
	printf("The super_pow_mod = %llu\n", super_product);
	
	return 0;

}				
