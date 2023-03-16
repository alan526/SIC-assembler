#include "locnode.h"

locnode::locnode() {
	next = nullptr;
	loc = "";
}

locnode::locnode(string newloc) {
	loc = newloc;
}

string locnode::getloc() {

	return(loc);
}