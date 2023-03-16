#include "instnode.h"

instnode::instnode(string newsym, string newinst, string newstate, string newall, string newlo, string newop) {
	next = nullptr;
	symbol = newsym;
	inst = newinst;
	state = newstate;
	allinst = newall;
	locate = newlo;
	opcode = newop;
}

instnode::instnode() {

}

string instnode::getsym() {
	return(symbol);
}

string instnode::getinst() {
	return(inst);
}

string instnode::getstate() {
	return(state);
}

string instnode::getall() {
	return(allinst);
}

string instnode::getloc() {
	return(locate);
}

string instnode::getop() {
	return(opcode);
}
