#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void rTypeDecode(char instruction[], int opcode);  //processes a r type instruction and prints the formatted results
char *registerDecode(int regNum);   //function to turn a integer value for the register into a string containing its name can be used for j and i type as well
char *functDecode(int functNum);    //function that turns an integer value for funct into the operation name in a string
int binaryToDecimal(int bin);       //converts a binary number into an integer

int main()
{
	char buffer[50], opcode[7];
	int opcodeNum;
	printf("Enter an instruction in machine code:\n");
	for(int i = 0; i < 32; i++)  //reading the machine code instruction into a char array buffer
	{
		buffer[i] = getchar();
		if(i < 6)                //storing the first 6 digits of the instruction into opcode char array to determine the type of instruction
			opcode[i] = buffer[i];
	}

	opcodeNum = binaryToDecimal(atoi(opcode));  //converting the decimal opcode into decimal to work with
	if(opcodeNum == 0)                          //all r type instructions have opcode of 0
		rTypeDecode(buffer,opcodeNum);
	/*else if(opcodeNum < 4)                     //of the instructions we consider all j type instructions have opcode of 3 or less
		jTypeDecode;
	else
		iTypeDecode;*/



}


void rTypeDecode(char instruction[], int opcode)   //passes in the read machine code in array instruction and the already converted int value opcode
{
	char temp1[6], temp2[6], temp3[6], temp4[6], temp5[7];  //arrays to store the char array for each field in the instruction for conversion with atoi
	for(int i = 6; i < 11; i++)
        temp1[i-6] = instruction[i];
    //temp1[5] = '\0';
    for(int i = 11; i < 16; i++)
        temp2[i-11] = instruction[i];             //iterating through the array and storing each part in their respective arrrays
    //temp2[5] = '\0';
    for(int i = 16; i < 21; i++)
        temp3[i-16] = instruction[i];
    //temp3[5] = '\0';
    for(int i = 21; i < 26; i++)
        temp4[i-21] = instruction[i];
    //temp4[5] = '\0';
    for(int i = 26; i < 32; i++)
        temp5[i-26] = instruction[i];
    //temp5[6] = '\0';

	printf("Instruction Type: R\n");               //for some reason changing a line of this breaks the whole function I don't understand this bit in the slightest
	int funct = binaryToDecimal(atoi(temp5));      //but it works, just don't ask me how I have no clue
	printf("%d :", funct);
	char *operation = functDecode(funct);
	printf("Operation: %s\n",operation);
	int rsNum = binaryToDecimal(atoi(temp1));
	char *rs = registerDecode(rsNum);
	printf("Rs: %s\n", rs);
	int rtNum = binaryToDecimal(atoi(temp2));
	char *rt = registerDecode(rtNum);
	printf("Rt: %s\n", rt);
    int rdNum = binaryToDecimal(atoi(temp3));
	char *rd = registerDecode(rdNum);
	printf("Rd: %s\n", rd);
	int shamt = binaryToDecimal(atoi(temp4));
	printf("Shamt: %d\n", shamt);
	funct = binaryToDecimal(atoi(temp5));
	printf("Funct: %d\n", funct);

}

char *registerDecode(int regNum)
{
	static char *reg;  //returns a char array
	if(regNum == 0)
		reg = "zero (R0)";   //uses the integer value to determine which register name to return
	else if(regNum == 1)
		reg = "at (R1)";
	else if(regNum == 2)
		reg = "v0 (R2)";
	else if(regNum == 3)
		reg = "v1 (R3)";
	else if(regNum == 4)
		reg = "a0 (R4)";
	else if(regNum == 5)
		reg = "a1 (R5)";
	else if(regNum == 6)
		reg = "a2 (R6)";
	else if(regNum == 7)
		reg = "a3 (R7)";
	else if(regNum == 8)
		reg = "t0 (R8)";
	else if(regNum == 9)
		reg = "t1 (R9)";
	else if(regNum == 10)
		reg = "t2 (R10)";
	else if(regNum == 11)
		reg = "t3 (R11)";
	else if(regNum == 12)
		reg = "t4 (R12)";
	else if(regNum == 13)
		reg = "t5 (R13)";
	else if(regNum == 14)
		reg = "t6 (R14)";
	else if(regNum == 15)
		reg = "t7 (R15)";
	else if(regNum == 16)
		reg = "s0 (R16)";
	else if(regNum == 17)
		reg = "s1 (R17)";
	else if(regNum == 18)
		reg = "s2 (R18)";
	else if(regNum == 19)
		reg = "s3 (R19)";
	else if(regNum == 20)
		reg = "s4 (R20)";
	else if(regNum == 21)
		reg = "s5 (R21)";
	else if(regNum == 22)
		reg = "s6 (R22)";
	else if(regNum == 23)
		reg = "s7 (R23)";
	else if(regNum == 24)
		reg = "t8 (R24)";
	else if(regNum == 25)
		reg = "t9 (R25)";
	else if(regNum == 26)
		reg = "k0 (R26)";
	else if(regNum == 27)
		reg = "k1 (R27)";
	else if(regNum == 28)
		reg = "gp (R28)";
	else if(regNum == 29)
		reg = "sp (R29)";
	else if(regNum == 30)
		reg = "fp (R30)";
	else if(regNum == 31)
		reg = "ra (R30)";
	else
		reg = "unknown";
	return reg;
}

char *functDecode(int functNum)
{
	static char *funct;        //performs the same actions as regDecode just with funct values
	if(functNum == 0)
		funct = "sll";
	else if(functNum == 2)
		funct = "srl";
	else if(functNum == 8)
		funct = "jr";
	else if(functNum == 32)
		funct = "add";
	else if(functNum == 33)
		funct = "addu";
	else if(functNum == 34)
		funct = "sub";
	else if(functNum == 35)
		funct = "subu";
	else if(functNum == 36)
		funct = "and";
	else if(functNum == 37)
		funct = "or";
	else if(functNum == 39)
		funct = "nor";
	else if(functNum == 42)
		funct = "slt";
	else if(functNum == 43)
		funct = "sltu";
	else
		funct = "unknown";
	return funct;
}

int binaryToDecimal(int bin)
{
	int dec;
	for(int i = 0; bin; i++, bin /= 10)
		if(bin % 10)
			dec += pow(2,i);
	return dec;