//#include "Scanner.h"
//#include "Symbol.h"
#include "Symbol.h"
#include "Node.h"

int main() {
	SymbolTableClass symbol;

	IntegerNode *myinteger = new IntegerNode(4);
	IntegerNode *mysecondinteger = new IntegerNode(5);

	//abstract expression node??

	//abstract another expression node??

	PlusNode * plus = new PlusNode(myinteger, mysecondinteger);


	IdentifierNode * identifier = new IdentifierNode("sum", &symbol);
	AssignmentStatementNode * assignment = new AssignmentStatementNode(identifier, plus);

	//group
	StatementGroupNode * statementgroup = new StatementGroupNode();
	statementgroup->AddStatement(assignment);
	
	//block
	BlockNode * block = new BlockNode(statementgroup);

	//program
	ProgramNode * program = new ProgramNode(block);
	
	//delete StartNode
	StartNode * start = new StartNode(program);

	delete start;
	
	return 0;

}