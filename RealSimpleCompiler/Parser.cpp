#include "Parser.h"

ParserClass::ParserClass(ScannerClass* scanner, SymbolTableClass* symboltable) {
	mScanner = scanner;
	mSymbolTable = symboltable;
}

StartNode * ParserClass::Start() {
	ProgramNode * pn = Program();
	Match(ENDFILE_TOKEN);
	StartNode * sn = new StartNode(pn);
	return sn;
}

TokenClass ParserClass::Match(TokenType TT) {
	TokenClass t = mScanner->GetNextToken();
	if (t.GetTokenType() != TT) {
		cerr << "The expected token type is: " << TokenClass::GetTokenTypeName(TT) << "You got " << t.GetTokenTypeName();
		exit(1);
	}
	cout << "Current Token: " << t.GetTokenTypeName() << " successful" << endl;
	cout<< "Lexeme " << t.GetLexeme() << endl;
	return t;
}

//sos
ProgramNode * ParserClass::Program() {
	Match(VOID_TOKEN);
	Match(MAIN_TOKEN);
	Match(LPAREN_TOKEN);
	Match(RPAREN_TOKEN);
	BlockNode * bn = Block();
	ProgramNode * pn = new ProgramNode(bn);
	return pn;
}

//sos
BlockNode * ParserClass::Block() {
	Match(LCURLY_TOKEN);
	StatementGroupNode * sg = StatementGroup();
	Match(RCURLY_TOKEN);
	BlockNode * bn = new BlockNode(sg);
	return bn;
}

StatementGroupNode * ParserClass::StatementGroup() {
	StatementGroupNode * sgn = new StatementGroupNode();
	StatementNode * sn;
	do {
		sn = Statement();
		if (sn) {
			sgn->AddStatement(sn);
		}
	} while (sn);
	return sgn;
}

StatementNode * ParserClass::Statement() {
	TokenClass T = mScanner->PeekNextToken();
	TokenType TT = T.GetTokenType();
	if (TT == INT_TOKEN) {
		DeclarationStatementNode * dsn = DeclarationStatement();
		return dsn;
	}
	else if (TT == IDENTIFIER_TOKEN) {
		AssignmentStatementNode * asn = AssignmentStatement();
		return asn;
	}
	else if (TT == COUT_TOKEN) {
		CoutStatementNode * csn = CoutStatement();
		return csn;
	}
	else if (TT == LCURLY_TOKEN) {
		//BLOCK
		BlockNode * block = Block();
		return block;
	}
	else if (TT == IFSTATEMENT_TOKEN) {
		IfStatementNode * myif = IfStatement();
		return myif;
	}
	else if (TT == WHILESTATEMENT_TOKEN) {
		WhileStatementNode * mywhile = WhileStatement();
		return mywhile;
	}
	else {
		return NULL;
	}
} 

DeclarationStatementNode * ParserClass::DeclarationStatement() {
	Match(INT_TOKEN);
	IdentifierNode * ident = Identifier();
	Match(SEMICOLON_TOKEN);
	DeclarationStatementNode * dsn = new DeclarationStatementNode(ident);
	return dsn;
}

//sos
AssignmentStatementNode * ParserClass::AssignmentStatement() {
	IdentifierNode * ident = Identifier();
	TokenClass T = mScanner->PeekNextToken();
	if (T.GetTokenType() == PLUSEQUAL_TOKEN) {
		Match(T.GetTokenType());
		ExpressionNode * exp = Expression();
		Match(SEMICOLON_TOKEN);
		AssignmentStatementNode * asn = new PlusEqualNode(ident, exp);
		return asn;
	}
	if (T.GetTokenType() == MINUSEQUAL_TOKEN) {
		Match(T.GetTokenType());
		ExpressionNode * exp = Expression();
		Match(SEMICOLON_TOKEN);
		AssignmentStatementNode * asn = new MinusEqualNode(ident, exp);
		return asn;
	}
	Match(T.GetTokenType());
	ExpressionNode * exp = Expression();
	Match(SEMICOLON_TOKEN);
	AssignmentStatementNode * asn = new AssignmentStatementNode(ident, exp);
	return asn;
}

//sos
CoutStatementNode * ParserClass::CoutStatement() {
	Match(COUT_TOKEN);
	CoutStatementNode * csn = new CoutStatementNode();
	while (true) {
		Match(INSERTION_TOKEN);
		TokenClass T = mScanner->PeekNextToken();
		if (T.GetTokenType() == ENDL_TOKEN) {
			Match(T.GetTokenType());
			csn->AddStatement(NULL);
			TokenClass T = mScanner->PeekNextToken();
			if (T.GetTokenType() == INSERTION_TOKEN) {
				continue;
			}
			else {
				Match(SEMICOLON_TOKEN);
				return csn;
			}
		}
		ExpressionNode * exp = Expression();
		csn->AddStatement(exp);
		//TokenClass T = mScanner->PeekNextToken();
		if (T.GetTokenType() == INSERTION_TOKEN) {
			continue;
		}
		if (T.GetTokenType() == SEMICOLON_TOKEN) {
			Match(SEMICOLON_TOKEN);
			return csn;
		}
		
	}
}

