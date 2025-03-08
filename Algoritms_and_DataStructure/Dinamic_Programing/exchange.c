#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min(int x, int y) {return x > y ? y : x;}

int start_programm(int** coins, int** exchanges, int* number, int* count)
{
	int res;

	printf("Enter count of coins: ");
	res = scanf("%d", count);
	if (res != 1){
		fprintf(stderr,"Error input!\n");
		return 1;
	}
	
	(*coins) = calloc(*count, sizeof(int));
	if ((*coins) == NULL){
		fprintf(stderr, "Error memory allocation for coins\n");
		return 2;
	}

	printf("Enter the coins: ");
	for (int i = 0; i < *count; i++){
		int x;
		res = scanf("%d", &x);
		if (res != 1){
			fprintf(stderr, "Error input coin[%d]", i);
			return 1;
		}

		(*coins)[i] = x;
	}


	printf("Enter the summ to eschange: ");
	res = scanf("%d", number);
	if (res != 1){
		fprintf(stderr, "Error input for summ\n");
		return 1;
	}
	(*exchanges) = calloc(*number+1, sizeof(int));
	if((*exchanges) == NULL){
		fprintf(stderr, "Error memory allocation for exchanges!\n");
		return 2;
	}
	for (int i = 0; i < *number+1; i++)
		(*exchanges)[i] = INT_MAX;

	return 0;
}

#if 0
int exchange(int number, int count,  int* coins, int* exchanges)
{
	if (number == 0) return 0;
	if (number < 0) return INT_MAX;
	if (exchanges[number] != INT_MAX) return exchanges[number];

	for (int i = 0; i < count; i++){
			int CT = exchange(number - coins[i], count, coins, exchanges);
			if (CT != INT_MAX) exchanges[number] = min(CT + 1, exchanges[number]);
	}

	return exchanges[number];
}
#endif

int exchange_iter(int number, int count, int* coins, int* exchanges)
{
	exchanges[0] = 0;
	
	for (int m = 1; m <= number; m++)
		for(int i = 0; i < count; i++)
			if (coins[i] <= m && exchanges[m - coins[i]] != INT_MAX) exchanges[m] = min(exchanges[m], exchanges[m-coins[i]]+1);

	return exchanges[number];
}



int main(void)
{
	int* coins;
	int* exchanges;
	int number, res, count;

	res = start_programm(&coins, &exchanges, &number, &count);
	if (res == 1) return 1;
	if (res == 2) return 2;



	printf("Coins: ");
	for (int i = 0; i < count; i++)
		printf("%d ", coins[i]);
	printf("\n");

	exchange_iter(number, count, coins, exchanges);

	for (int i = 1; i < number+1; i++){
		if (exchanges[i] != INT_MAX)
			printf("%d coins for %d summ\n", exchanges[i], i);
		else 
			printf("Cannot exchanges %d with this number of coins\n", i);
	}

	free(coins);
    free(exchanges);

	return 0 ;
}
