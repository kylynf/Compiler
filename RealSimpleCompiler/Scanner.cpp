#include "Scanner.h"

ScannerClass::ScannerClass(string input) {
	MSG("Initializing ScannerClass object");
	mLineNumber = 1;
	mFin.open(input);
	if (!mFin.is_open()) {
		cerr << "Error opening file!";
		exit(1);
	}

}

ScannerClass::~ScannerClass(void) {
	mFin.close();
}

int ScannerClass::GetLineNumber() {
	return mLineNumber;
}


TokenClass ScannerClass::GetNextToken() {
	TokenType TT;
	StateMachineClass SM;

	string lexeme;

	MachineState state;

	char c;

	do {
		c = mFin.get();
		if( c == '\n'){
			mLineNumber += 1;
		}
		lexeme += c;
		state = SM.UpdateState(c, TT);
		if (state == START_STATE) {
			lexeme = "";
		}
	} while (state != CANTMOVE_STATE);
		mFin.unget();
		//decrement the line number if c == \n
		if (c == '\n'){
			mLineNumber -= 1;
		}
		lexeme.pop_back();
		if (TT == BAD_TOKEN) {
			cerr << "The lexeme made a bad token: " << lexeme;
			exit(1);
		}
		TokenClass T(TT, lexeme);
		T.CheckReserved();
		return T;
}

TokenClass ScannerClass::PeekNextToken() {
	long long fileoffset;

	int line;

	fileoffset = mFin.tellg();
	line = GetLineNumber();

	TokenClass tc = GetNextToken();

	if (!mFin) {
		mFin.clear();
	}

	//reset the get position of mFin and the current line number to where they were

	mFin.seekg(fileoffset);
	mLineNumber = line;

	return tc;
	//what should this return?
		
	
}