#include "instlist.h"
#include <iostream>
#include <cstdlib>

using namespace std;

instlist::instlist() {
	first = nullptr;
	last = nullptr;
}

/* add instructon data */
void instlist::addinst(string newsym, string newinst, string newstate, string newall, string newlo, string newop) {

	if (first == nullptr) {

		first = new instnode(newsym, newinst, newstate, newall, newlo, newop);
		last = first;
	}
	else {
		instnode* current = last;
		last = new instnode(newsym, newinst, newstate, newall, newlo, newop);
		current->next = last;

	}
}

void instlist::display() {
	instnode* current;
	instnode* nextone = first;
	cout << "Loc.\t" << "Source statement" << endl;
	cout << "===== =============================" << endl;
	do {
		current = nextone;
		cout << current->getloc();
		cout << current->getall();
		cout << "\t" << current->getop()  << endl;
		nextone = current->next;
	} while (nextone);
}

string instlist::getLastSym() {
	return(last->getsym());
}

string instlist::getLastInst() {
	return(last->getinst());
}

string instlist::getLastState() {
	return(last->getstate());
}

string instlist::getLastLocate() {
	return(last->getloc());
}

/* LST file output */
void instlist::outputLST() {
	instnode* current;
	instnode* nextone = first;
	ofstream fout;
	fout.open("test.lst");
	fout << "Loc.\t" << "Source statement" << endl;
	fout << "===== =============================" << endl;
	do {
		current = nextone;
		fout << current->getloc();
		fout << current->getall() << endl;
		nextone = current->next;
	} while (nextone);
	cout << "lst output success " << endl;
	fout.close();
}