#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define rtypeopcodeposition 1
#define rtypeopcodelength 6
#define rtypefirstsourceregisterposition 7
#define rtypefirstsourceregisterlength 5
#define rtypesecondsourceregisterposition 12
#define rtypesecondsourceregisterlength 5
#define rtyperestinationregisterposition 17
#define rtypedestinationtrgisterlength 5
#define rtypeshiftamountposition 22
#define rtypeshiftamountlength 5
#define rtypefunctionposition 27
#define rtypefunctionlength 6
 

void setStr(char *c, const char * x)
{
    int i = 0;
    while(x[i] != '\0')
    {
        c[i] = x[i];
        i++;
    }
}
void decoderrtypesecondregister(char *rtypeinstruction,int position, int length)
{
   int dsecondpost = 0;
   char rtypesecondregister[33];
   for (size_t i = 0; i < strlen(rtypeinstruction); i++) {
    rtypeinstruction[i];   
  }

  printf("The value of original machine codeis %s\n",rtypeinstruction);
   while (dsecondpost < length) {
                           rtypesecondregister[dsecondpost] = rtypeinstruction[position + dsecondpost - 1];
                           dsecondpost++;
                       }
      rtypesecondregister[dsecondpost] = '\0';
 
   printf("Extracted rtypesecondregister code is \"%s\"\n",  rtypesecondregister); 
         int res = strcmp(rtypesecondregister,"01001"); 
         if(res==0)
         { 
           printf("Rt:t1(R9)\n");           
         }
  printf("The value of length is %d \n",length);
  
}
void decoderrtypedestinationregister(char *rtypeinstruction,int position, int length)
{
   for (size_t i = 0; i < strlen(rtypeinstruction); i++) {
    rtypeinstruction[i];   
  }

  printf("The value of original machine code is\n %s",rtypeinstruction);
  printf("The value of length is %d\n",length);
  
}
void decoderrtypeshiftamount(char *rtypeinstruction,int position, int length)
{
   for (size_t i = 0; i < strlen(rtypeinstruction); i++) {
    rtypeinstruction[i];   
  }

  printf("The value of original machine code is %s\n",rtypeinstruction);
  printf("The value of length is %d\n",length);
  
}
void decoderrtypefunction(char *rtypeinstruction,int position, int length)
{
   for (size_t i = 0; i < strlen(rtypeinstruction); i++) {
    rtypeinstruction[i];   
  }
 printf("The value of original machine code is %s\n",rtypeinstruction);
 printf("The value of length is %d\n",length);
}
void rinstructionTypedecoding(char *c, const char * x)
{
    int i = 0;   
    char machinecode[33], rtypeinstruction[33];
    char rtypesecondregister[6];
    int position, length;
    int d = 0, dpost = 0;

    while(x[i] != '\0')
    {
        c[i] = x[i]; 
         i++;    

    }     
       strcpy(machinecode,x);
       printf("The value of opcode bits are %s",machinecode); 
       //printf("Enter the position and length of to get the decoded for R-type instruction\n");
       //scanf("%d%d", &position, &length);
       while (d < rtypeopcodelength) {
                           rtypeinstruction[d] = machinecode[rtypeopcodeposition+d-1];
                           d++;
                       }
      rtypeinstruction[d] = '\0';
 
   printf("Extracted opcode is \"%s\"\n",  rtypeinstruction); 
         int res = strcmp(rtypeinstruction,"000000"); 
         if(res==0)
         { 
           printf("Instruction Type:R\n");
           printf("Operation:add\n");
         }

   while (dpost < rtypedestinationtrgisterlength) {
                           rtypeinstruction[dpost] = machinecode[rtypefirstsourceregisterposition + dpost - 1];
                           dpost++;
                       }
      rtypeinstruction[dpost] = '\0';
 
   printf("Extracted code for rtypefirstregister is \"%s\"\n",  rtypeinstruction); 
          res = strcmp(rtypeinstruction,"01000"); 
         if(res==0)
         { 
           printf("Rs:t0(R8)\n");           
         }
       
       decoderrtypesecondregister(machinecode,rtypesecondsourceregisterposition,rtypesecondsourceregisterlength);
       decoderrtypedestinationregister(machinecode,rtyperestinationregisterposition,rtypedestinationtrgisterlength);
       decoderrtypeshiftamount(machinecode,rtypeshiftamountposition,rtypeshiftamountlength);
       decoderrtypefunction(machinecode,rtypefunctionposition,rtypefunctionlength); 
}

void prepend(char* s, const char* t)
{
    size_t len = strlen(t);
    size_t i;
    memmove(s + len, s, strlen(s) + 1);
    for (i = 0; i < len; ++i)
    {
        s[i] = t[i];
    }
}

int main(int argc, char const *argv[])
{
    char *x = malloc(33*sizeof(char));  
    char str[33];
    char* pstr = str;
    const char* pcstr = pstr;
    printf("Welcome to MIPS decoder");
    printf("Enter an instruction in machine code : \n");
    fgets( pstr, 99, stdin );
   // puts( pcstr );
    //setStr(x, "00000001000010011000100000100000");
    setStr(x,pcstr);
    while (strlen(x) < 31) // To prepend 0 if entered group of bits is less than 32 bits
    {
        prepend(x,"0");
        printf("The macinne code is not R, I or J instruction %s\n"); 
    }
    printf("The group of 32 bits is %s\n", x);
    rinstructionTypedecoding(x,pcstr);
    int i = strtol(x,NULL,2);
    printf("The decimal value of entered machine code is %d\n",i);
    free(x);
    return 0;
}