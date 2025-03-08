#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

enum{b_size = 20, reg_length = 20, str_length = 128, MAX_MATCHES = 10, BUFFSIZE = 128};


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

void reg_reverse(regex_t* regex, char* string, regmatch_t* matches)
{
	int res;
	unsigned start = 0;
	while(1){
		res = regexec(regex, string + start, MAX_MATCHES, matches, 0);
		if (res == 0){
			for (size_t i = 0; i <= (*regex).re_nsub; i++)
				word_reverse(string, start + matches[i].rm_so, start + matches[i].rm_eo);
			start += matches[0].rm_eo;
		}
		else break;
	}
}


int main(void)
{
	regex_t regex;
	int res, r;
	char buff[BUFFSIZE];
	char regex_str[reg_length];
	char string[str_length];
	regmatch_t matches[MAX_MATCHES];
	

	printf("Enter the regular expression (length less then %d) : ", reg_length);
	read_string(regex_str, reg_length);

	res = regcomp(&regex, regex_str, REG_EXTENDED);
	if (res){	
		fprintf(stderr, "Regex compile failed\n");
		return 1;
	}
	printf("Enter the string (length less then %d) : ", str_length);	
	read_string(string, str_length);
	
	puts(string);
	reg_reverse(&regex, string, matches);
	puts(string);


	regfree(&regex);
	return 0;
}
