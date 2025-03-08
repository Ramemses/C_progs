#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum{cur_buf = 30, cur_src= 50};

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

char* _strcat_r(char *dest, int bufsz, const char* src)
{
	int src_length = strlen(src);
	int dest_length = strlen(dest);
	char *res_ptr = dest;


	if (bufsz < src_length + dest_length + 1){
		char* ptr = realloc(dest, src_length + dest_length + 1);
		if (ptr == NULL) {
			fprintf(stderr, "Error realloc\n");
			return NULL;
		}
		res_ptr = ptr;
	}
	res_ptr = strcat(res_ptr, src);	
	return res_ptr;
}







int main(void)
{
	
	char* buff = calloc(cur_buf, sizeof(char));
	char* src=  calloc(cur_src, sizeof(char));
	char *new_buff = NULL;


	printf("Enter the buffer (length less then %d): ", cur_buf);
	read_string(buff, cur_buf);		

	printf("Enter the src (length less then %d): ", cur_src);
	read_string(src, cur_src);

	printf("String before concatenate <%s>\n", buff);
	new_buff = _strcat_r(buff, cur_buf, src);
	if (new_buff == NULL){
		fprintf(stderr, "Concataneting failed\n");
		return 1;
	}
	printf("String after concatenate <%s>\n", new_buff);

	free(src);
	buff = src = NULL;

	free(new_buff);
	new_buff = NULL;	
	
	return 0;
}
