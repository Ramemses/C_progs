#include <stdio.h>



int iabs(int x) {return (x > 0) ? x : -x;};

int eu_mod(int x, int y ) { return  iabs(x) % iabs(y);}

int gcd(int x, int y)
{
	if (eu_mod(x,y)  == 0)
		return y;
	return gcd(y, eu_mod(x,y)); 
}

void base_euqlide(int* r0, int* r1, int* s0, int* s1, int* t0, int* t1)
{
	int cur_r, cur_s, cur_t;
	int q;
	
	while (*(r1) != 0)	
	{
		q = *(r0) / *(r1);	
			
		cur_r = *(r0);
		*(r0) = *(r1);
		*(r1) = cur_r - q * *(r0);
	
		cur_s = *(s0);
		*(s0) = *(s1);
		*(s1) = cur_s - q * *(s0);

		cur_t = *(t0);
		*(t0) = *(t1);
		*(t1) = cur_t - q * *(t0);
	}
}


int main(void)
{
	int a,b,c;
	int g;
	printf("Input a,b,c: ");
	int res = scanf("%d%d%d", &a, &b, &c);
	if (res != 3)
	{
		printf("Error input!");
		return 0;
	}

	int r0 = a, s0 = 1, t0 = 0, r1 = b, s1=  0, t1 = 1;
	g = gcd(a,b);

	if (c % g != 0)
	{
		printf("No solution with integer numbers!");
		return 0;
	}
	

	base_euqlide(&r0, &r1, &s0, &s1, &t0, &t1);
	

	printf("The Euqlide solution : %d * %d + %d * %d = %d\n", s0, a, t0, b, r0);

	s0 *= c / g;
	t0 *= c / g;

	printf("The diaffant solition: %d * %d + %d * %d = %d\n\n", s0, a, t0, b ,c);
	
	
	return 0 ;


}
