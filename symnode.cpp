#include "symnode.h"

symnode::symnode() {
	next = nullptr;
	value = "";
}

symnode::symnode(string newsym) {
	sym = newsym;
	next = nullptr;
	value = "";
}

string symnode::getSym() {
	return(sym);
}

string symnode::getValue() {
	return(value);
}

/* if symbol's value which is undefined be used , add location which need to be modified */
void symnode::addloc(string newloc) {
	if (first == nullptr) {
		first = new locnode(newloc);
		last = first;
	}
	else {
		locnode* current = last;
		last = new locnode(newloc);
		current->next = last;

	}
}