#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

long long f(long long x){
	return x < 0 ? -x : x;
}

int main() {

	 long long a, b, c;
	 long long q;
	int res = scanf("%lld%lld", &a, &b);
	
	if (res != 2){
		fprintf(stderr, "Пошёл наxуй");
		return 1;
	}

	long long tmp_a = a, tmp_b = b;
	
	a = f(a);
	b = f(b);

	long long r;
	long long x = 0, x1 = 1, tmp_x;
	long long  y = 1, y1 = 0, tmp_y;
	long long tmp;


	while (b != 0){
		q = a/b;
		r = a % b;
		a = b;
		b = r;

		tmp_x = x1;
		x1 = x - q * x1;
		x = tmp_x;

		tmp_y = y1;
		y1 = y - q * y1;
		y = tmp_y;
		
	}
	

	if ( tmp_b < 0){
		x *= -1;
	}
	if ( tmp_a < 0){
		y *= -1;
	}


	printf("%lld %lld %lld\n", y, x, a);

	return 0;
}
