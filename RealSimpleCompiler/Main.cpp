//#include "Scanner.h"

#include "Symbol.h"

int main() {
	/*TokenType tt = VOID_TOKEN;
	string lexeme = "void";
	TokenClass tok1(tt, lexeme);

	cout << tok1 << endl;

	return 0;*/

	//===========================================

	/*ScannerClass S("code.txt");

	TokenClass T;

	do {
		T = S.GetNextToken();
		cout << S.GetLineNumber();
		cout << T << endl;
	} while (T.GetTokenType() != ENDFILE_TOKEN);
	return 0;*/

	//============================================

	SymbolTableClass symbol;
	
	symbol.AddEntry("apple");
	cout << "apple was added" << endl;

	cout << "count " << symbol.GetCount() << endl;

	if (symbol.Exists("apple")) {
		cout << "the apple exists"<< endl;
	}
	else {
		cout << "error" << endl;
	}

	symbol.SetValue("apple", 5);
	cout << "apple was set to 5" << endl;


	if (symbol.GetValue("apple") == 5) {
		cout << "the values match" << endl;
	}
	else {
		cout << "error the value is " << symbol.GetValue("apple") << "its supposed to be 5" <<endl;
 
	}

	cout << "apple index " << symbol.GetIndex("apple") << endl;

	cout << "the count is " << symbol.GetCount() << endl;

	//this should throw an error
	//cout << symbol.GetValue("banana") << endl;

	//this should throw an error
	//symbol.SetValue("orange", 90);

	//this should throw an error
	symbol.AddEntry("apple");
	
	return 0;

}