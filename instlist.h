#ifndef _INSTLIST_H_
#define _INSTLIST_H_

#include "instnode.h"
#include <fstream>

/* use linked list to store instruction*/
class instlist {

public:
	instlist();
	void addinst(string newsym, string newinst, string newstate, string newall, string newlo, string newop);
	void display();
	string getLastSym();
	string getLastInst();
	string getLastState();
	string getLastLocate();
	void outputLST();

private:
	instnode* first;
	instnode* last;
};
#endif // !instlist
#pragma once
