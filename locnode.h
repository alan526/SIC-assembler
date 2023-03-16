#pragma once
#ifndef _LOCNODE_H_
#define _LOCNODE_H_

#include<string>

using namespace std;

/* store the location which need to be modified in the symabol table */
class locnode {

public:
	locnode();
	locnode(string newloc);
	string getloc();

private:
	locnode* next;
	string loc;

	friend class symnode;
	friend class symlist;
};
#endif // !_LOCNODE_H_

