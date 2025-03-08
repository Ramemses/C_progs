#include <stdio.h>
#include <stdlib.h>
#include <errno.h>






int main(void)
{
	FILE* f = fopen("new.txt", "w");
	if (f == NULL){
		perror("Error opening file");
		return 1;
	}
	fprintf(f, "%s", "This is an apple\n");
	fseek(f, 9, SEEK_SET);
	
	fprintf(f, "%s", " sam");
		
	return 0;
}

