#include <stdio.h>
#include <stdlib.h>
#include <regex.h>


enum {BUFFLEN = 128, string_length = 128};


char* email_regex = "[A-Za-z0-9_.+-]+@[A-Za-z0-9-]+\\.[A-Za-z]{2,}";

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


int main(void)
{
	int res;
	char buff[BUFFLEN];
	char string[string_length];

	regex_t regex;
	res = regcomp(&regex, email_regex, REG_EXTENDED);
	if (res){
		fprintf(stderr, "Could not compile regex\n");
		return 1;
	}


	printf("Enter the email: ");
	int n = read_string(string, string_length);
	if (n == 0){
		fprintf(stderr,"Error input\n");
		return 2;
	}

	res= regexec(&regex, string, 0, NULL, 0);

	if (res != 0 && res != REG_NOMATCH){
		regerror(res, &regex, buff, sizeof(buff));
		fprintf(stderr, "Regex match failed: %s\n", buff);
	}
	else if (res == 0)
		printf("Email <%s> is correct!\n", string);
	else if (res == REG_NOMATCH)	
		printf("Email <%s> is incorrect!\n", string);


	regfree(&regex);
	return 0;
}