IfStatementNode * ParserClass::IfStatement() {
	Match(IFSTATEMENT_TOKEN);
	Match(LPAREN_TOKEN);
	ExpressionNode * exp = Expression();
	Match(RPAREN_TOKEN);
	StatementNode * state = Statement();
	IfStatementNode * myif = new IfStatementNode(exp, state);
	return myif;
}

WhileStatementNode * ParserClass::WhileStatement() {
	Match(WHILESTATEMENT_TOKEN);
	Match(LPAREN_TOKEN);
	ExpressionNode * exp = Expression();
	Match(RPAREN_TOKEN);
	StatementNode *state = Statement();
	WhileStatementNode * mywhile = new WhileStatementNode(exp, state);
	return mywhile;
}

//SOS
ExpressionNode * ParserClass::Expression() {
	return Or();
}

ExpressionNode * ParserClass::Or() {
	ExpressionNode * current = And();
	while (true) {
		TokenClass T = mScanner->PeekNextToken();
		if (T.GetTokenType() == OR_TOKEN) {
			Match(T.GetTokenType());
			current = new OrNode(current, And());
		}
		else {
			return current;
		}
	}
}

ExpressionNode * ParserClass::And() {
	ExpressionNode * current = Relational();

	while (true) {
		TokenClass T = mScanner->PeekNextToken();
		if (T.GetTokenType() == AND_TOKEN) {
			Match(T.GetTokenType());
			current = new AndNode(current, Relational());
		}
		else {
			return current;
		}
	}
}

ExpressionNode * ParserClass::Relational() {
	ExpressionNode * current = PlusMinus();

	//Handle the optional tail
	TokenClass T = mScanner->PeekNextToken();
	if (T.GetTokenType() == LESS_TOKEN) {
		Match(T.GetTokenType());
		current = new LessNode(current, PlusMinus());
	}
	else if (T.GetTokenType() == LESSEQUAL_TOKEN) {
		Match(T.GetTokenType());
		current = new LessEqualNode(current, PlusMinus());
	}
	else if (T.GetTokenType() == GREATER_TOKEN) {
		Match(T.GetTokenType());
		current = new GreaterNode(current, PlusMinus());
	}
	else if (T.GetTokenType() == GREATEREQUAL_TOKEN) {
		Match(T.GetTokenType());
		current = new GreaterEqualNode(current, PlusMinus());
	}
	else if (T.GetTokenType() == ISEQUAL_TOKEN) {
		Match(T.GetTokenType());
		current = new EqualNode(current, PlusMinus());
	}
	else if (T.GetTokenType() == NOTEQUAL_TOKEN) {
		Match(T.GetTokenType());
		current = new NotEqualNode(current, PlusMinus());
	}
	return current;
}

ExpressionNode * ParserClass::PlusMinus() {
	ExpressionNode * current = TimesDivide();
	while (true) {
		TokenClass T = mScanner->PeekNextToken();

		if (T.GetTokenType() == PLUS_TOKEN) {
			Match(T.GetTokenType());
			current = new PlusNode(current, TimesDivide());

		}
		else if (T.GetTokenType() == MINUS_TOKEN) {
			Match(T.GetTokenType());
			current = new MinusNode(current, TimesDivide());
		}
		else {
			//here the book has an else statement but doesnt make sense to have else statement bc current wouldnt be returned
			return current;
		}
	}
}

ExpressionNode * ParserClass::TimesDivide() {
	ExpressionNode * current = Factor();
	while (true) {
		TokenClass T = mScanner->PeekNextToken();

		if (T.GetTokenType() == TIMES_TOKEN) {
			Match(T.GetTokenType());
			current = new TimesNode(current, Factor());

		}
		else if (T.GetTokenType() == DIVIDE_TOKEN) {
			Match(T.GetTokenType());
			current = new DivideNode(current, Factor());
		}
		else {
			//here the book has an else statement but doesnt make sense to have else statement bc current wouldnt be returned
			return current;
		}
	}
}

//sos
ExpressionNode * ParserClass::Factor() {
	TokenClass T = mScanner->PeekNextToken();

	if (T.GetTokenType() == IDENTIFIER_TOKEN) {
		return Identifier();

	}
	else if (T.GetTokenType() == INTEGER_TOKEN) {
		return Integer();
	}
	//CHECK ME FOR PARSER2
	else if (T.GetTokenType() == LPAREN_TOKEN) {
		//this should be lparen token
		Match(T.GetTokenType());
		ExpressionNode * exp = Expression();
		Match(RPAREN_TOKEN);
		return exp;
		//return what expression returns
	}
	else {
		cerr << "The factor method did not see one of the three token types";
		exit(1);
	}
	
}

//identifier node takes a label and symbol table as parameters??
IdentifierNode * ParserClass::Identifier() {
	TokenClass tc = Match(IDENTIFIER_TOKEN);
	return new IdentifierNode(tc.GetLexeme(), mSymbolTable);
}

//sos
//integernode takes a number as a parameter
IntegerNode * ParserClass::Integer() {
	TokenClass tc = Match(INTEGER_TOKEN);
	//string s = tc.GetLexeme();
	//const char * c = s.c_str();

	return new IntegerNode(atoi(tc.GetLexeme().c_str()));
}