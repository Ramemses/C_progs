#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum {max_word_length = 20, max_text_length = 1000};


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


void word_reverse(char* src, unsigned start, unsigned end)
{	
	for (unsigned i = start; i < (end+start)/2; i++){
		char tmp = src[i];
		src[i] = src[end+start-i-1];
		src[end+start-i-1] = tmp;
	}	
}

void substrings_reverse(char* src, char* word, unsigned word_length)
{
	char* ptr = strstr(src, word);
	while(ptr != NULL){
		unsigned start = ptr - src;
		unsigned end = ptr-src + word_length - 1;
	
		word_reverse(src, start, end);
		ptr = strstr(ptr+word_length, word);
	}	
}


int main(void)
{
	char word[max_word_length];
	char string[max_text_length];

	printf("Enter the word (length less then %d)", max_word_length);
	int word_length = read_string(word, max_word_length);	
	
	printf("Enter the string (length less then %d)", max_text_length);
	int string_length = read_string(string, max_text_length);

	printf("Original string <%s>\n", string);

	substrings_reverse(string, word, word_length);

	printf("Reversed string <%s>\n", string);
	return 0;
}
