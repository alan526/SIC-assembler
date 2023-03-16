#ifndef _SYMLIST_H_
#define _SYMLIST_H_

#include "symnode.h"
#include "locnode.h"
#include "record.h"
#include "assembler.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

/* use linked list record symbol table */
class symlist {

public:
	symlist();
	void addsym(string newsym);
	/* add symbol's value */
	void addvalue(string targetSym, string value, record& objcode);
	string getvalue(string targetSym);
	void display();
	void outputSTD();
	/* Is symbol exist */
	bool findsym(string targetSym);
	/* Is value exist */
	bool findval(string targetSym);
	/* if symbol's value isn't exist , add the location which need to be modified */
	void nosymvalue(string targetSym, string nowloc);

private:
	symnode* first;
	symnode* last;

};
#endif // !_SYMLIST_H_
#pragma once
