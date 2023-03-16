#include "record.h"

record::record() {
	tsize = 0;
}

/* store head record */
void record::headrecord(string name, string startLoc, string endLoc) {
	string size;
	for (int i = name.length(); i < 6; i++) {
		name = name + " ";
	}
	while (startLoc.length() < 6) {
		startLoc = "0" + startLoc;
	}
	size = inttohex(stoi(endLoc, nullptr, 16) - stoi(startLoc, nullptr, 16), 1);
	h = "H" + name + startLoc + size;

	
}

/* add text record */
void record::addtext(string code, int addsize, string loc) {
	if (tsize == 0) {
		textStart = loc;
	}
	if (tsize + addsize > 30) {
		textline();
		tempT = code;
		tsize += addsize;
		textStart = loc;
	}
	else {
		tsize += addsize;
		tempT = tempT + code;
	}

}

/* add text record */
void record::addtext(string modifyCode) {
	t = t + modifyCode;
}

/* text record break line */
void record::textline() {
	stringstream ss1, ss2;
	if (tsize == 0) {
	
	}
	else {
		ss1 << setw(6) << setfill('0') << textStart;
		ss2 << setw(2) << setfill('0') << setiosflags(ios::uppercase) << hex << tsize;
		t = t + "T" + ss1.str() + ss2.str() + tempT + "\n";
		ss1.clear();
		ss2.clear();
		tempT = "";
		tsize = 0;
		textStart = "";
	}
}

/* store end record */
void record::endrecord(string startLoc){
	while (startLoc.length() < 6) {
		startLoc = "0" + startLoc;
	}
	e = "E" + startLoc;
}

/* output obj file */
void record::outputOBJ() {
	ofstream fout;
	fout.open("test.obj");
	fout << h << endl;
	fout << t;
	fout << e << endl;
	cout << "obj output success " << endl;
	fout.close();
}

void record::display() {
	cout << h << endl;
	cout << t;
	cout << e << endl;
}

string record::inttohex(int number, int select) {

	int r;
	string hexnum = "";
	char hex[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

	while (number > 0)
	{
		r = number % 16;
		hexnum = hex[r] + hexnum;
		number = number / 16;
	}

	if (select > 0) {
		while (hexnum.length() < 6) {
			hexnum = '0' + hexnum;
		}
	}

	return(hexnum);
}