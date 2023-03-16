#include "symlist.h"

/* constructor */
symlist::symlist() {
	first = nullptr;
}

/* add symbol into symbol table */
void symlist::addsym(string newsym) {
	if (findsym(newsym)) {

	}
	else {
		if (first == nullptr) {
			first = new symnode(newsym);
			last = first;
		}
		else {
			symnode* current = last;
			last = new symnode(newsym);
			current->next = last;
		}
	}
}

/* add value to symbol which has been defined */
void symlist::addvalue(string targetSym, string newvalue, record& objcode) {
	symnode* current;
	symnode* nextone = first;
	while (nextone) {
		current = nextone;
		if (current->getSym() == targetSym) {
			current->value = newvalue;
			locnode* cur;
			locnode* next = current->first;
			/* if had location which need to modify */
			while (next) {
				cur = next;
				stringstream ss;
				/* text record's break line */
				objcode.textline();
				int loc = stoi(cur->getloc(), nullptr, 16) + 1;
				ss << "T" << setw(6) << setfill('0') << setiosflags(ios::uppercase) << hex << loc << "02" << newvalue << endl;
				/* add text record */
				objcode.addtext(ss.str());
				next = cur->next;
				ss.clear();
			}
			current->first = nullptr;
			break;
		}

		nextone = current->next;
		
	}
}

/* get symbol's value */
string symlist::getvalue(string targetSym) {
	symnode* current;
	symnode* nextone = first;
	while (nextone) {
		current = nextone;
		if (current->getSym() == targetSym) {
			if (current->getValue() != "") {
				return(current->getValue());
			}
			else {
				return("0000");
			}
			
		}

		nextone = current->next;

	}

	return("0000");
}

void symlist::display() {
	symnode* current;
	symnode* nextone = first;
	cout << "Symbol\t" << "Value\t" << endl;
	cout << "======\t" << "======\t" << endl;
	while (nextone) {
		current = nextone;
		cout << current->getSym() + "\t" << current->getValue() + "\t";
		locnode* cur;
		locnode* next = current->first;
		while (next) {
			cur = next;
			cout << "  :" << cur->getloc() + "\t";
			next = cur->next;
		}

		cout << endl;
		nextone = current->next;

	}
}

/* output std file */
void symlist::outputSTD() {
	symnode* current;
	symnode* nextone = first;
	ofstream fout;
	fout.open("test.stb");
	fout << "Symbol\t" << "Value\t" << endl;
	fout << "======\t" << "======\t" << endl;
	while (nextone) {
		current = nextone;
		fout << current->getSym() + "\t" << current->getValue() + "\t" << endl;
		nextone = current->next;
	}

	cout << "stb output success " << endl;
	fout.close();
}

/* judge symbol exist or not */
bool symlist::findsym(string targetSym) {
	symnode* current;
	symnode* nextone = first;
	while (nextone) {
		current = nextone;
		if (current->getSym() == targetSym) {
			return(true);
		}

		nextone = current->next;

	}

	return(false);
}

/* judge symbol's value exist or not */
bool symlist::findval(string targetSym) {
	symnode* current;
	symnode* nextone = first;
	while (nextone) {
		current = nextone;
		if (current->getSym() == targetSym) {
			if (current->getValue() == "") {
				return(true);
			}
			else {
				return(false);
			}
		}

		nextone = current->next;

	}

	return(false);
}

/* add the location which need to be modified behind the symbol */
void symlist::nosymvalue(string targetSym, string nowloc) {
	symnode* current;
	symnode* nextone = first;
	while (nextone) {
		current = nextone;
		if (current->getSym() == targetSym) {
			current->addloc(nowloc);
		}

		nextone = current->next;
	}

}