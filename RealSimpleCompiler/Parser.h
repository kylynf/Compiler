#pragma once

#include "Scanner.h"
#include "Symbol.h"
#include "Token.h"
#include "Node.h"

class ParserClass {
public:
	ParserClass(ScannerClass* scanner, SymbolTableClass* symboltable);
	StartNode * Start();
private:
	ScannerClass * mScanner;
	SymbolTableClass * mSymbolTable;
	TokenClass Match(TokenType TT);
	ProgramNode * Program();
	BlockNode * Block();
	StatementGroupNode * StatementGroup();
	StatementNode * Statement();
	DeclarationStatementNode * DeclarationStatement();
	AssignmentStatementNode * AssignmentStatement();
	CoutStatementNode * CoutStatement();
	IfStatementNode * IfStatement();
	WhileStatementNode * WhileStatement();
	ExpressionNode * Expression();
	ExpressionNode * Or();
	ExpressionNode * And();
	ExpressionNode * Relational();
	ExpressionNode * PlusMinus();
	ExpressionNode * TimesDivide();
	ExpressionNode * Factor();
	IdentifierNode * Identifier();
	IntegerNode * Integer();
};
