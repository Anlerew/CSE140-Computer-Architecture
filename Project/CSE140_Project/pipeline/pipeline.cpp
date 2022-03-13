#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <map>
#include <sstream>
#include <iterator>
using namespace std;

long long int binDeci(string bin) {
    char *pEnd;
    long long int ull = strtoull(bin.c_str(), &pEnd, 2);
    return ull;
}

class Instructions {
public:
    bool operator==(const int &rhs) const;
    virtual void toPush(long data[32], unordered_map<long long int, long long int> varr){};
    virtual void consoleDisplay(long data[32], unordered_map<long long int, long long int> varr){};
    virtual void init(long data[32], unordered_map<long long int, long long int> varr, unsigned int &pc){};
    unsigned int str2int(const char *input, int h) {
        return !input[h] ? 5381 : (str2int(input, h + 1) * 33) ^ input[h];
    }
    virtual long long int fetchStateR() = 0;
    virtual long long int fetchStateT() = 0;
    virtual long long int fetchStateD() = 0;
    virtual ~Instructions(){};
};
class RegisterMode : public Instructions {
private:
    int op;
    string name;
    long long int rs = -1;
    long long int rt = -1;
    long long int rd = -1;
    long long int sharedMem;
    int func;
    unordered_map<long long int, string> strRM;
    long val;

public:
    RegisterMode(int op, string name, int func) {
        this->op = op;
        this->name = name;
        this->rs = 0;
        this->rt = 0;
        this->rd = 0;
        this->sharedMem = 0;
        this->func = func;
    }
    RegisterMode(int op, string name, long long int rs, long long int rt, long long int rd, long long int sharedMem,
                 int func, unordered_map<long long int, string> strRM) {
        this->op = op;
        this->name = name;
        this->rs = rs;
        this->rt = rt;
        this->rd = rd;
        this->sharedMem = sharedMem;
        this->func = func;
        this->strRM = strRM;
    }

    void init(long data[32], unordered_map<long long int, long long int> varr, unsigned int &pc) {
        unsigned int dd = this->str2int(name.c_str(), 0);
        if (dd == this->str2int("add", 0))
            val = data[rs] + data[rt];
        else if (dd == this->str2int("sub", 0))
            val = data[rs] - data[rt];
        else if (dd == this->str2int("and", 0))
            val = data[rs] & data[rt];
        else if (dd == this->str2int("or", 0))
            val = data[rs] | data[rt];
        else if (dd == this->str2int("nor", 0))
            val = ~(data[rs] | data[rt]);
    }
    void toPush(long data[32], unordered_map<long long int, long long int> varr) {}
    void consoleDisplay(long data[32], unordered_map<long long int, long long int> varr) {
        unsigned int dd = this->str2int(name.c_str(), 0);
        if (dd == this->str2int("add", 0)) {
            data[rd] = val;
            printf("$%s is modified to %#lx\n", strRM[rd].c_str(), val);
        }
        else if (dd == this->str2int("sub", 0)) {
            data[rd] = val;
            printf("$%s is modified to %#lx\n", strRM[rd].c_str(), val);
        }
        else if (dd == this->str2int("and", 0)) {
            data[rd] = val;
            printf("$%s is modified to %#lx\n", strRM[rd].c_str(), val);
        }
        else if (dd == this->str2int("or", 0)) {
            data[rd] = val;
            printf("$%s is modified to %#lx\n", strRM[rd].c_str(), val);
        }
        else if (dd == this->str2int("slt", 0)) {
            data[rd] = val;
            if (!val) {
                printf("$%s is modified to 0x0\n", strRM[rd].c_str());
            }
            else {
                printf("$%s is modified to %02lx\n", strRM[rd].c_str(), val);
            }
        }
        else if (dd == this->str2int("nor", 0)) {
            data[rd] = val;
            printf("$%s is modified to %#lx\n", strRM[rd].c_str(), val);
        }
    }
    long long int fetchStateR() {
        return rs;
    }
    long long int fetchStateT() {
        return rt;
    }
    long long int fetchStateD() {
        return rd;
    }
};
class JunctionMode : public Instructions {
private:
    int op;
    string name;
    string rde;

public:
    JunctionMode(int op, string name) {
        this->op = op;
        this->name = name;
        this->rde = "";
    }
    JunctionMode(int op, string name, string rde) {
        this->op = op;
        this->name = name;
        this->rde = rde;
    }

