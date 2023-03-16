#include <iostream>
#include <cstdlib>
#include <string>
#include "assembler.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	int number, outputType = 0;
	assembler a;
	string fname, type;
	/* record number of argument and error detect */
	number = argc;
	/* decide output and the input file's name */
	if (number == 2) {
		fname = argv[1];
		outputType = 1;
	}
	else if (number == 3) {
		fname = argv[1];
		type = argv[2];
		if (type == "-s") {
			outputType = 2;
		}
		else if (type == "-t") {
			outputType = 3;
		}
		else if (type == "-a") {
			outputType = 4;
		}
		else {
			cout << "«ü¥O¿é¤J¿ù»~";
			system("pause");
			exit(1);
		}
	}
	else {
		cout << "«ü¥O¿é¤J¿ù»~";
		system("pause");
		exit(1);
	}
	/* one pass assembler */
	a.sourceCode(fname, outputType);
	system("pause");
	return(0);
}