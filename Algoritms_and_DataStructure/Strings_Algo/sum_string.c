#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {length = 1000};



void read_string(char* buff, int length)
{
	int c, cnt = 0;
	while ((c=getchar()) != EOF && cnt < length - 1)
	{
		if (c == '\0' || c == '\n') break;
		buff[cnt++] = c;
	}
	buff[cnt++] = '\0';
}

int main(void)
{
	int  res;
	unsigned total = 0;
	char buff[length];
	printf("Enter string: (length less then %d) ", length);
	read_string(buff, length);

	for (int i = 0; buff[i] != '\0'; i++)
		total += buff[i];
			
	printf("String <%s> has simbols sum equal %d\n", buff, total);

	return 0;
}
