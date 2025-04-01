#include <stdio.h>
#include <stdlib.h>


double min (double x, double y) {return x > y ? y : x;}

void the_transported_table(int n, double e1, double e2, double* f1, double *f2, double* a1, double* a2, double* t1, double* t2)
{
	f1[0] = e1 + a1[0];
	f2[0] = e2 + a2[0];

	for (int i = 1; i < n; i++){
		f1[i] = min(f1[i-1], f2[i-1] + t2[i-1]) + a1[i];
		f2[i] = min(f2[i-1], f1[i-1] + t1[i-1]) + a2[i];
	}
}


int the_start(int* n, double* e1, double* e2, double** f1, double** f2, double** a1, double** a2, double** t1, double** t2)
{

	printf("Enter the number of positions: ");
	int result = scanf("%d", n);
	if (result != 1){
		fprintf(stderr, "Error input!\n");
		return 0;
	}
	
	printf("Input start_time for first transporter (e1): ");
	result = scanf("%lf", e1);
	if (result != 1){
		fprintf(stderr, "Error input!\n");
		return 0;
	}
	
	printf("Input start_time for second transporter (e2): ");
	result = scanf("%lf", e2);
	if (result != 1){
		fprintf(stderr, "Error input!\n");
		return 0;
	}
//--------------
	*f1 = calloc(*n, sizeof(double));
	if (*f1 == NULL){
		fprintf(stderr, "Error memory allocation!\n");
		return 1;
	}

	*f2 = calloc(*n, sizeof(double));
	if (*f2 == NULL){
		fprintf(stderr, "Error memory allocation!\n");
		return 1;
	}

	*a1 = calloc(*n, sizeof(double));
	if (*a1 == NULL){
		fprintf(stderr, "Error memory allocation!\n");
		return 1;
	}
	*a2 = calloc(*n, sizeof(double));
	if (*a2 == NULL){
		fprintf(stderr, "Error memory allocation!\n");
		return 1;
	}
	*t1 = calloc(*n-1, sizeof(double));
	if (*t1 == NULL){
		fprintf(stderr, "Error memory allocation!\n");
		return 1;
	}
	(*t2) = calloc(*n-1, sizeof(double));
	if (*t2 == NULL){
		fprintf(stderr, "Error memory allocation!\n");
		return 1;
	}
//--------------

	for (int i = 0; i < *n; i++){
		printf("Enter the a1%d: ", i+1);
		result = scanf("%lf", (*a1)+i);
		if (result != 1){
			fprintf(stderr, "Error input!\n");
			return 1;
		}
		printf("\n");
	}

	for (int i = 0; i < *n; i++){
		printf("Enter the a2%d: ", i+1);
		result = scanf("%lf", (*a2)+i);
		if (result != 1){
			fprintf(stderr, "Error input!\n");
			return 1;
		}
		printf("\n");
	}

	for (int i = 0; i < *(n)-1; i++){
		printf("Enter the t1%d: ", i+1);
		result = scanf("%lf", (*t1)+i);
		if (result != 1){
			fprintf(stderr, "Error input!\n");
			return 1;
		}
		printf("\n");
	}

	for (int i = 0; i < *(n)-1; i++){
		printf("Enter the t2%d: ", i+1);
		result = scanf("%lf", (*t2)+i);
		if (result != 1){
			fprintf(stderr, "Error input!\n");
			return 1;
		}
		printf("\n");
	}

	return 0;
}


int main(void)
{
	int n;
	double e1, e2;
	double *f1, *f2;
	double *a1, *a2;
	double *t1, *t2;
	
	int result = the_start(&n, &e1, &e2, &f1, &f2, &a1, &a2, &t1, &t2);
	the_transported_table(n, e1, e2, f1, f2, a1, a2, t1, t2);	

	for (int i = 0; i < n; i++){
		printf("f1%d = %lf\n", i+1, f1[i]);
	}

	for (int i = 0; i < n; i++){
		printf("f2%d = %lf\n", i+1, f2[i]);
	}

	free(f1);
	free(f2);
	free(a1);
	free(a2);
	free(t1);
	free(t2);

	return 0;
}
