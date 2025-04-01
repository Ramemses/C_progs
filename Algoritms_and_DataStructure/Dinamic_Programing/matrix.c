#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void matrix_optimal(int n, int** m, int** A)
{
	for (int i = 0; i < n; i++)
		m[i][i] = 0;		

	for (int l = 1; l < n; l++){
		for (int i = 0; i < n-l; i++){
			int j = i+l;
			m[i][j]	= INT_MAX;
			for (int k = i; k < j; k++){
				int q = m[i][k] + m[k+1][j] + A[0][i] * A[1][k] * A[1][j];
				if (q < m[i][j]) m[i][j] = q;
			}
		}
	}

}



int main(void)
{

	int n, result;
	printf("Enter chain length: ");
	result = scanf("%d", &n);
	if (result != 1){
		fprintf(stderr, "Error input!\n");
		return 1;
	}
	
	int **m = calloc(n, sizeof(int*));
	if (m == NULL){
		fprintf(stderr, "Error memory allocation");	
		return 1;
	}

	for (int i = 0; i < n; i++){
		m[i] = calloc(n, sizeof(int));
		if (m[i] == NULL){
			fprintf(stderr, "Error memory allocation!\n");
			return 1;
		}

	}	
	
	int** chain_A = calloc(2, sizeof(int*));
	if (chain_A == NULL){
		fprintf(stderr, "Error memory allocation!\n");
		return 1;
	}

	
	chain_A[0] = calloc(n, sizeof(int));
	if (chain_A[0] == NULL) return 1;
	chain_A[1] = calloc(n, sizeof(int));	
	if (chain_A[1] == NULL) return 1;


	for (int i = 0; i < n; i++){
		printf("Enter A%d params: ", i+1);
		result = scanf("%d%d", chain_A[0] + i, chain_A[1] + i);
		if (result != 2){
			fprintf(stderr, "Error input!\n");
			return 2;
		}
	}		

	matrix_optimal(n, m, chain_A);

	for (int i =0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (m[i][j] != 0) printf("%5d ", m[i][j]);	
			else printf("      ");
		}	
		printf("\n");
	}
	return 0;
}
