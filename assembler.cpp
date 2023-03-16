#include "assembler.h"
#include "instlist.h"
#include "symlist.h"
#include "record.h"

/* constructor */
assembler::assembler() {

}

/* assembler */
void assembler::sourceCode(string fname, int outputType) {
	/* input file */
	fstream fin;
	/* now input string */
	string temp;
	/* three part of instruction and decide locate */
	string symbol = "", inst = "", state = "", locate = "", locateRecord = "";
	/* write header record */
	string programName, startLoc, endLoc;
	/* write end record */
	string firstInstLoc;
	/* store intruction */
	instlist data;
	/* store symbol table */
	symlist symtable;
	/* store objcode */
	record objcode;
	/* calculate objcode*/
	string opNum = "", opLoc = "";
	/* use to cut string */
	string cutstr;
	/* decide how to calculate location */
	int locmode, loctrans, locdiffer;

	/* isop : decide temp is instruction or not
	   line : decide a instruction finish or not
	   start : decide the start position load or not
	   hassymbol : Is symbol exist
	   x : Is index addressing 
	   nosymval : decide symbol's value exist or not 
	   firstInst : decide the firt instruction(used in end record) */
	bool isop = false, line = false, start = false, hassymbol = false, x = false, nosymval = false, firstInst = true;

	/* open file and error detect */
	fin.open(fname + ".asm");
	if (!fin.is_open()) {
		cout << "File open fail";
		system("pause");
		exit(1);
	}

	/* each time load a string */
	while (!fin.eof()) {

		fin >> temp;

		/* decide temp is instruction or not , and decide mode to calculate location*/
		if (temp == "START" || temp == "END" || temp == "BYTE" || temp == "WORD" || temp == "RESB" || temp == "RESW") {
			inst = temp;
			if (inst == "START" || inst == "END") {
				locmode = 0;
			}
			else if (inst == "BYTE") {
				locmode = 1;
			}
			else if (inst == "WORD") {
				locmode = 2;
			}
			else if (inst == "RESB") {
				locmode = 3;
			}
			else if (inst == "RESW") {
				locmode = 4;
			}
			isop = true;
		}
		else {
			for (int i = 0; i < opNumber; i++) {
				if (temp == opTable[i]) {
					inst = temp;
					isop = true;
					opNum = opcode[i];
					locmode = 5;
					/* record first instruction's address (end record) */
					if (firstInst) {
						firstInstLoc = locateRecord;
						firstInst = false;
					}
					break;
				}
			}
		}

		/* if temp is . , it's a line */
		if (temp == ".") {
			line = true;
			locate = "";
			locmode = 100;
			/* get comment */
			getline(fin, inst);	
		}

		/* if instruction is RSUB, it's a line */
		if (inst == "RSUB") {
			line = true;
			locate = locateRecord;
			opLoc = "0000";
		}

		/* if temp isn't a instruction,add temp to symbol and symbol table */
		if (!isop) {
			symbol = temp;
			if (symbol != ".") {
				symtable.addsym(symbol);
				hassymbol = true;
			}
		}
		/* if it has instructon, and instructon isn't RSUB¡Aadd to state */
		else if (!(inst == "RSUB")) {
			fin >> state;
			/* process instruction(not directive)objcode */
			if (locmode == 5) {
				int currentpos = 0;
				int cutpos;
				/* if it's index addressing , need to cut string to find symbol */
				cutpos = state.find_first_of(" ,", currentpos);
				cutstr = state.substr(currentpos, cutpos - currentpos);
				/* search target is in symbol table or not */
				if (symtable.findsym(cutstr)) {
					/* if target be found, is its value exist */
					nosymval = symtable.findval(cutstr);
				}
				else {
					/* if not found ¡Aadd symbol to symbol table */
					symtable.addsym(cutstr);
					nosymval = true;
				}
				/* decide it is index addressing or not */
				for (int i = 0; i < state.length(); i++) {

					if (state[i] == ',') {
						x = true;
					}
				}
				/* get target address */
				opLoc = symtable.getvalue(cutstr);
				/* process index addressing's objcode */
				if (x == true) {
					opLoc = inttohex(stoi(opLoc, nullptr, 16) + stoi("8000", nullptr, 16));
				}
				
			}
			/* process byte's target address */
			if (locmode == 1) {
				if (state[0] == 'X') {
					opLoc = state.substr(2, state.length() - 3);
				}
				else if(state[0] == 'C'){
					for (int i = 2; i < state.length() - 1; i++) {
						stringstream ss;
						int asc = (int)state[i];
						ss << setiosflags(ios::uppercase) << hex << asc;
						opLoc = opLoc + ss.str();
						ss.clear();
					}
				}

			}
			/* process word's target address */
			else if (locmode == 2) {
				opNum = "00";
				opLoc = inttohex(stoi(state));
			}
			/* get start address */
			if (!start) {
				if (inst == "START") {
					locateRecord = state;
					while (locateRecord.length() < 4) {
						locateRecord = '0' + locateRecord;
					}
					programName = symbol;
					startLoc = locateRecord;
				}
			}
			/* a instruction is finish */
			line = true;
			locate = locateRecord;
			/* add symbol and its value in symbol table */
			if (hassymbol) {
				symtable.addvalue(symbol, locate, objcode);
			}
		}
		
		/* if a instruction is finish, add in data */
		if (line) {
			/* if target address isn't exist , add location which need modified in symbol table */
			if (nosymval) {
				symtable.nosymvalue(cutstr, locate);
			}
			/* store data */
			data.addinst(symbol, inst, state, symbol + "\t" + inst + "\t" + state, locate + "\t", opNum + opLoc);
			/* calculate instruction used location */
			switch (locmode) {
				/* start and end */
				case 0:
					loctrans = stoi(locateRecord, nullptr, 16);
					locateRecord = inttohex(loctrans);
					break;
				/* BYTE */
				case 1:
					if (state[0] == 'X') {
						loctrans = stoi(locateRecord, nullptr, 16) + (state.length() - 3) / 2;
						locateRecord = inttohex(loctrans);
						locdiffer = (state.length() - 3) / 2;
					}
					else if (state[0] == 'C') {
						loctrans = stoi(locateRecord, nullptr, 16) + (state.length() - 3);
						locateRecord = inttohex(loctrans);
						locdiffer = (state.length() - 3);
					}

					objcode.addtext(opNum + opLoc, locdiffer, locate);

					break;
				/* WORD */
				case 2:
					loctrans = stoi(locateRecord, nullptr, 16) + 3;
					locateRecord = inttohex(loctrans);
					locdiffer = 3;
					objcode.addtext(opNum + opLoc, locdiffer, locate);
					break;
				/* RESB */
				case 3:
					loctrans = stoi(locateRecord, nullptr, 16) + stoi(state);
					locateRecord = inttohex(loctrans);
					objcode.textline();
					break;
				/* RESW */
				case 4:
					loctrans = stoi(locateRecord, nullptr, 16) + stoi(state)*3;
					locateRecord = inttohex(loctrans);
					objcode.textline();
					break;
				/* instruction */
				case 5:
					loctrans = stoi(locateRecord, nullptr, 16) + 3;
					locateRecord = inttohex(loctrans);
					locdiffer = 3;
					objcode.addtext(opNum + opLoc, locdiffer, locate);
					break;
				default:
					break;
			}

			/* it is end  */
			if (inst == "END") {
				endLoc = locateRecord;
				objcode.textline();
				objcode.headrecord(programName, startLoc, endLoc);
				objcode.endrecord(firstInstLoc);
				break;
			}

			/* initial variable to get next instruction */
			symbol = "";
			inst = "";
			state = "";
			opNum = "";
			opLoc = "";
			cutstr = "";
			isop = false;
			line = false;
			hassymbol = false;
			x = false;
			nosymval = false;
			
		}
		
	}
	/* output (used to debug) */
	//data.display();
	//symtable.display();
	//objcode.display();
	switch (outputType)
	{
	case 1:
		objcode.outputOBJ();
		break;
	case 2:
		objcode.outputOBJ();
		data.outputLST();
		break;
	case 3:
		objcode.outputOBJ();
		symtable.outputSTD();
		break;
	case 4:
		objcode.outputOBJ();
		symtable.outputSTD();
		data.outputLST();
		break;
	default:
		break;
	}
	fin.close();
}

/* translate int to hex string */
string assembler::inttohex(int number) {
	
	int r;
	string hexnum = "";
	char hex[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

	while (number > 0)
	{
		r = number % 16;
		hexnum = hex[r] + hexnum;
		number = number / 16;
	}

	/* add 0 */
	while (hexnum.length() < 4) {
		hexnum = '0' + hexnum;
	}

	return(hexnum);
}