#include "Parser.h"

ParserClass::ParserClass(ScannerClass* scanner, SymbolTableClass* symboltable) {
	mScanner = scanner;
	mSymbolTable = symboltable;
}

void ParserClass::Start() {
	Program();
	Match(ENDFILE_TOKEN);
}

void ParserClass::Match(TokenType TT) {
	TokenClass t = mScanner->GetNextToken();
	if (t.GetTokenType() != TT) {
		cerr << "Sorry your token types dont match";
		exit(1);
	}
	return;
}

void ParserClass::Program() {
	Match(VOID_TOKEN);
	Match(MAIN_TOKEN);
	Match(LPAREN_TOKEN);
	Match(RPAREN_TOKEN);
	Block();
}

void ParserClass::Block() {
	Match(LCURLY_TOKEN);
	StatementGroup();
	Match(RCURLY_TOKEN);
}

void ParserClass::StatementGroup() {
	bool found;
	do {
		found = Statement();
	} while (found == true);
}

bool ParserClass::Statement() {
	TokenClass T = mScanner->PeekNextToken();
	TokenType TT = T.GetTokenType();
	if (TT == INT_TOKEN) {
		DeclarationStatement();
		return true;
	}
	else if (TT == IDENTIFIER_TOKEN) {
		AssignmentStatement();
		return true;
	}
	else if (TT == COUT_TOKEN) {
		CoutStatement();
		return true;
	}
	else {
		return false;
	}
} 

void ParserClass::DeclarationStatement() {
	Match(INT_TOKEN);
	Identifier();
	Match(SEMICOLON_TOKEN);
}

void ParserClass::AssignmentStatement() {
	Identifier();
	Match(ASSIGNMENT_TOKEN);
	Expression();
	Match(SEMICOLON_TOKEN);
}

void ParserClass::CoutStatement() {
	Match(COUT_TOKEN);
	Expression();
	Match(SEMICOLON_TOKEN);
}

void ParserClass::Expression() {
	Relational();
}

void ParserClass::Relational() {
	PlusMinus();

	//Handle the optional tail
	TokenClass T = mScanner->PeekNextToken();
	if (T.GetTokenType() == LESS_TOKEN) {
		Match(T.GetTokenType());
		PlusMinus();
	}
	else if (T.GetTokenType() == LESSEQUAL_TOKEN) {
		Match(T.GetTokenType());
		PlusMinus();
	}
	else if (T.GetTokenType() == GREATER_TOKEN) {
		Match(T.GetTokenType());
		PlusMinus();
	}
	else if (T.GetTokenType() == GREATEREQUAL_TOKEN) {
		Match(T.GetTokenType());
		PlusMinus();
	}
	else if (T.GetTokenType() == ISEQUAL_TOKEN) {
		Match(T.GetTokenType());
		PlusMinus();
	}
	else if (T.GetTokenType() == NOTEQUAL_TOKEN) {
		Match(T.GetTokenType());
		PlusMinus();
	}
	else {
		return;
	}
}

void ParserClass::PlusMinus() {
	TimesDivide();
	while (true) {
		TokenClass T = mScanner->PeekNextToken();

		if (T.GetTokenType() == PLUS_TOKEN) {
			Match(T.GetTokenType());
			TimesDivide();

		}
		else if (T.GetTokenType() == MINUS_TOKEN) {
			Match(T.GetTokenType());
			TimesDivide();
		}
		else {
			return;
		}
	}
}

void ParserClass::TimesDivide() {
	Factor();
	while (true) {
		TokenClass T = mScanner->PeekNextToken();

		if (T.GetTokenType() == TIMES_TOKEN) {
			Match(T.GetTokenType());
			Factor();

		}
		else if (T.GetTokenType() == DIVIDE_TOKEN) {
			Match(T.GetTokenType());
			Factor();
		}
		else {
			return;
		}
	}
}

void ParserClass::Factor() {
	TokenClass T = mScanner->PeekNextToken();

	if (T.GetTokenType() == IDENTIFIER_TOKEN) {
		Match(T.GetTokenType());
		Identifier();

	}
	else if (T.GetTokenType() == INTEGER_TOKEN) {
		Match(T.GetTokenType());
		Integer();
	}
	else if (T.GetTokenType() == LPAREN_TOKEN) {
		//this should be lparen token
		Match(T.GetTokenType());
		Expression();
		Match(RPAREN_TOKEN);
	}
	else {
		cerr << "The factor method did not see one of the three token types";
		exit(1);
	}
	
}

void ParserClass::Identifier() {
	TokenClass T = mScanner->PeekNextToken();
	Match(T.GetTokenType());
}

void ParserClass::Integer() {
	TokenClass T = mScanner->PeekNextToken();
	Match(T.GetTokenType());
}