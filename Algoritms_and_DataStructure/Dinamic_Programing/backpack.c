#include <stdio.h>
#include <stdlib.h>


int max(int x, int y) {return (x > y ? x : y);}

int start_programm(int** weights, int** prices,  int* count, int* capacity)
{
	int res;
	printf("Enter the number of items: ");
	res = scanf("%d", count);
	if (res != 1){
		fprintf(stderr, "Error input of count!\n");
		return 1;
	}

	printf("Enter the backpack capacity: ");
	res = scanf("%d", capacity);
	if (res != 1){
		fprintf(stderr, "Error input of capacity!\n");
		return 1;
	}
	
	(*weights) = calloc(*count+1, sizeof(int));
	if ((*weights) == NULL){
		fprintf(stderr ,"Error memory allocation to weights\n");
		return 2;
	}
	(*prices) = calloc(*count+1, sizeof(int));
	if((*prices) == NULL){
		fprintf(stderr, "Error memory allocation for prices\n");
		free((*weights));
		return 2;
	}

	printf("Enter the items like [weight] [price] (without brackets):\n");
	for (int i = 1; i < *count+1; i++){
		printf("%d : ", i);
		int weight, price;
		res = scanf("%d%d", &weight, &price);
		if (res != 2){
			fprintf(stderr, "Error input!\n");	
			return 1;
		}
		(*prices)[i] = price;
		(*weights)[i] = weight;
	}

	return 0;
}

int backpack_function(int** V, int* weights, int* prices, int count, int capacity)
{
	for (int cnt = 0; cnt <= count; cnt++){
	
		for (int cpt = 0; cpt <= capacity; cpt++){
			if (cnt == 0 || cpt == 0) V[cnt][cpt] = 0;
			else if (weights[cnt] > cpt) V[cnt][cpt] = V[cnt-1][cpt];
			else V[cnt][cpt] = max(V[cnt-1][cpt], V[cnt-1][cpt-weights[cnt]] + prices[cnt]);
		}
	}

}




int main(void)
{
	int* weights = NULL;
	int* prices = NULL;
	int** the_table = NULL;
	int count;
	int capacity;	



	int res = start_programm(&weights, &prices, &count, &capacity);
	if (res == 1) return 1;
	if (res == 2) return 2;

	the_table = calloc(count+1, sizeof(int*));
	if (the_table == NULL){
		printf("Error memory allocation for the table!\n");
		return 2;
	}
	for (int i = 0; i < count+1; i++){
		the_table[i] = calloc(capacity+1, sizeof(int));
		if (the_table[i] == NULL){
			fprintf(stderr, "Error memory allocation for table part!\n");
			return 2;
		}
	}

	

	backpack_function(the_table, weights, prices, count, capacity);




	for (int i =0; i < count+1; i++){
		for (int j =0; j < capacity+1; j++)
			printf("%d ", the_table[i][j]);

		printf("\n");
	}

	return 0;
}
