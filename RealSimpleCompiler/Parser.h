#pragma once

#include "Scanner.h"
#include "Symbol.h"
#include "Token.h"

class ParserClass {
public:
	ParserClass(ScannerClass* scanner, SymbolTableClass* symboltable);
	void Start();
	/*void Match(TokenType TT);
	void Program();
	void Block();
	void StatementGroup();
	bool Statement();
	void DeclarationStatement();
	void AssignmentStatement();
	void CoutStatement();
	void Expression();
	void Relational();
	void PlusMinus();
	void TimesDivide();
	void Factor();
	void Identifier();
	void Integer();*/
private:
	ScannerClass * mScanner;
	SymbolTableClass * mSymbolTable;
	void Match(TokenType TT);
	void Program();
	void Block();
	void StatementGroup();
	bool Statement();
	void DeclarationStatement();
	void AssignmentStatement();
	void CoutStatement();
	void Expression();
	void Relational();
	void PlusMinus();
	void TimesDivide();
	void Factor();
	void Identifier();
	void Integer();
};
