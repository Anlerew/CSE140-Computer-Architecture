1. Command to compile the code:
    > gcc Decode.c -o decoder.exe
    > decoder.exe
2. /* For R Instruction type:
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
