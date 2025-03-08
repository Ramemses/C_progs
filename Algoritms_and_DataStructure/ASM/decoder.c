#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int regs[] = {0, 0 ,0, 0};
enum regno{A = 0, B, C, D, RLAST};
enum operator{MOVI = 0, ADD = 8, SUB = 9, MUL = 10, DIV = 11, IN, OUT, OPLAST};

union operand{
	struct {int rx, rs;} ops;	
	int rop;
	int imm;
};

struct operation{
	enum operator opr;
	union operand opnd;
};


struct operation decode_command(unsigned char cmd)
{
	struct operation instr;
	if ((cmd >> 7) == 0){
		instr.opr = MOVI;
		instr.opnd.imm = cmd;
		return instr;
	}

	if (((cmd >> 6) & 1) == 1 ){
		if ((cmd >> 2) == 0x31) instr.opr = OUT;
		if ((cmd >> 2) == 0x30) instr.opr = IN;	
		instr.opnd.rop = cmd & 0x3;
		return instr;
	}
	if ( (cmd >> 4) <= 0xB && (cmd >> 4) >= 0x8){
		instr.opr = (cmd >> 0x4) & 0xFF;
		instr.opnd.ops.rs = cmd & 0x3;
		instr.opnd.ops.rx = (cmd >> 2) & 0x3;
		return instr;
	}


	fprintf(stderr, "Unrecognised operation!\n");
	abort();
}


void print_operation(struct operation oper)
{
	char reg_arr[] = {'A', 'B' ,'C', 'D'};	
	switch(oper.opr){
		case MOVI:
			printf("MOVI D %u\n", oper.opnd.imm);
			break;
		case IN:
			printf("IN %c\n", reg_arr[oper.opnd.rop]);
			break;
		case OUT:
			printf("OUT %c\n", reg_arr[oper.opnd.rop]);
			break;
		case ADD:
			printf("ADD %c, %c\n", reg_arr[oper.opnd.ops.rx], reg_arr[oper.opnd.ops.rs]);
			break;
		case SUB:
			printf("SUB %c, %c\n", reg_arr[oper.opnd.ops.rx], reg_arr[oper.opnd.ops.rs]);
			break;
		case MUL:
			printf("MUL %c, %c\n", reg_arr[oper.opnd.ops.rx], reg_arr[oper.opnd.ops.rs]);
			break;
		case DIV:
			printf("DIV %c, %c\n", reg_arr[oper.opnd.ops.rx], reg_arr[oper.opnd.ops.rs]);
			break;
		default:
			fprintf(stderr, "Unsupported operation!\n");
			abort();
			break;
	}

}




int main(int args, char** argv)
{

	unsigned x;
	int res;
	res = scanf("%x", &x);
	if (res != 1){
		fprintf(stderr, "Error input!\n");
		return 1;
	}
	


	while (res == 1){
		struct operation oper;
		unsigned char cmd = x & 0xFF;
		assert(cmd == x);

		oper = decode_command(cmd);		
		print_operation(oper);

		res = scanf("%x", &x);
	}
	

	return 0;
}
