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
 
/* For R Instruction type:
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
    > 100000 */


   