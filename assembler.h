#ifndef _ASSEMBLER_H_
#define _ASSEMBLER_H_

#include <string>
#include <math.h>
#include <fstream>
#include <cstdlib>
#include <iostream>


using namespace std;

/* assembler and optable */
class assembler {

public:
	assembler();
	void sourceCode(string fname, int outputtype);
	string inttohex(int number);

private:

	int opNumber = 42;

	string opTable[42] = { "ADD", "ADDF", "AND", "COMP", "COMMPF",
						   "DIV", "DIVF", "J", "JEQ", "JGT",
						   "JLT", "JSUB", "LDA", "LDB", "LDCH",
						   "LDF", "LDL", "LDS", "LDT", "LDX",
						   "LPS", "MUL", "MULF", "OR", "RD",
						   "RSUB","SSK", "STA", "STB", "STCH",
						   "STF", "STI", "STL", "STS", "STSW",
						   "STT", "STX", "SUB", "SUBF", "TD",
						   "TIX", "WD" };

	string opcode[42] = { "18", "58", "40", "28", "88",
						  "24", "64", "3C", "30", "34",
						  "38", "48", "00", "68", "50",
						  "70", "08", "6C", "74", "04",
						  "D0", "20", "60", "44", "D8",
						  "4C", "EC", "0C", "78", "54",
						  "80", "D4", "14", "7C", "E8",
						  "84", "10", "1C", "5C", "E0",
						  "2C", "DC" };

};

#endif // !assembler