    void init(long data[32], unordered_map<long long int, long long int> varr, unsigned int &pc) {
        unsigned int dd = this->str2int(name.c_str(), 0);
        if (dd == this->str2int("j", 0)) {
            long long int temp = binDeci(rde);
            temp = temp >> 2;
            pc += temp;
        }
    }
    void toPush(long data[32], unordered_map<long long int, long long int> varr){};
    void consoleDisplay(long data[32], unordered_map<long long int, long long int> varr){};
    long long int fetchStateR() { return -1; }
    long long int fetchStateT() { return -1; }
    long long int fetchStateD() { return -1; }
};
class IteratorMode : public Instructions {
private:
    int op;
    string name;
    long long int rs = -1;
    long long int rt = -1;
    long long int rde;
    unordered_map<long long int, string> strRM;

public:
    IteratorMode(int op, string name) {
        this->op = op;
        this->name = name;
        this->rs = 0;
        this->rt = 0;
        this->rde = 0;
    }
    IteratorMode(int op, string name, long long int rs, long long int rt, long long int rde, unordered_map<long long int, string> strRM) {
        this->op = op;
        this->name = name;
        this->rs = rs;
        this->rt = rt;
        this->rde = rde;
        this->strRM = strRM;
    }

    void init(long data[32], unordered_map<long long int, long long int> varr, unsigned int &pc) {
        unsigned int dd = this->str2int(name.c_str(), 0);
        if (dd == this->str2int("beq", 0)) {
            if (data[rs] == data[rt]) {
                pc = pc + (rde)*4;
            }
        }
    }
    void toPush(long data[32], unordered_map<long long int, long long int> varr) {
        unsigned int dd = this->str2int(name.c_str(), 0);
        if (dd == this->str2int("lw", 0)) {
            long dMemLocation = data[rs] + rde;
            if (varr.count(dMemLocation) <= 0) {
                varr[dMemLocation] = 0;
            }
            data[rt] = varr[dMemLocation];
            printf("$%s is modified to %#llx\n", strRM[rt].c_str(), varr[dMemLocation]);
        }
    }
    void consoleDisplay(long data[32], unordered_map<long long int, long long int> varr) {
        unsigned int dd = this->str2int(name.c_str(), 0);
        if (dd == this->str2int("sw", 0)) {
            long dMemLocation = data[rs] + rde;
            if (varr.count(dMemLocation) <= 0) {
                varr[dMemLocation] = 0;
            }
            varr[dMemLocation] = data[rt];
            printf("Memory %#lx is modified to %#lx\n", dMemLocation, data[rt]);
        }
    }
    long long int fetchStateR() {
        return -1;
    }
    long long int fetchStateT() {
        return -1;
    }
    long long int fetchStateD() {
        return -1;
    }
};
void allocationString(unordered_map<string, char> *um) {
    (*um)["0000"] = '0';(*um)["0001"] = '1';(*um)["0010"] = '2';(*um)["0011"] = '3';(*um)["0100"] = '4';(*um)["0101"] = '5';(*um)["0110"] = '6';(*um)["0111"] = '7';
    (*um)["1000"] = '8';(*um)["1001"] = '9';(*um)["1010"] = 'A';(*um)["1011"] = 'B';(*um)["1100"] = 'C';(*um)["1101"] = 'D';(*um)["1110"] = 'E';(*um)["1111"] = 'F';
}
long int binHex(long int binary) {
    string hex = "";
    long int dec = 0, i = 1, remainder;
    while (binary != 0) {
        remainder = binary % 10;
        dec = dec + remainder * i;
        i = i * 2;
        binary = binary / 10;
    }
    while (dec != 0) {
        hex.insert(0, to_string(dec % 16));
        dec = dec / 16;
    }
    if (hex.size() == 0) hex = "0";
    return stoi(hex);
}
string binDec(string bin) { {
        int l = bin.size();
        int t = bin.find_first_of('.');
        int len_left = t != -1 ? t : l;
        for (int i = 1; i <= (4 - len_left % 4) % 4; i++)
            bin = '0' + bin;
        if (t != -1) {
            int len_right = l - len_left - 1;
            for (int i = 1; i <= (4 - len_right % 4) % 4; i++)
                bin = bin + '0';
        }
        unordered_map<string, char> bin_hex_map;
        allocationString(&bin_hex_map);
        unsigned int i = 0;
        string hex = "";
        while (1) {
            hex += bin_hex_map[bin.substr(i, 4)];
            i += 4;
            if (i == bin.size())
                break;
            if (bin.at(i) == '.') {
                hex += '.';
                i++;
            }
        }
        unsigned int x;
        stringstream ss;
        ss << hex << hex;
        ss >> x;
        hex = to_string(x);
        return hex;
    }
}
bool checkRMode(long int binary) {
    long int hex = binHex(binary);
    return (hex == 0);
}
unordered_map<string, string> insFile(string filename) {
    unordered_map<string, string> instructionMap;
    ifstream inFile;
    inFile.open(filename);
    if (!inFile) {
        cerr << "Unable to open file: " << filename;
        exit(1);
    }
    string line;
    string key;
    while (getline(inFile, line)) {
        istringstream iss(line);
        vector<string> results(istream_iterator<string>{iss},
                               istream_iterator<string>());
        key = results[0] + results[2];
        instructionMap.insert(pair<string, string>(key, results[1]));
    }
    return instructionMap;
}
unordered_map<long long int, string> regFile(string filename) {
    unordered_map<long long int, string> registermap;
    ifstream inFile;
    inFile.open(filename);
    if (!inFile) {
        cerr << "Unable to open file: " << filename;
        exit(1);
    }
    string line;
    string key;
    long long int keyInt;
    while (getline(inFile, line)) {
        istringstream iss(line);
        vector<string> results(istream_iterator<string>{iss},
                               istream_iterator<string>());
        key = results[0];
        keyInt = atoi(key.c_str());
        registermap.insert(pair<long long int, string>(keyInt, results[1]));
    }
    return registermap;
}
string binHex(string bin) { {
        int l = bin.size();
        int t = bin.find_first_of('.');
        int len_left = t != -1 ? t : l;
        for (int i = 1; i <= (4 - len_left % 4) % 4; i++)
            bin = '0' + bin;
        if (t != -1) {
            int len_right = l - len_left - 1;
            for (int i = 1; i <= (4 - len_right % 4) % 4; i++)
                bin = bin + '0';
        }
        unordered_map<string, char> bin_hex_map;
        allocationString(&bin_hex_map);
        unsigned i = 0;
        string hex = "";
        while (1) {
            hex += bin_hex_map[bin.substr(i, 4)];
            i += 4;
            if (i == bin.size())
                break;
            if (bin.at(i) == '.') {
                hex += '.';
                i++;
            }
        }
        return hex;
    }
}

