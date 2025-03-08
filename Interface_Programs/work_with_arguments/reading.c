#include <stdio.h>
#include <stdlib.h>

int find_in_file(const char* name, int needle){
	int count = 0, n; FILE* f;
	f = fopen(name, "r");
	if (f == NULL){
		perror("Error opening file");
		abort();
	}
	
	for (;;){
		int res;
		res = fscanf(f, "%d", &n);
		
		if (res == EOF)
			break;
		if (res != 1){
			fprintf(stderr, "File <%s> have broken format\n", name);
			abort();
		}
		if (needle == n)
			count++;
	} 		
	fclose(f);
	return count;
}

int main(int argc, char **argv)
{
	int n, i; char *endptr;
	int count = 0;
	if (argc < 3){
		fprintf(stderr, "Call: %s <n> <files...>\n", argv[0]);
		return 1;
	}	
	
	n = strtol(argv[1], &endptr, 10);
	if (endptr == argv[1]){
		fprintf(stderr, "<%s> can not be converted to int\n", argv[1]);
		return 1;
	}	 
		
 
	for (int i = 2; i <argc; i++)
		count += find_in_file(argv[i], n);
	printf("%d\n", count);
	
	return 0;
}
