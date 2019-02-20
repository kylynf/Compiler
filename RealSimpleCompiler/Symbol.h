#pragma once

#include "Token.h"

using namespace std;

class SymbolTableClass {
	struct Variable {
		string mLabel;
		int mValue;
	};

public:
	bool Exists(const std::string & s);
	
	void AddEntry(const std::string & s);

	int GetValue(const std::string & s);

	void SetValue(const std::string & s, int v);

	int GetIndex(const std::string & s);

	int GetCount();

private:
	//symbol table vector??
	std::vector<Variable> SymbolTableVector;

};