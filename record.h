#ifndef _RECORD_H_
#define _RECORD_H_

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

class record {

public:
	record();
	/* add head record */
	void headrecord(string name, string startLoc, string endLoc);
	/* add text record (overload) */
	void addtext(string code, int addsize, string loc);
	void addtext(string modifyCode);
	/* process text record break line */
	void textline();
	/* add end record */
	void endrecord(string startLoc);
	/* output obj file */
	void outputOBJ();
	void display();
	string inttohex(int number, int select);
	string geth() { return(h); }
	string gett() { return(t); }
	string gete() {	return(e); }

private:
	string textStart;//text record start position
	string tempT;//store temporary text record
	string h;//head record
	string t;//text record
	string e;//end record
	int tsize;//text record size
};
#endif // !_RECORD_H_
#pragma once
