#include "Symbol.h"

bool SymbolTableClass::Exists(const std::string & s) {
	//returns true if <s> is already in the symbol table

	if (SymbolTableVector.size() > 0) {
		for (size_t i = 0; i < SymbolTableVector.size(); i++) {
			if (SymbolTableVector[i].mLabel == s) {
				return true;
			}
		}
	}

	return false;
}

void SymbolTableClass::AddEntry(const std::string & s) {
	//adds <s> to the symboltable
	//or quits if it was already there
	if (Exists(s)) {
		cerr << s << " already exists. Now quitting.";
		exit(1);

	}
	else {
		struct Variable newVariable;
		newVariable.mLabel = s;
		SymbolTableVector.push_back(newVariable);
	}
}

int SymbolTableClass::GetValue(const std::string & s) {
	//returns the current value of variable <s> when interpreting
	//prints a message and quits if variable s does not exist

	//how do you return the value of a string????
	if (Exists(s)) {
		for (size_t i = 0; i < SymbolTableVector.size(); i++) {
			if (SymbolTableVector[i].mLabel == s) {
				return SymbolTableVector[i].mValue;
			}
		}
	}
	else {
		cerr <<  s << " does not exist in the symbol table. Now quitting.";
		exit(1);
	}
	
}

void SymbolTableClass::SetValue(const std::string & s, int v) {
	//sets variable <s> to the given value
	//prints message and quits if variable s doesnt exist
	if (Exists(s)) {
		//how do you set the value of a string??
		for (size_t i = 0; i < SymbolTableVector.size(); i++) {
			if (SymbolTableVector[i].mLabel == s) {
				SymbolTableVector[i].mValue = v;
			}
		}
	}
	else {
		cerr << s << " cannot be set because it does not exist. Now quitting.";
		exit(1);
	}
}

int SymbolTableClass::GetIndex(const std::string & s) {
	//returns the index of where variable <s> is
	//returns -1 if variable <s> is not there
	for (size_t i = 0; i < SymbolTableVector.size(); i++) {
		if (SymbolTableVector[i].mLabel == s) {
			return i;
		}
	}
	return -1;	
}

int SymbolTableClass::GetCount() {
	//returns the current number of variables in the symbol table
	return SymbolTableVector.size();
}