#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum{max_sub = 20, max_string = 128};

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

void failure_function(char* func, char* string, unsigned length)
{
	
	int k, index;
	func[0] = k = 0;
	index = 1;
	
	while (index <= length - 1){
		if (string[index] == string[k]){
				 func[index] = k+1;
				 k++;
				 index++;
			}
		else if (k == 0){
			 func[index] = 0;	 
			 index++;
		}
		else{
			 k = func[k];
		}
			
	}

}


char* strstr_kmp(char* needle, char* haystack)
{
	unsigned nd_length = strlen(needle);
	unsigned hs_length = strlen(haystack);
	int i = 0, j = 0;
 
	char* ptr = NULL;
	char* f = calloc(nd_length, sizeof(char));
	if (f == NULL) return NULL;
	failure_function(f, needle, nd_length);
	
	
	while(i < hs_length){
		if (needle[j] == haystack[i]){
			i++; j++; 
		}	
		else if (j > 0 && f[j-1] > 0){
			i += i - f[j-1];
			j = 0;
		}
		else{i++; j = 0;}
		
		if (j == nd_length){
			ptr = haystack + i - j;
			return ptr;
		}
	}


	return NULL;
}



int main(void)
{
	int index;
	char substring[max_sub];
	char string[max_string];

	char* ptr = NULL;
	printf("Enter the string (length less the %d): ", max_string);
	read_string(string, max_string);
	
	printf("Enter the substring (length less the %d): ", max_sub);
	int length = read_string(substring, max_sub);
		
	ptr = strstr_kmp(substring, string);
	puts(substring);

	if (ptr == NULL){
		printf("There is no matches to <%s> in string\n", substring);
		return 0;
	}
	
	index = ptr - string;
	printf("There is match at string[%d:%d] = ", index, index+length);
 	for (int i = 0; i < length; i++)
		putchar(string[index+i]);
	printf("\n");

	

	return 0;
}
