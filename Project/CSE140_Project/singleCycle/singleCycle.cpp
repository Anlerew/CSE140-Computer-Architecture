#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

//initializing local variables.
int pc = 0;
int PCForward = 0;
int destinationBranch = 0;
int destinationJump = 0;
int ALUInit = 0;
int rotationSize = 0;
int PushRegister = 0;
int TargetRegister = 0;
int Branch = 0;
int ALUSource = 0;
int TypeInstruction = 0;
int PushMemory = 0;
int MemoryToRegister = 0;
int FetchFromMemory = 0;
int Jump = 0;
int FileName[32] = {0};
int MemoryArray[32] = {0};

// Function declaration from pdf.
string toStr(int value);
void Decode(string state);
void Execute(string aLUOp, string rt, string rs, string imm);
void Mem(string fetch, string rt, int data);
void Writeback(string rt, int value);
string Controlunit(string ins);
int toInt(string str);
void Fetch(string str) {
    PCForward = pc + 4;
    Decode(str);
}
/**
 * 
 * @param  {string} str : 
 */
void Decode(string str) {
    string tt = str.substr(0, 6);
    if (toInt(tt) == 2 || toInt(tt) == 3) {
        printf("\nInstruction Type: J");
        string temp = str.substr(0, 6);
        string mem = str.substr(6, 26);
        if (toInt(temp) == 2) {
            printf("\nOperation: j \n");
            printf("Target address: ");
            printf("%i", toInt(mem));
        }
        else {
            printf("\nOperation: UNONWN \n");
            printf("Target address: ");
            printf("%i", toInt(mem));
        }
    }
    else if (toInt(tt) == 0) {
        string rs = str.substr(6, 5);
        string rt = str.substr(11, 5);
        string rd = str.substr(16, 5);
        string ts = str.substr(21, 5);
        string t = str.substr(26, 6);
        if (toInt(t) == 42) {
            Execute(Controlunit(t), rd, rs, rt);
        }
        else if (toInt(t) == 34) {
            Execute(Controlunit(t), rd, rs, rt);
        }
        else {
            cout << "Unknown" << toInt(t) << endl;
        }
    }
    else {
        string ss = str.substr(0, 6);
        string rs = str.substr(6, 5);
        string rt = str.substr(11, 5);
        string mim = str.substr(16, 16);
        if (toInt(ss) == 4) {
            Execute(Controlunit(ss), rt, rs, mim);
        }
        else if (toInt(ss) == 43) {
            Execute(Controlunit(ss), rt, rs, mim);
        }
        else if (toInt(ss) == 35) {
            Execute(Controlunit(ss), rt, rs, mim);
        }
        else {
            printf(" Unknown");
        }
    }
}
/**
 * 
 * @param  {string} oa     : 
 * @param  {string} target : 
 * @param  {string} rs     : 
 * @param  {string} rimm   : 
 */
void Execute(string oa, string target, string rs, string rimm) {
    if (oa == "0010") {
        if (FetchFromMemory == 0 && TypeInstruction == 0) {
            int out = FileName[toInt(rs)] + toInt(rimm);
            Mem("sw", target, out);
        }
        else if (FetchFromMemory == 1 && TypeInstruction == 0) {
            int out = FileName[toInt(rs)] + toInt(rimm);
            Mem("lw", target, out);
        }
    }
    else if (oa == "0110") {
        if (Jump == 1 && TypeInstruction == 0) {
            int out = FileName[toInt(rs)] - FileName[toInt(rimm)];
            rotationSize = rotationSize + 1;
            cout << "\ntotal_clock_cycles " << rotationSize << " :" << endl;
            if (out == 0) {
                int sl2 = toInt(rimm);
                sl2 = sl2 << 2;
                destinationBranch = PCForward + sl2;
            }
            else {
                destinationBranch = PCForward;
            }
            pc = destinationBranch;
            stringstream ssp;
            ssp << hex << destinationBranch;
            string response = ssp.str();
            cout << "pc is modified to 0x" << response << endl;
        }
        else {
            int out = FileName[toInt(rs)] - FileName[toInt(rimm)];
            FileName[toInt(target)] = out;
            rotationSize = rotationSize + 1;
            cout << "\ntotal_clock_cycles " << rotationSize << " :" << endl;
            stringstream ss;
            ss << hex << FileName[toInt(target)];
            string res = ss.str();
            pc = PCForward;
            stringstream ssp;
            ssp << hex << pc;
            string response = ssp.str();
            cout << toStr(toInt(target)) << " is modified to 0x" << res << endl;
            cout << "pc is modified to 0x" << response << endl;
        }
    }
    else if (oa == "0111") {
        int out = 0;
        if (FileName[toInt(rs)] < FileName[toInt(rimm)]) {
            out = 1;
        }
        FileName[toInt(target)] = out;
        rotationSize = rotationSize + 1;
        cout << "\ntotal_clock_cycles " << rotationSize << " :" << endl;
        stringstream ss;
        ss << hex << FileName[toInt(target)];
        string res = ss.str();
        pc = PCForward;
        stringstream ssp;
        ssp << hex << pc;
        string response = ssp.str();
        cout << toStr(toInt(target)) << " is modified to 0x" << res << endl;
        cout << "pc is modified to 0x" << response << endl;
    }
    ALUInit = 1;
}
/**
 * 
 * @param  {string} fetch : 
 * @param  {string} rt    : 
 * @param  {int} data     : 
 */
