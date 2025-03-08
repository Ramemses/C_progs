#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {cur_buff = 100, cur_from = 15, cur_to = 15};


int read_string(char* buff, int length)
{
	int c, cnt = 0;
	while ((c=getchar()) != EOF && cnt < length - 1)
	{
		if (c == '\0' || c == '\n') break;
		buff[cnt++] = c;
	}
	buff[cnt++] = '\0';

	return cnt;
}

char* d_replace(char* dest, unsigned pos, const char* to, unsigned to_length, unsigned from_length, unsigned dest_length)
{
	char* ptr = dest;	

	if (from_length == to_length){
		for (unsigned i = pos; i < pos + to_length; ++i)
			ptr[i] = to[i-pos];
		return ptr;
	}
	
	dest_length = dest_length - from_length + to_length;
	

	if (from_length <  to_length){
		ptr = realloc(dest, dest_length);

		if (ptr == NULL){
			fprintf(stderr, "Error memory reallocation\n");
			return NULL;
		}
		for (int i = dest_length-1; i > pos + to_length - from_length; --i)
				ptr[i] = ptr[i-(to_length - from_length)];
	}else{
		for(int i = pos + to_length; i < dest_length; i++)
			ptr[i] = ptr[i + from_length - to_length];
	
		ptr = realloc(dest, dest_length);
		if (ptr == NULL){
			fprintf(stderr, "Error memory reallocation\n");
			return NULL;
		}

		ptr[dest_length] = '\0';
	}
	
	for (unsigned i = pos; i < pos + to_length; ++i)
		ptr[i] = to[i-pos];

	return ptr;
}

char* replace(char* dest, const char* from , const char* to)
{
	char* ptr = strstr(dest, from);
	if (ptr == NULL) return NULL;

	unsigned to_length = strlen(to);
	unsigned from_length = strlen(from);


	while (ptr != NULL){
		unsigned dest_length = strlen(dest);
		unsigned index = ptr - dest;
		dest = d_replace(dest, index, to, to_length, from_length, dest_length);
		ptr = strstr(ptr + 1, from);
	}
	return dest;
}




int main(void)
{
	char* buff = (char*)calloc(cur_buff, sizeof(char));	
	if (buff == NULL){
		fprintf(stderr, "Error <buff> memory allocation\n");
		return 1;
	}
	
	char* from = (char*)calloc(cur_from, sizeof(char));	
	if (from == NULL){
		fprintf(stderr, "Error <from> memory allocation\n");
		free(buff); buff = NULL;
		return 1;
	}
	
	char* to = (char*)calloc(cur_to, sizeof(char));		
	if (to == NULL){
		fprintf(stderr, "Error <to> memory allocation\n");
		free(buff); buff = NULL;	
		free(from); from = NULL;
		
		return 1;
	}	
	char* new_buff = NULL;


	printf("Enter the string (length less then %d) : ", cur_buff);
	read_string(buff, cur_buff);
	printf("Enter the old substring (length less then %d) : ", cur_from);
	read_string(from, cur_from);
	printf("Enter the new substring (length less then %d) : ", cur_to);	
	read_string(to, cur_to);

	printf("String before replaces <%s> has length = %ld\n\n", buff, strlen(buff));


	new_buff = replace(buff, from, to);
	if (new_buff == NULL){
		fprintf(stderr, "Replace failed\n");
		return 2;
	}

	printf("String after replaces <%s> has length = %ld\n", new_buff, strlen(new_buff));
	


	return 0;
}