Instructions *decode(string inputB, unordered_map<long long int, string> mapReg, unordered_map<string, string> mapIns) {
    string firstSix = inputB.substr(0, 6);
    string key;
    if (checkRMode(stoi(firstSix))) {
        key = "r";
        key.append(inputB.substr(inputB.size() - 7));
        key.pop_back();
        string name;
        name = mapIns[key];
        long int lastSix = stoi(inputB.substr(inputB.size() - 7));
        long long int rs = binDeci(inputB.substr(6, 5));
        long long int rt = binDeci(inputB.substr(11, 5));
        long long int rd = binDeci(inputB.substr(16, 5));
        long long int sharedMem = binDeci(inputB.substr(21, 5));
        Instructions *i = new RegisterMode(0, name, rs, rt, rd, sharedMem, binHex(lastSix), mapReg);
        return i;
    }
    key = "i" + firstSix;
    if (mapIns.count(key) > 0) {
        string name;
        name = mapIns[key];
        long int opcode = binHex(stoi(inputB.substr(0, 6)));
        long long int rs = binDeci(inputB.substr(6, 5));
        long long int rt = binDeci(inputB.substr(11, 5));
        long long int imm = binDeci(inputB.substr(16, 16));
        Instructions *i = new IteratorMode(opcode, name, rs, rt, imm, mapReg);
        return i;
    }
    key = "j" + firstSix;
    if (mapIns.count(key) > 0) {
        string name;
        name = mapIns[key];
        long int opcode = binHex(stoi(inputB.substr(0, 6)));
        string address = inputB.substr(6, 26);
        static Instructions *i = new JunctionMode(opcode, name, address);
        return i;
    }
    else {
        cout << "Instruction not found!" << endl;
        Instructions *noVal;
        exit(1);
    }
}