void Mem(string fetch, string rt, int data) {
    if (fetch == "lw") {
        int value = MemoryArray[data / 4];
        Writeback(rt, value);
    }
    /**
     * 
     * @param  {fetch} == : "sw"
     * @return {else}     : 
     */
    else if (fetch == "sw") {
        int value = FileName[toInt(rt)];
        rotationSize = rotationSize + 1;
        cout << "\ntotal_clock_cycles " << rotationSize << " :" << endl;
        MemoryArray[data / 4] = value;
        stringstream ss;
        ss << hex << MemoryArray[data / 4];
        string res = ss.str();
        stringstream sd;
        sd << hex << data;
        string mres = sd.str();
        pc = PCForward;
        stringstream ssp;
        ssp << hex << pc;
        string response = ssp.str();
        cout << "memory 0x" << mres << " is modified to 0x" << res << endl;
        cout << "pc is modified to 0x" << response << endl;
    }
}
/**
 * 
 * @param  {string} rt : 
 * @param  {int} value : 
 */
void Writeback(string rt, int value) {
    rotationSize = rotationSize + 1;
    cout << "\ntotal_clock_cycles " << rotationSize << " :" << endl;
    FileName[toInt(rt)] = value;
    stringstream ss;
    ss << hex << FileName[toInt(rt)];
    string res = ss.str();
    pc = PCForward;
    stringstream ssp;
    ssp << hex << pc;
    string response = ssp.str();
    cout << toStr(toInt(rt)) << " is modified to 0x" << res << endl;
    cout << "pc is modified to 0x" << response << endl;
}
/**
 * 
 * @param  {string} ins : 
 * @return {string}     : 
 */
string Controlunit(string ins) {
    string ALUOp;
    if (toInt(ins) == 35) {
        TargetRegister = 0, 
        ALUSource = 1, 
        MemoryToRegister = 1, 
        PushRegister = 1, 
        FetchFromMemory = 1, 
        PushMemory = 0, Branch = 0;
        Jump = 0, TypeInstruction = 0;
        ALUOp = "0010";
    }
    else if (toInt(ins) == 34) {
        TargetRegister = 1, 
        ALUSource = 0, 
        MemoryToRegister = 0, 
        PushRegister = 1, 
        FetchFromMemory = 0, 
        PushMemory = 0, Branch = 0;
        Jump = 0, TypeInstruction = 0;
        ALUOp = "0110";
    }
    else if (toInt(ins) == 42) {
        TargetRegister = 1, 
        ALUSource = 0, 
        MemoryToRegister = 0, 
        PushRegister = 1, 
        FetchFromMemory = 0, 
        PushMemory = 0, Branch = 0;
        Jump = 0, TypeInstruction = 0;
        ALUOp = "0111";
    }
    else if (toInt(ins) == 4) {
        TargetRegister = 0, 
        ALUSource = 0, 
        MemoryToRegister = 0, 
        PushRegister = 0, 
        FetchFromMemory = 0, 
        PushMemory = 0, Branch = 1;
        Jump = 1, TypeInstruction = 0;
        ALUOp = "0110";
    }
    else if (toInt(ins) == 43) {
        TargetRegister = 0, 
        ALUSource = 1, 
        MemoryToRegister = 0, 
        PushRegister = 0, 
        FetchFromMemory = 0, 
        PushMemory = 1, Branch = 1;
        Jump = 0, TypeInstruction = 0;
        ALUOp = "0010";
    }
    return ALUOp;
}
/**
 * 
 * @param  {int} value : 
 * @return {string}    : 
 */
string toStr(int value) {
    string cc = (value == 0)? "$zero":
    (value == 1)? "$at":
    (value == 2)? "$v0":
    (value == 3)? "$v1":
    (value == 4)? "$a0":
    (value == 5)? "$a1":
    (value == 6)? "$a2":
    (value == 7)? "$a3":
    (value == 8)? "$t0":
    (value == 9)? "$t1":
    (value == 10)? "$t2":
    (value == 11)? "$t3":
    (value == 12)? "$t4":
    (value == 13)? "$t5":
    (value == 14)? "$t6":
    (value == 15)? "$t7":
    (value == 16)? "$s0":
    (value == 17)? "$s1":
    (value == 18)? "$s2":
    (value == 19)? "$s3":
    (value == 20)? "$s4":
    (value == 21)? "$s5":
    (value == 22)? "$s6":
    (value == 23)? "$s7":
    (value == 24)? "$t8":
    (value == 25)? "$t9":
    (value == 26)? "$k0":
    (value == 27)? "$k1":
    (value == 28)? "$gp":
    (value == 29)? "$sp":
    (value == 30)? "$fp":
    (value == 31)? "$ra":"Unknown";
    return cc;
}
/**
 * 
 * @param  {string} str : 
 * @return {int}        : 
 */
int toInt(string str) {
    char *begin = &str[0];
    int total = 0;
    while (*begin) {
        total *= 2;
        if (*begin++ == '1')
            total += 1;
    }
    return total;
}
/**
 * 
 * @return {int}  : 
 */
int main() {
    //Updating the location for the filename variable 
    //for the 32 character instruction.
    FileName[16] = 112;
    FileName[9] = 32;
    FileName[10] = 5;
    MemoryArray[29] = 16;
    MemoryArray[28] = 5;
    string state;int numLines = 0;
    ifstream fileReadSample("sample_binary.txt");
    while (getline(fileReadSample, state)) {
        ++numLines;
    }
    ifstream fileRead("sample_binary.txt");
    if (fileRead.is_open()) {
        for (int i = 0; getline(fileRead, state) && i < numLines; i++) {
            if (i == pc / 4) {
                Fetch(state);
            }
        }
        fileRead.close();
    }
    else
        cout << "Unable to open file";
    cout << "\nprogram terminated:\ntotal execution time is " << rotationSize << " cycles";
    return 0;
}
