#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>


enum {max_length = 30, BUFFSIZE = 128};

const char *patterns[] = {"^ *MOVI *[A-D]{1} *[0-9]{1,4} *$", "^ *ADD *[A-D]{1}, *[A-D]{1} *$", "^ *SUB *[A-D]{1}, *[A-D]{1} *$",
						  "^ *MUL *[A-D]{1}, *[A-D]{1} *$", "^ *DIV *[A-D]{1}, *[A-D]{1} *$", "^ *IN *[A-D]{1} *$" , "^ *OUT *[A-D]{1} *$"};


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


int reg_match(char* string)
{	
	
	regex_t regex[7];	
	char buff[BUFFSIZE];
	int res;




	
	for (int i = 0; i < 7; i++){
		res = regcomp(&regex[i], patterns[i], REG_EXTENDED);
		if (res){
			fprintf(stderr, "Could not compile regex\n");
			return -1;
		}
	
	
		res= regexec(&regex[i], string, 0, NULL, 0);
		if (res != 0 && res != REG_NOMATCH){
		regerror(res, &regex[i], buff, sizeof(buff));
			fprintf(stderr, "Regex match failed: %s\n", buff);
			abort();
		}
		else if (res == 0){
			regfree(&regex[i]);
			return i;
		}
		else if (res == REG_NOMATCH)	


		regfree(&regex[i]);
	}
	
	printf("Instruction <%s> is incorrect!\n", string);
	return -1;
}

void instr(int flag, char* string)
{
	unsigned command = 0;
	unsigned char cmd = 0;
	char* ptr = NULL;
	char reg, reg1, reg2;

	switch(flag){
		case 0:	
			ptr = strpbrk(string, "0123456789");
			command = (unsigned)atoi(ptr);
			cmd = command & 0xFF;			
			printf("0x%X\n", cmd);
		return;
		case 1:
			ptr = strchr(string, 'A') + 3;
			ptr = strpbrk(ptr, "ABCD");		
			reg1 = ptr[0] - 65;
			ptr = strpbrk(ptr+1, "ABCD");
			reg2 = ptr[0] - 65;

			command = (command | 1) << 5;
			command = (command | reg1) << 2;
	 		command = (command | reg2);
			cmd = command & 0xFF;

			printf("0x%X\n", cmd);
		return;
		case 2:
			ptr = strchr(string, 'S') + 3;
			ptr = strpbrk(ptr, "ABCD");		
			reg1 = ptr[0] - 65;
			ptr = strpbrk(ptr+1, "ABCD");
			reg2 = ptr[0] - 65;

			command = (((command | 1) << 3) | 0x1) << 2;
			command = (command | reg1) << 2;
	 		command = (command | reg2);
			cmd = command & 0xFF;
			printf("0x%X\n", cmd);
		return;
		case 3:
			ptr = strchr(string, 'M') + 3;
			ptr = strpbrk(ptr, "ABCD");		
			reg1 = ptr[0] - 65;
			ptr = strpbrk(ptr+1, "ABCD");
			reg2 = ptr[0] - 65;

			command = (((command | 1) << 3) | 0x2) << 2;
			command = (command | reg1) << 2;
 			command = (command | reg2);
			cmd = command & 0xFF;

			printf("0x%X\n", cmd);
		return;
		case 4:
			ptr = strchr(string, 'D') + 3;
			ptr = strpbrk(ptr, "ABCD");		
			reg1 = ptr[0] - 65;
			ptr = strpbrk(ptr+1, "ABCD");
			reg2 = ptr[0] - 65;

			command = (((command | 1) << 3) | 0x3) << 2;
			command = (command | reg1) << 2;
 			command = (command | reg2);
			cmd = command & 0xFF;
			printf("0x%X\n", cmd);
		return;
		case 5:
			ptr = strpbrk(strchr(string, 'I') + 2, "ABCD");
			reg = ptr[0] - 65;
				
			command = (command | 0x3) << 6;
			command = command | reg;
			cmd = command & 0xFF;
			printf("0x%X", cmd);
		return;
		case 6:
			ptr = strpbrk(strchr(string, 'O') + 3, "ABCD");
			reg = ptr[0] - 65;
				
			command = (((command | 0x3)<< 4) | 0x1) << 2;
			command = command | reg;
			cmd = command & 0xFF;
			printf("0x%X", cmd);
		return;
	}
}


int main(void)
{
	char string[max_length];
	int length;
	int res, flag;

	printf("Enter the comands on assembler (length less then %d) : \n", max_length);
	length = read_string(string, max_length);

	while(length > 0){
		flag = reg_match(string);

		if (flag == -1){
			fprintf(stderr, "Unsupported instruction!\n");
			return 2;
		}
		instr(flag, string);	
		length = read_string(string, max_length);
	}
	return 0;
}
