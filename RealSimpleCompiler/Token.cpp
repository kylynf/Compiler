#include "Token.h"

//constructors
TokenClass::TokenClass() {
	//MSG("Initializing TokenClass");
};

TokenClass::TokenClass(TokenType type, const string & lexeme) {
	//MSG("Initializing TokenClass");
	mType = type;
	mLexeme = lexeme;
};

TokenType TokenClass::GetTokenType() const {
	return mType;
}

const string & TokenClass::GetTokenTypeName() const
{
	return gTokenTypeNames[mType];
}

string TokenClass::GetLexeme() const {
	return mLexeme;
}

//checkReserved method:
//change the token type from IDENTIFIER_TOKEN if mLexeme matches one of the reserved words
void TokenClass::CheckReserved()
{
	if(mLexeme == "void"){
		mType = VOID_TOKEN;
	}

	else if(mLexeme == "main"){
		mType = MAIN_TOKEN;
	}

	else if (mLexeme == "int") {
		mType = INT_TOKEN;
	}

	else if (mLexeme == "cout") {
		mType = COUT_TOKEN;
	}

	else if (mLexeme == "if") {
		mType = IFSTATEMENT_TOKEN;
	}

	else if (mLexeme == "while") {
		mType = WHILESTATEMENT_TOKEN;
	}
	else if (mLexeme == "&&") {
		mType = AND_TOKEN;
	}
	else if (mLexeme == "||") {
		mType = OR_TOKEN;
	} 
	else if (mLexeme == ">>") {
		mType = SHIFTRIGHT_TOKEN;
	}
	else if (mLexeme == "<") {
		mType = LESS_TOKEN;
	}
	else if (mLexeme == "true") {
		mType = INTEGER_TOKEN;
		mLexeme = "1";
	}
	else if(mLexeme == "false"){
		mType = INTEGER_TOKEN;
		mLexeme = "0";
	}
	else if (mLexeme == "<=") {
		mType = LESSEQUAL_TOKEN;
	}

	else if (mLexeme == ">") {
		mType = GREATER_TOKEN;
	}

	else if (mLexeme == ">=") {
		mType = GREATEREQUAL_TOKEN;
	}

	else if (mLexeme == "==") {
		mType = ISEQUAL_TOKEN;
	}

	else if (mLexeme == "!=") {
		mType = NOTEQUAL_TOKEN;
	}

	else if (mLexeme == "<<") {
		mType = INSERTION_TOKEN;
	}
	else if (mLexeme == "endl") {
		mType = ENDL_TOKEN;
	}

	else if (mLexeme == "=") {
		mType = ASSIGNMENT_TOKEN;
	}

	else if (mLexeme == "+=") {
		mType = PLUSEQUAL_TOKEN;
	} 

	else if (mLexeme == "-=") {
		mType = MINUSEQUAL_TOKEN;
	}

	else if (mLexeme == "+") {
		mType = PLUS_TOKEN;
	}

	else if (mLexeme == "-") {
		mType = MINUS_TOKEN;
	}

	else if (mLexeme == "*") {
		mType = TIMES_TOKEN;
	}

	else if (mLexeme == "/") {
		mType = DIVIDE_TOKEN;
	}

	else if (mLexeme == ";") {
		mType = SEMICOLON_TOKEN;
	}

	else if (mLexeme == "(") {
		mType = LPAREN_TOKEN;
	}

	else if (mLexeme == ")") {
		mType = RPAREN_TOKEN;
	}

	else if (mLexeme == "{") {
		mType = LCURLY_TOKEN;
	}

	else if (mLexeme == "}") {
		mType = RCURLY_TOKEN;
	}

	//CHECK ME
	/*else if (mLexeme == "identifier") {
		mType = IDENTIFIER_TOKEN;
	}*/

	else if (mLexeme == "0" || mLexeme == "1" || mLexeme == "2" || mLexeme == "3" || mLexeme == "4" || mLexeme == "5" || mLexeme == "6" || mLexeme == "7" || mLexeme == "8" || mLexeme == "9") {
		mType = INTEGER_TOKEN;
	}

	//check me
	else if (mLexeme == "bad") {
		mType = BAD_TOKEN;
	}

	//check me
	/*else if (mLexeme == "identifier") {
		mType = ENDFILE_TOKEN;
	}*/
	
}

const string & TokenClass::GetTokenTypeName(TokenType type)
{
	return gTokenTypeNames[type];
}


ostream & operator<<(ostream & out, const TokenClass & tc) {
	//out << "Token Type: " << tc.GetTokenType() << "Token Name: " << tc.GetTokenTypeName() << "Lexeme: " << tc.GetLexeme();
	const TokenType mytype = tc.GetTokenType();
	const string& myname = tc.GetTokenTypeName(mytype);
	out << "Token type name: " << myname << " " << "Lexeme: " << tc.GetLexeme();
	return out;
}


