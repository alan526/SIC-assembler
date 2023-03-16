#ifndef _SYMNODE_H_
#define _SYMNODE_H_

#include <string>
#include "locnode.h"

using namespace std;

/* store symbol and value */
class symnode {

public:
	symnode(string newsym);
	symnode();
	string getSym();
	string getValue();
	void addloc(string newloc); //if symbol's value which is undefined be used , add location which need to be modified.
private:
	symnode* next;
	locnode* first;
	locnode* last;
	string sym;
	string value;

	friend class symlist;
};
#endif // !_SYMNODE_H_
#pragma once