bool checkStateS(Instructions *decoding, Instructions *executing, Instructions *consoleDisplay) {
    long long int rs = decoding->fetchStateR();
    long long int rt = decoding->fetchStateT();
    if (executing != NULL) {
        long long int rd = executing->fetchStateD();
        if (rd == rt || rd == rs) return true;
    }
    if (consoleDisplay != NULL) {
        long long int rd = consoleDisplay->fetchStateD();
        if (rd == rt || rd == rs) return true;
    }
    return false;
}



bool componentsAreEmpty(int getI, string decIsn, Instructions *exI, Instructions *memI, Instructions *pushI) {
    return (getI < 0) && decIsn.empty() && (exI == NULL) && (memI == NULL) && (pushI == NULL);
}
int main(int argc, char *argv[]) {
    long int data[32];
    for (int i = 0; i < 32; i++) data[i] = 0;
    data[9] = 32;
    data[10] = 5;
    data[16] = 112;
    unordered_map<long long int, long long int> varr;
    varr[112] = 5;
    varr[116] = 16;
    ifstream inFile;
    inFile.open("sample_binary.txt");
    if (!inFile) {
        cerr << "Unable to open file: sample_binary.txt";
        exit(1);
    }
    vector<string> vecObj;
    string inputB;
    while (getline(inFile, inputB)) {
        vecObj.push_back(inputB);
    }
    inFile.close();
    unordered_map<string, string> mapIns;
    mapIns = insFile("instructions.txt");
    unordered_map<long long int, string> mapReg;
    mapReg = regFile("data.txt");
    int getI = -1;
    string decIsn = "\0";
    Instructions *decI = NULL;
    Instructions *exI = NULL;
    Instructions *memI = NULL;
    Instructions *pushI = NULL;
    unsigned int pc_ = 0;
    unsigned int pc = 0;
    bool stateR = true;
    bool checkDRF = false;
    bool stateS = false;
    unsigned int cyclesSum = 0;
    while (stateR) {
        if (exI != NULL) stateS = checkStateS(exI, memI, memI);
        else stateS = false;
        cout << "total_clock_cycles " << cyclesSum + 1 << " :" << endl;
        if (!(pushI == NULL)) pushI->toPush(data, varr);
        if (!(memI == NULL)) memI->consoleDisplay(data, varr);
        if (!(exI == NULL || stateS)) exI->init(data, varr, pc);
        if (!(decIsn.empty() || stateS)) {
            decI = decode(decIsn, mapReg, mapIns);
            stateS = checkStateS(decI, exI, memI);
            if (stateS) {
                exI = NULL;
            }
        }
        getI = pc;
        pushI = memI;
        memI = exI;
        exI = decI;
        if (decIsn.empty()) exI = NULL;
        if (getI >= 0 && !checkDRF && (getI / 4 <= vecObj.size() - 1)) decIsn = vecObj[getI / 4];
        else {
            decIsn = "";
            decI = NULL;
        }
        if (pc_ != pc) {
            printf("control hazard detected (flush 3 instructions)\n");
            decIsn = "";
            decI = NULL;
            exI = NULL;
        }
        if (!stateS) pc += 4;
        else printf("data hazard detected\n");
        pc_ = pc;
        if (!(checkDRF || stateS)) {
            printf("pc is modified to %#x\n", pc);
        }
        cyclesSum++;
        if (pc / 4 >= vecObj.size() - 1) checkDRF = true;
        if (checkDRF) {
            pc = -1;
            pc_ = pc;
            if (componentsAreEmpty(getI, decIsn, exI, memI, pushI)) {
                stateR = false;
            }
        }
        cout << endl;
    }
    cout << "program terminated:" << endl;
    cout << "total execution time is " << cyclesSum << " cycles" << endl;
    return 0;
}