#pragma once

#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

#include "Debug.h"

using namespace std;

enum TokenType {
	// Reserved Words:
	VOID_TOKEN, MAIN_TOKEN, INT_TOKEN, COUT_TOKEN, IFSTATEMENT_TOKEN, WHILESTATEMENT_TOKEN, ENDL_TOKEN,
	// Relational Operators:
	LESS_TOKEN, LESSEQUAL_TOKEN, GREATER_TOKEN, GREATEREQUAL_TOKEN,
	ISEQUAL_TOKEN, NOTEQUAL_TOKEN, AND_TOKEN, OR_TOKEN, SHIFTRIGHT_TOKEN,
	// Other Operators:
	INSERTION_TOKEN, ASSIGNMENT_TOKEN, PLUS_TOKEN, MINUS_TOKEN,
	TIMES_TOKEN, DIVIDE_TOKEN, PLUSEQUAL_TOKEN, MINUSEQUAL_TOKEN,
	// Other Characters:
	SEMICOLON_TOKEN, LPAREN_TOKEN, RPAREN_TOKEN, LCURLY_TOKEN,
	RCURLY_TOKEN,
	// Other Token Types:
	IDENTIFIER_TOKEN, INTEGER_TOKEN,
	BAD_TOKEN, ENDFILE_TOKEN
};

// IMPORTANT: The list above and the list below MUST be kept in sync.
const string gTokenTypeNames[] = {
"VOID", "MAIN", "INT", "COUT", "IF", "WHILE", "ENDL",
"LESS", "LESSEQUAL", "GREATER", "GREATEREQUAL", "EQUAL",
"NOTEQUAL", "AND", "OR", "SHIFTRIGHT",
"INSERTION", "ASSIGNMENT", "PLUS", "MINUS", "TIMES", "DIVIDE", 
"PLUSEQUAL", "MINUSEQUAL",
"SEMICOLON", "LPAREN", "RPAREN", "LCURLY", "RCURLY",
"IDENTIFIER", "INTEGER",
"BAD", "ENDFILE"
};

class TokenClass {
public:
	TokenClass();
	TokenClass(TokenType type, const string & lexeme);
	TokenType GetTokenType() const;

	const string & GetTokenTypeName() const;

	string GetLexeme() const;
	
	void CheckReserved();

	static const string & GetTokenTypeName(TokenType type);

private:
	TokenType mType;
	string mLexeme;

	static char sTokenNames[100][20];
};

ostream & operator<<(ostream & out, const TokenClass & tc);