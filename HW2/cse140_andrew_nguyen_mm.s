# Traditional Matrix Multiply program
		.data
matrix_a:
		.word   1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12
		.word  13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24
		.word  25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36
		.word  37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48
		.word  49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60
		.word  61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72
		.word  73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84
		.word  85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96
		.word  97, 98, 99,100,101,102,103,104,105,106,107,108
		.word 109,110,111,112,113,114,115,116,117,118,119,120
		.word 121,122,123,124,125,126,127,128,129,130,131,132
		.word 133,134,135,136,137,138,139,140,141,142,143,144

matrix_b:
		.word 133,134,135,136,137,138,139,140,141,142,143,144
		.word 121,122,123,124,125,126,127,128,129,130,131,132
		.word 109,110,111,112,113,114,115,116,117,118,119,120
		.word  97, 98, 99,100,101,102,103,104,105,106,107,108
		.word  85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96
		.word  73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84
		.word  61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72
		.word  49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60
		.word  37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48
		.word  25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36
		.word  13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24
		.word   1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12

matrix_c:
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		.word   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0

bs:		.word 3
n:		.word 12

nline:  .asciiz "\n"				#Define new line string
sp:		.asciiz " "
msga: 	.asciiz "Matrix A is: \n"
msgb: 	.asciiz "Matrix B is: \n"
msgc: 	.asciiz "Matrix C=A*B is: \n"

		.text
		.globl main
main:

		la	$s0, bs	
		lw	$s0, 0($s0)
		la	$s1, n
		lw	$s1, 0($s1)
		la	$s2, matrix_a
		la	$s3, matrix_b
		la	$s4, matrix_c

		la	$a0, msga
		la 	$a1, matrix_a
		jal	PRINT_MAT 
		la	$a0, msgb
		la 	$a1, matrix_b
		jal	PRINT_MAT 

# Your CODE HERE
incrementk:
    		addi $s7, $s7, 1                        #increment k by 1
    		j forloopk                              #go to next forloop of k

forloopk:
    		beq  $s7, $s1, incrementj               #If k equals n increment j by 1, else
    		j multiply                              #go to multiply

incrementj:
    		addi $s6, $s6, 1                        #increment j by 1
    		j forloopj                              #go to next forloop of j

forloopj:
    		beq  $s6, $s1, incrementi               #If j equals n increment i by 1, else
    		addi $s7, $zero, 0
    		j forloopk                              #go to next forloop of k
    
incrementi:
    		addi $s5, $s5, 1                        #increment i by 1
    		j forloopi                              #go to next forloop of i
    
forloopi:
    		beq  $s5, $s1, PRINT_MAT                #If i equals n display result else,
    		addi $s6, $zero, 0
    		j forloopj                              #go to next for loop j
                                    
 multiply:
    		mul  $t0, $s1, $s5                      #t0 = n*i
    		add  $t0, $t0, $s7
    		mul  $t0, $t0, 4
    		add $t0,$t0 ,$s2                        #t0 = t0 + k  
    		lw   $t4, 0($t0)                        #t4 = A[n*i+k]
  
    		mul $t1, $s1, $s7                       #t1 = n*k
    		add  $t1, $t1, $s6                      #t1 = t1 + j    
    		mul  $t1, $t1, 4
    		add $t1, $t1, $s3
    		lw   $t5, 0($t1)                        #t5 = B[n*k+j]
    		
    		mul $t2, $s1, $s6			#t2 = n*j
    		add $t2, $t2, $s5			#t2 = t2 + i
    		mul $t2, $t2, 4
    		add $t2, $t2, $s4
    		lw $t6, 0($t2)				#t6 = C[n*j+i]
    		
    
    		mul $t7, $t4, $t5                       #t1= A[n*i+k] * B[n*k+j]
    		add $t7, $t6, $t7			#t1 = C[n*j+i] +[A[n*i+k] * B[n*k+j]]
    
    		mul $t2, $s1, $s5                       #t2 = n*i
    		add  $t2, $t2, $s6                      #t2 = (n*i)+j  
    		mul  $t2, $t2, 4
    		add $t2, $t2, $s4
    		lw   $t3, 0($t2)
    		
    		add $t3, $t3, $t7
    		sw $t3, 0($t2)
    
    		j incrementk                            #go to next forloop of k
    		
    		# I feel like I was on the right track but can't seem to add the C to the A times B for some reason. I don't necessarily know what exactly I'm doing wrong but I at leasts got it to print A time B


# End CODE

		la	$a0, msgc
		la 	$a1, matrix_c
		jal	PRINT_MAT 

#   Exit
		li	 $v0,10
    	syscall


PRINT_MAT:	li	$v0,4
		syscall
		addi $a2,$0,0	
PL4:	bge	$a2,$s1,PL1
		addi $a3,$0,0
PL3:	bge	$a3,$s1,PL2

		lw	$a0,0($a1)
		li	$v0,1
		syscall
		la	$a0,sp
		li	$v0,4
		syscall
		addi $a1,$a1,4
		addi $a3,$a3,1
		b 	PL3

PL2:	addi	$a2,$a2,1
		la	$a0,nline
		li	$v0,4
		syscall
		b	PL4
PL1:	jr	$ra
