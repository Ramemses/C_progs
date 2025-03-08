#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char* strstr_ci(const char* needle, const char* haystack)
{
	char* ptr = NULL;
	int flag = 1;
	for(int i = 0; haystack[i] != '\0'; i++){
		flag = 1;
		for(int j = 0, k = i; needle[j] != '\0'; j++, k++)
			if (tolower(haystack[k]) != tolower(needle[j])){
				flag = 0;
				break;
			}

		if (flag == 1){
			ptr = (char*)(haystack + i);
			break;
		}
	}

	return ptr;	

}



int main(void)
{

	char str1[] = "Hello, my dear friend";
	char str2[] = "FRIEND";

	char* ptr = strstr_ci(str2, str1);
	if (ptr != NULL) puts(ptr);
	else puts("Error!");	

	return 0;
}
