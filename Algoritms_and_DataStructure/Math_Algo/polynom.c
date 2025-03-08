#include <stdio.h>
#include <stdlib.h>

struct Poly{
	unsigned n;
	unsigned *p;
};


struct Poly mult(struct Poly lhs, struct Poly rhs)
{
	struct Poly ret = {rhs.n+lhs.n -1, NULL};
	ret.p = calloc(ret.n, sizeof(unsigned));
	
	for (unsigned i = 0; i < lhs.n; i++)
		for (unsigned j = 0; j < rhs.n; j++)
		{
			ret.p[j+i] += lhs.p[i] * rhs.p[j];
		}

	return ret;
}
void free_poly(struct Poly pl)
{
	pl.n = 0;
	free(pl.p);
	pl.p = NULL;
}
void show_p(struct Poly p)
{
	for (int i = 0; i < p.n; i++)
		printf((i == p.n - 1) ? "%ux^%u" : "%ux^%u + ", p.p[i], p.n-i-1);
	printf("\n");
}

int main(void)
{
#if 0
	struct Poly pl1 = {3, NULL};
	pl1.p = calloc(pl1.n, sizeof(unsigned));
	pl1.p[0] = 1;	
	pl1.p[1] = 2;
	pl1.p[2] = 1;
	show_p(pl1);
	struct Poly pl2 = {3, NULL};
	pl2.p = calloc(pl2.n, sizeof(unsigned));
	pl2.p[0] = 1;
	pl2.p[1] = 2;
	pl2.p[2] = 1;
	show_p(pl2);
	struct Poly res = mult(pl1,pl2);
	
	show_p(res);
	free_poly(pl1);
	free_poly(pl2);
	free_poly(res);
#endif
	return 0;
}
