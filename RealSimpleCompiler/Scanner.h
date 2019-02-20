#pragma once

#include "Token.h"
#include "StateMachine.h"

using namespace std;

class ScannerClass {
public:
	ScannerClass(string input);
	~ScannerClass(void);

	TokenClass GetNextToken();
	int GetLineNumber();

private:
	ifstream mFin;
	int mLineNumber;
};