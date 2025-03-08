#include <stdio.h>
#include <stdlib.h>





enum{max_from_length = 30, max_to_length= 30};

int min(int x, int y, int z) {
    if (x < y && x < z) {
        return x;
    } else if (y < x && y < z) {
        return y;
    } else {
        return z;
    }
}

int read_string(char* buff, int length)
{
	int c, cnt = 0;
	while ((c=getchar()) != EOF && cnt < length - 1)
	{
		if (c == '\0' || c == '\n') break;
		buff[cnt++] = c;
	}
	buff[cnt++] = '\0';

	return cnt-1;
}

void optimal_redact(int** V, char* from, char* to, int from_length, int to_length)
{

	for (int row = 0; row <= from_length; row++){
		for (int col = 0; col <= to_length; col++){
			if (row == 0) V[row][col] = col;
			else if (col == 0) V[row][col] = row;
			else {
				int k = (from[row-1] == to[col-1] ? 0 : 2);
				V[row][col] = min(V[row-1][col]+1, V[row][col-1]+1, V[row-1][col-1] + k);
			}
		}		 
	}

}



int main(void)
{
	int to_length, from_length;


	int** table;
	char from[max_from_length];
	char to[max_to_length];
	
	printf("Enter the original string (length less then %d): ", max_from_length);
	from_length = read_string(from, max_from_length);

	printf("Enter the result string (length less then %d): ", max_to_length);
	to_length = read_string(to, max_to_length);

	table = calloc(from_length+1, sizeof(int*));
	if (table == NULL){
		fprintf(stderr, "Error memory allocation for table\n");
		return 1;
	}
	for (int i = 0; i <= from_length; i++){
		table[i] = calloc(to_length+1, sizeof(int));
		if (table[i] == NULL){
			fprintf(stderr, "Error memory allocation for part of table\n");
			return 1;
		}
	}

	optimal_redact(table, from, to, from_length, to_length);

	for (int i = 0; i <= from_length; i++){
		for (int j = 0; j <= to_length; j++)
			printf("%d ", table[i][j]);
		printf("\n");
	}



	return 0;
}

