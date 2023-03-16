#ifndef _INSTNODE_H_
#define _INSTNODE_H_

#include <string>

using namespace std;

/* record the input instruction */
class instnode {

public :
	instnode(string newsym, string newinst, string newstate, string newall, string newlo, string newop);
	instnode();
	string getsym();
	string getinst();
	string getstate();
	string getall();
	string getloc();
	string getop();

private:
	instnode* next;
	string symbol;
	string inst;
	string state;
	string allinst;
	string locate;
	string opcode;

	friend class instlist;
};
#endif // !instruction
#pragma once
