//HW 3 CSE 140 ANDREW NGUYEN & VINCENT ZHANG
/*
Write a C program (Decode.c) that decodes an input machine instruction.
Your program needs to be able to decode the R, I, and J type instructions listed below. 
We will only test the following instructions.
When the program is started, your program will print “Enter an instruction in machine code:” and receive num1 32-bit machine code from user. 
Then, the program will decode the machine code and print the information (type and values of individual fields of the instruction format) of the instruction. 
The followings are the example execution of the program. 
Your program must produce the following sample results in the exact same format.

The instruction format: R, I, or J

The opcode

The Rs, Rt, and Rd, register numbers

The immediate value, if any

The jump address, if any
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *reg_num[32] = 
{   //Establish register numbers
    "R0",
	"R1",
	"R2",
	"R3",
	"R4",
	"R5",
	"R6",
	"R7",
	"R8",
	"R9",
	"R10",
	"R11",
	"R12",
	"R13",
	"R14",
	"R15",
	"R16",
	"R17",
	"R18",
	"R19",
	"R20",
	"R21",
	"R22",
	"R23",
	"R24",
	"R25",
	"R26",
	"R27",
	"R28",
	"R29",
	"R30",
	"R31" 
};
const char *reg_name[32] = 
{   //Establish register names for all the registers such as the temporary registers
    "zero",
	"at",
	"v0",
	"v1",
	"a0",
	"a1",
	"a2",
	"a3",
	"t0",
	"t1",
	"t2",
	"t3",
	"t4",
	"t5",
	"t6",
	"t7",
	"s0",
	"s1",
	"s2",
	"s3",
	"s4",
	"s5",
	"s6",
	"s7",
	"t8",
	"t9",
	"k0",
	"k1",
	"gp",
	"sp",
	"fp",
	"ra" 
};

int conv_five(int num5, int num4, int num3, int num2, int num1) 
{
	int point = 0;

	if (num5 == 1)
	{
		point = point + 16;
	}

	if (num4 == 1)
	{
		point = point + 8;
	}

	if (num3 == 1)
	{
		point = point + 4;
	}

	if (num2 == 1)
	{
		point = point + 2;
	}

	if (num1 == 1)
	{
		point = point + 1;
	}
	else
	{
		point = point;
	}

	return point;
} // converts the 5 digits of machine code into decimal point values of 2^n and then saves the value of the point

int conv_six(int num6, int num5, int num4, int num3, int num2, int num1)
{
	int point = 0;

	if (num6 == 1)
	{
		point = point + 32;
	}

	if (num5 == 1)
	{
		point = point + 16;
	}

	if (num4 == 1)
	{
		point = point + 8;
	}

	if (num3 == 1)
	{
		point = point + 4;
	}

	if (num2 == 1)
	{
		point = point + 2;
	}

	if (num1 == 1)
	{
		point = point + 1;
	}
	else
	{
		point = point;
	}

	return point;
}// converts the 6 digits of machine code into decimal point values 2^n and then saves the value of the point

int conv_sixteen(int num16, int num15, int num14, int num13, int num12, int num11, int num10, int num9, int num8, int num7, int num6, int num5, int num4, int num3, int num2, int num1)
{
	int point = 0;

	if (num16 == 1)
	{
		point = point + 32768;
	}

	if (num15 == 1)
	{
		point = point + 16384;
	}

	if (num14 == 1)
	{
		point = point + 8192;
	}

	if (num13 == 1)
	{
		point = point + 4096;
	}

	if (num12 == 1)
	{
		point = point + 2048;
	}

	if (num11 == 1)
	{
		point = point + 1024;
	}

	if (num10 == 1)
	{
		point = point + 512;
	}

	if (num9 == 1)
	{
		point = point + 256;
	}

	if (num8 == 1)
	{
		point = point + 128;
	}

	if (num7 == 1)
	{
		point = point + 64;
	}

	if (num6 == 1)
	{
		point = point + 32;
	}

	if (num5 == 1)
	{
		point = point + 16;
	}

	if (num4 == 1)
	{
		point = point + 8;
	}

	if (num3 == 1)
	{
		point = point + 4;
	}

	if (num2 == 1)
	{
		point = point + 2;
	}

	if (num1 == 1)
	{
		point = point + 1;
	}
	else
	{
		point = point;
	}

	return point;
} // converts the 16 digits of machine code into decimal point values 2^n and then saves the value of the point

int conv_twentysix(int num26, int num25, int num24, int num23, int num22, int num21, int num20, int num19, int num18, int num17, int num16, int num15, int num14, int num13, int num12, int num11, int num10, int num9, int num8, int num7, int num6, int num5, int num4, int num3, int num2, int num1)
{
	int point = 0;

	if (num26 == 1)
	{
		point = point + 33554432;
	}

	if (num25 == 1)
	{
		point = point + 16777216;
	}

	if (num24 == 1)
	{
		point = point + 8388608;
	}

	if (num23 == 1)
	{
		point = point + 4194304;
	}

	if (num22 == 1)
	{
		point = point + 2097152;
	}

	if (num21 == 1)
	{
		point = point + 1048576;
	}

	if (num20 == 1)
	{
		point = point + 524288;
	}

	if (num19 == 1)
	{
		point = point + 262144;
	}

	if (num18 == 1)
	{
		point = point + 131072;
	}

	if (num17 == 1)
	{
		point = point + 65536;
	}

	if (num16 == 1)
	{
		point = point + 32768;
	}

	if (num15 == 1)
	{
		point = point + 16384;
	}

	if (num14 == 1)
	{
		point = point + 8192;
	}

	if (num13 == 1)
	{
		point = point + 4096;
	}

	if (num12 == 1)
	{
		point = point + 2048;
	}

	if (num11 == 1)
	{
		point = point + 1024;
	}

	if (num20 == 1)
	{
		point = point + 512;
	}

	if (num9 == 1)
	{
		point = point + 256;
	}

	if (num8 == 1)
	{
		point = point + 128;
	}

	if (num7 == 1)
	{
		point = point + 64;
	}

	if (num6 == 1)
	{
		point = point + 32;
	}

	if (num5 == 1)
	{
		point = point + 16;
	}

	if (num4 == 1)
	{
		point = point + 8;
	}

	if (num3 == 1)
	{
		point = point + 4;
	}

	if (num2 == 1)
	{
		point = point + 2;
	}

	if (num1 == 1)
	{
		point = point + 1;
	}
	else
	{
		point = point;
	}

	return point;
} // converts the 26 digits of machine code into decimal point values 2^n and then saves the value of the point

int r_type(int bin[]) 
{
	int op = conv_six(bin[0], bin[1], bin[2], bin[3], bin[4], bin[5]);
	if (op == 0)
	{ // checks to see if it is an r type instruction
		int funct = conv_six(bin[26], bin[27], bin[28], bin[29], bin[30], bin[31]);
		if (funct = 32)
		{
			printf("instruction type: R\n");
			printf("operation: add\n");
			int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
			printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
			int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
			printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
			int rd = conv_five(bin[16], bin[17], bin[18], bin[19], bin[20]);
			printf("rd: %s (%s)\n", reg_name[rd], reg_num[rd]);
			int shamt = conv_five(bin[21], bin[22], bin[23], bin[24], bin[25]);
			printf("shamt: %d\n", shamt);
			printf("funct: %d\n", funct);
		}
		else if (funct == 33)
		{
			printf("instruction type: R\n");
			printf("operation: addu\n");
			int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
			printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
			int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
			printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
			int rd = conv_five(bin[16], bin[17], bin[18], bin[19], bin[20]);
			printf("rd: %s (%s)\n", reg_name[rd], reg_num[rd]);
			int shamt = conv_five(bin[21], bin[22], bin[23], bin[24], bin[25]);
			printf("shamt: %d\n", shamt);
			printf("funct: %d\n", funct);
		}
		else if (funct == 36)
		{
			printf("instruction type: R\n");
			printf("operation: and\n");
			int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
			printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
			int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
			printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
			int rd = conv_five(bin[16], bin[17], bin[18], bin[19], bin[20]);
			printf("rd: %s (%s)\n", reg_name[rd], reg_num[rd]);
			int shamt = conv_five(bin[21], bin[22], bin[23], bin[24], bin[25]);
			printf("shamt: %d\n", shamt);
			printf("funct: %d\n", funct);
		}
		else if (funct == 8)
		{
			printf("instruction type: R\n");
			printf("operation: jr\n");
			int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
			printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
			int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
			printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
			int rd = conv_five(bin[16], bin[17], bin[18], bin[19], bin[20]);
			printf("rd: %s (%s)\n", reg_name[rd], reg_num[rd]);
			int shamt = conv_five(bin[21], bin[22], bin[23], bin[24], bin[25]);
			printf("shamt: %d\n", shamt);
			printf("funct: %d\n", funct);
		}
		else if (funct == 39)
		{
			printf("instruction type: R\n");
			printf("operation: nor\n");
			int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
			printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
			int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
			printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
			int rd = conv_five(bin[16], bin[17], bin[18], bin[19], bin[20]);
			printf("rd: %s (%s)\n", reg_name[rd], reg_num[rd]);
			int shamt = conv_five(bin[21], bin[22], bin[23], bin[24], bin[25]);
			printf("shamt: %d\n", shamt);
			printf("funct: %d\n", funct);
		}
		else if (funct == 37)
		{
			printf("instruction type: R\n");
			printf("operation: or\n");
			int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
			printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
			int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
			printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
			int rd = conv_five(bin[16], bin[17], bin[18], bin[19], bin[20]);
			printf("rd: %s (%s)\n", reg_name[rd], reg_num[rd]);
			int shamt = conv_five(bin[21], bin[22], bin[23], bin[24], bin[25]);
			printf("shamt: %d\n", shamt);
			printf("funct: %d\n", funct);
		}
		else if (funct == 42)
		{
			printf("instruction type: R\n");
			printf("operation: slt\n");
			int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
			printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
			int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
			printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
			int rd = conv_five(bin[16], bin[17], bin[18], bin[19], bin[20]);
			printf("rd: %s (%s)\n", reg_name[rd], reg_num[rd]);
			int shamt = conv_five(bin[21], bin[22], bin[23], bin[24], bin[25]);
			printf("shamt: %d\n", shamt);
			printf("funct: %d\n", funct);
		}
		else if (funct == 43)
		{
			printf("instruction type: R\n");
			printf("operation: sltu\n");
			int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
			printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
			int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
			printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
			int rd = conv_five(bin[16], bin[17], bin[18], bin[19], bin[20]);
			printf("rd: %s (%s)\n", reg_name[rd], reg_num[rd]);
			int shamt = conv_five(bin[21], bin[22], bin[23], bin[24], bin[25]);
			printf("shamt: %d\n", shamt);
			printf("funct: %d\n", funct);
		}
		else if (funct == 0)
		{
			printf("instruction type: R\n");
			printf("operation: sll\n");
			int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
			printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
			int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
			printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
			int rd = conv_five(bin[16], bin[17], bin[18], bin[19], bin[20]);
			printf("rd: %s (%s)\n", reg_name[rd], reg_num[rd]);
			int shamt = conv_five(bin[21], bin[22], bin[23], bin[24], bin[25]);
			printf("shamt: %d\n", shamt);
			printf("funct: %d\n", funct);
		}
		else if (funct == 2)
		{
			printf("instruction type: R\n");
			printf("operation: srl\n");
			int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
			printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
			int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
			printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
			int rd = conv_five(bin[16], bin[17], bin[18], bin[19], bin[20]);
			printf("rd: %s (%s)\n", reg_name[rd], reg_num[rd]);
			int shamt = conv_five(bin[21], bin[22], bin[23], bin[24], bin[25]);
			printf("shamt: %d\n", shamt);
			printf("funct: %d\n", funct);
		}
		else if (funct == 34)
		{
			printf("instruction type: R\n");
			printf("operation: sub\n");
			int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
			printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
			int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
			printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
			int rd = conv_five(bin[16], bin[17], bin[18], bin[19], bin[20]);
			printf("rd: %s (%s)\n", reg_name[rd], reg_num[rd]);
			int shamt = conv_five(bin[21], bin[22], bin[23], bin[24], bin[25]);
			printf("shamt: %d\n", shamt);
			printf("funct: %d\n", funct);
		}
		else if (funct == 35)
		{
			printf("instruction type: R\n");
			printf("operation: subu\n");
			int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
			printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
			int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
			printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
			int rd = conv_five(bin[16], bin[17], bin[18], bin[19], bin[20]);
			printf("rd: %s (%s)\n", reg_name[rd], reg_num[rd]);
			int shamt = conv_five(bin[21], bin[22], bin[23], bin[24], bin[25]);
			printf("shamt: %d\n", shamt);
			printf("funct: %d\n", funct);
		}
		return 0;
	}
	else
	{
		return 0;
	}
}

int i_type(int bin[])
{	// checks if it is i type instruction
	int op = conv_six(bin[0], bin[1], bin[2], bin[3], bin[4], bin[5]);
	if (op == 8)
	{
		printf("instruction type: I\n");
		printf("operation (opcode): addi\n");
		int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
		printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
		int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
		printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
		int immediate = conv_sixteen(bin[16], bin[17], bin[18], bin[19], bin[20], bin[21], bin[22], bin[23], bin[24], bin[25], bin[26], bin[27], bin[28], bin[29], bin[30], bin[31]);
		printf("immediate: %d\n", immediate);
	}
	else if (op == 9)
	{
		printf("instruction type: I\n");
		printf("operation (opcode): addiu");
		int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
		printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
		int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
		printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
		int immediate = conv_sixteen(bin[16], bin[17], bin[18], bin[19], bin[20], bin[21], bin[22], bin[23], bin[24], bin[25], bin[26], bin[27], bin[28], bin[29], bin[30], bin[31]);
		printf("immediate: %d\n", immediate);
	}
	else if (op == 12)
	{
		printf("instruction type: I\n");
		printf("operation (opcode): andi\n");
		int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
		printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
		int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
		printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
		int immediate = conv_sixteen(bin[16], bin[17], bin[18], bin[19], bin[20], bin[21], bin[22], bin[23], bin[24], bin[25], bin[26], bin[27], bin[28], bin[29], bin[30], bin[31]);
		printf("immediate: %d\n", immediate);
	}
	else if (op == 4)
	{
		printf("instruction type: I\n");
		printf("operation (opcode): beq\n");
		int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
		printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
		int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
		printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
		int immediate = conv_sixteen(bin[16], bin[17], bin[18], bin[19], bin[20], bin[21], bin[22], bin[23], bin[24], bin[25], bin[26], bin[27], bin[28], bin[29], bin[30], bin[31]);
		printf("immediate: %d\n", immediate);
	}
	else if (op == 5)
	{
		printf("instruction type: I\n");
		printf("operation (opcode): bne\n");
		int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
		printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
		int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
		printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
		int immediate = conv_sixteen(bin[16], bin[17], bin[18], bin[19], bin[20], bin[21], bin[22], bin[23], bin[24], bin[25], bin[26], bin[27], bin[28], bin[29], bin[30], bin[31]);
		printf("immediate: %d\n", immediate);
	}
	else if (op == 36)
	{
		printf("instruction type: I\n");
		printf("operation (opcode): lbu\n");
		int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
		printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
		int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
		printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
		int immediate = conv_sixteen(bin[16], bin[17], bin[18], bin[19], bin[20], bin[21], bin[22], bin[23], bin[24], bin[25], bin[26], bin[27], bin[28], bin[29], bin[30], bin[31]);
		printf("immediate: %d\n", immediate);
	}
	else if (op == 37)
	{
		printf("instruction type: I\n");
		printf("operation (opcode): lhu\n");
		int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
		printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
		int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
		printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
		int immediate = conv_sixteen(bin[16], bin[17], bin[18], bin[19], bin[20], bin[21], bin[22], bin[23], bin[24], bin[25], bin[26], bin[27], bin[28], bin[29], bin[30], bin[31]);
		printf("immediate: %d\n", immediate);
	}
	else if (op == 48)
	{
		printf("instruction type: I\n");
		printf("operation (opcode): ll\n");
		int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
		printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
		int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
		printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
		int immediate = conv_sixteen(bin[16], bin[17], bin[18], bin[19], bin[20], bin[21], bin[22], bin[23], bin[24], bin[25], bin[26], bin[27], bin[28], bin[29], bin[30], bin[31]);
		printf("immediate: %d\n", immediate);
	}
	else if (op == 15)
	{
		printf("instruction type: I\n");
		printf("operation (opcode): lui\n");
		int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
		printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
		int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
		printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
		int immediate = conv_sixteen(bin[16], bin[17], bin[18], bin[19], bin[20], bin[21], bin[22], bin[23], bin[24], bin[25], bin[26], bin[27], bin[28], bin[29], bin[30], bin[31]);
		printf("immediate: %d\n", immediate);
	}
	else if (op == 35)
	{
		printf("instruction type: I\n");
		printf("operation (opcode): lw\n");
		int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
		printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
		int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
		printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
		int immediate = conv_sixteen(bin[16], bin[17], bin[18], bin[19], bin[20], bin[21], bin[22], bin[23], bin[24], bin[25], bin[26], bin[27], bin[28], bin[29], bin[30], bin[31]);
		printf("immediate: %d\n", immediate);
	}
	else if (op == 13)
	{
		printf("instruction type: I\n");
		printf("operation (opcode): ori\n");
		int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
		printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
		int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
		printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
		int immediate = conv_sixteen(bin[16], bin[17], bin[18], bin[19], bin[20], bin[21], bin[22], bin[23], bin[24], bin[25], bin[26], bin[27], bin[28], bin[29], bin[30], bin[31]);
		printf("immediate: %d\n", immediate);
	}
	else if (op == 10)
	{
		printf("instruction type: I\n");
		printf("operation (opcode): slti\n");
		int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
		printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
		int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
		printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
		int immediate = conv_sixteen(bin[16], bin[17], bin[18], bin[19], bin[20], bin[21], bin[22], bin[23], bin[24], bin[25], bin[26], bin[27], bin[28], bin[29], bin[30], bin[31]);
		printf("immediate: %d\n", immediate);
	}
	else if (op == 11)
	{
		printf("instruction type: I\n");
		printf("operation (opcode): sltiu\n");
		int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
		printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
		int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
		printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
		int immediate = conv_sixteen(bin[16], bin[17], bin[18], bin[19], bin[20], bin[21], bin[22], bin[23], bin[24], bin[25], bin[26], bin[27], bin[28], bin[29], bin[30], bin[31]);
		printf("immediate: %d\n", immediate);
	}
	else if (op == 40)
	{
		printf("instruction type: I\n");
		printf("operation (opcode): sb\n");
		int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
		printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
		int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
		printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
		int immediate = conv_sixteen(bin[16], bin[17], bin[18], bin[19], bin[20], bin[21], bin[22], bin[23], bin[24], bin[25], bin[26], bin[27], bin[28], bin[29], bin[30], bin[31]);
		printf("immediate: %d\n", immediate);
	}
	else if (op == 56)
	{
		printf("instruction type: I\n");
		printf("operation (opcode): sc\n");
		int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
		printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
		int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
		printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
		int immediate = conv_sixteen(bin[16], bin[17], bin[18], bin[19], bin[20], bin[21], bin[22], bin[23], bin[24], bin[25], bin[26], bin[27], bin[28], bin[29], bin[30], bin[31]);
		printf("immediate: %d\n", immediate);
	}
	else if (op == 41)
	{
		printf("instruction type: I\n");
		printf("operation (opcode): sh\n");
		int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
		printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
		int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
		printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
		int immediate = conv_sixteen(bin[16], bin[17], bin[18], bin[19], bin[20], bin[21], bin[22], bin[23], bin[24], bin[25], bin[26], bin[27], bin[28], bin[29], bin[30], bin[31]);
		printf("immediate: %d\n", immediate);
	}
	else if (op == 43)
	{
		printf("instruction type: I\n");
		printf("operation (opcode): sw\n");
		int rs = conv_five(bin[6], bin[7], bin[8], bin[9], bin[10]);
		printf("rs: %s (%s)\n", reg_name[rs], reg_num[rs]);
		int rt = conv_five(bin[11], bin[12], bin[13], bin[14], bin[15]);
		printf("rt: %s (%s)\n", reg_name[rt], reg_num[rt]);
		int immediate = conv_sixteen(bin[16], bin[17], bin[18], bin[19], bin[20], bin[21], bin[22], bin[23], bin[24], bin[25], bin[26], bin[27], bin[28], bin[29], bin[30], bin[31]);
		printf("immediate: %d\n", immediate);
	}
	else
	{
		return 0;
	}
}

int j_type(int bin[])
{	//checks if its a j type instruction
	int op = conv_six(bin[0], bin[1], bin[2], bin[3], bin[4], bin[5]);
	if (op == 2)
	{
		printf("instruction type: J\n");
		printf("operation: j\n");
		int address = conv_twentysix(bin[6], bin[7], bin[8], bin[9], bin[10], bin[11], bin[12], bin[13], bin[14], bin[15], bin[16], bin[17], bin[18], bin[19], bin[20], bin[21], bin[22], bin[23], bin[24], bin[25], bin[26], bin[27], bin[28], bin[29], bin[30], bin[31]);
		printf("address: %d\n", address);
	}
	else if (op == 3)
	{
		printf("instruction type: J\n");
		printf("operation: jal\n");
		int address = conv_twentysix(bin[6], bin[7], bin[8], bin[9], bin[10], bin[11], bin[12], bin[13], bin[14], bin[15], bin[16], bin[17], bin[18], bin[19], bin[20], bin[21], bin[22], bin[23], bin[24], bin[25], bin[26], bin[27], bin[28], bin[29], bin[30], bin[31]);
		printf("address: %d\n", address);
	}
	else
	{
		return 0;
	}
	return 0;
}

int main(int argc, char **argv)
{
	int bin[32];	//allocating spots for the machine code
	char word[32];	//breaking up the user input as a char
	printf("enter an instruction in machine code:\n");
	scanf("%s",word);	//converts to digits but reads as words
	for (int i = 0; i < 32; i++)
	{
		bin[i] = word[i] - '0';	//convert the char into a digits
	}
	printf("\n");
	r_type(bin);
	i_type(bin);
	j_type(bin);
	return 0;
}

#include <math.h>
#include<stdio.h>
#include <stdlib.h>
int convertbinarytodecimal(long long n);
char* convertLongToChar(long long N);
int main()
{
long long n;
int len = 5;
printf("Welcome to MIPS decoder");
printf("Enter an instruction in machine code : \n");
scanf("%lld", &n); 
printf("The long long value is %lld", n);

printf("%lld in binary = %d in decimal", n, convertbinarytodecimal(n));
int nconvert =   convertbinarytodecimal(n);  
  // Function call
   char* arr = convertLongToChar(nconvert); 
    // Print char array
    for (int i = 0; i < len; i++)
      {
        printf("%c, ", arr[i]);
      }  
return 0;
}

int convertbinarytodecimal(long long n) {
    int dec = 0, i = 0, rem;   
    
    while (n != 0) {
        rem = n % 10;
        n /= 10;
        dec += rem * pow(2, i);
        ++i;
    }
    return dec;
}
// Function to convert long long to
// character array
char* convertLongToChar(long long N)
{
 
    // Count digits in number N
    long long m = N;
    int digit = 0;
    while (m) {
 
        // Increment number of digits
        digit++;
 
        // Truncate the last
        // digit from the number
        m /= 10;
    }
 
    // Declare char array for result
    char* arr;
 
    // Declare duplicate char array
    char arr1[digit];
 
    // Memory allocaton of array
    arr = (char*)malloc(digit);
 
    // Separating integer into digits and
    // accomodate it to character array
    int index = 0;
    while (N) {
 
        // Separate last digit from
        // the number and add ASCII
        // value of character '0' is 48
        arr1[++index] = N % 10 + '0';
 
        // Truncate the last
        // digit from the number
        N /= 10;
    }
 
    // Reverse the array for result
    int i;
    for (i = 0; i < index; i++) {
        arr[i] = arr1[index - i];
    }
 
    // Char array truncate by null
    arr[i] = '\0';
 
    // Return char array
    return (char*)arr;
}
 
/*For R Instruction type:
 a. First 6 bits: opcode
     > 000000
 b. Next 5 bits-rs
    > 01000 -8
 c. Next 5 bits-rt
    > 01001 -9
 d. Next 5 bits-rd
    > 10001 -17
 e. Next 5 bits-shamt
    > 00000
 f. next 6 bits-funct
    > 100000 
*/
   