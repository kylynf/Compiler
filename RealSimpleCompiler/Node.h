#pragma once

//using namespace std;
//#include <cstdlib>
//#include <vector>
//#include <iostream>
//#include <string>
//#include <fstream>

#include "Symbol.h"

//sum1, sum2, sum3 for testing 
class Node;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementGroupNode;
class StatementNode;
class DeclarationStatementNode;
class AssignmentStatementNode;
class CoutStatementNode;
class ExpressionNode;
class IntegerNode;
class IdentifierNode;
class BinaryOperatorNode;
class PlusNode;

class MinusNode;
class TimesNode;
class DivideNode;

//1 true or 0 false
class LessNode;
class LessEqualNode;
class GreaterNode;
class GreaterEqualNode;
class EqualNode;
class NotEqualNode;


class Node {
public:
	virtual ~Node();
	virtual void Interpret()=0;
};

class StartNode : public Node {
public:
	StartNode(ProgramNode* programNode);
	~StartNode();
	virtual void Interpret();

private:
	ProgramNode* mProgramNode;
};

class ProgramNode : public Node {
public:
	ProgramNode(BlockNode* blockNode);
	~ProgramNode();
	virtual void Interpret();

private:
	BlockNode* mBlockNode;

};

class StatementNode : public Node {
};

//redo the block node class so it derives from statement node instead of node
class BlockNode : public StatementNode {
public:
	BlockNode(StatementGroupNode* statementGroupNode);
	~BlockNode();
	virtual void Interpret();

private:
	StatementGroupNode* mStatementGroupNode;
};

class StatementGroupNode : public Node {
public:
	StatementGroupNode();
	void AddStatement(StatementNode* statementNode);
	~StatementGroupNode();
	virtual void Interpret();

private:
	std::vector<StatementNode *> StatementNodeVector;
};


class DeclarationStatementNode : public StatementNode {
public:
	DeclarationStatementNode(IdentifierNode* identifierNode);
	~DeclarationStatementNode();
	virtual void Interpret();

private:
	IdentifierNode * mIdentifierNode;
};

class AssignmentStatementNode : public StatementNode {
public:
	AssignmentStatementNode(IdentifierNode* identifierNode, ExpressionNode* expressionNode);
	~AssignmentStatementNode();
	virtual void Interpret();
private:
	IdentifierNode* mIdentifierNode;
	ExpressionNode* mExpressionNode;
};

class CoutStatementNode : public StatementNode {
public:
	CoutStatementNode(ExpressionNode* expressionNode);
	~CoutStatementNode();
	virtual void Interpret();
private: 
	ExpressionNode* mExpressionNode;
};

//ifstatement

class IfStatementNode : public StatementNode {
public:
	IfStatementNode(ExpressionNode* expressionNode, StatementNode* statementNode);
	virtual void Interpret();
	~IfStatementNode();
private:
	StatementNode* mStatementNode;
	ExpressionNode* mExpressionNode;
};

class WhileStatementNode : public StatementNode {
public:
	WhileStatementNode(ExpressionNode* expressionNode, StatementNode* statementNode);
	virtual void Interpret();
	~WhileStatementNode();
private:
	StatementNode* mStatementNode;
	ExpressionNode* mExpressionNode;
};

class ExpressionNode {
public:
	virtual int Evaluate() = 0;
	virtual ~ExpressionNode() {};
};

class IntegerNode : public ExpressionNode {
public:
	IntegerNode(int number);
	virtual int Evaluate();
	//are we supposed to have an expression node destructor here??
private:
	int mNumber;
};

class IdentifierNode : public ExpressionNode {
public: 
	IdentifierNode(std::string label, SymbolTableClass* symbolTableClass);
	void DeclareVariable();
	void SetValue(int v);
	int GetIndex();
	virtual int Evaluate();
	//are we supposed to have an expression node destructor here??
private:
	SymbolTableClass* mSymbolTable;
	std::string mLabel;
};

class BinaryOperatorNode : public ExpressionNode {
public:
	BinaryOperatorNode(ExpressionNode* left, ExpressionNode* right);
	~BinaryOperatorNode();
protected:
	ExpressionNode* mExpressionNodeOne;
	ExpressionNode* mExpressionNodeTwo;
};

class PlusNode : public BinaryOperatorNode {
public:
	PlusNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {
	};
	virtual int Evaluate();
};

class MinusNode : public BinaryOperatorNode {
public:
	MinusNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {
	};
	virtual int Evaluate();
};

class TimesNode : public BinaryOperatorNode {
public:
	TimesNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {
	};
	virtual int Evaluate();
};

class DivideNode : public BinaryOperatorNode {
public:
	DivideNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {
	};
	virtual int Evaluate();
};

class LessNode : public BinaryOperatorNode {
public:
	LessNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {
	};
	virtual int Evaluate();
};

class GreaterNode : public BinaryOperatorNode {
public:
	GreaterNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {
	};
	virtual int Evaluate();
};

class LessEqualNode : public BinaryOperatorNode {
public:
	LessEqualNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {
	};
	virtual int Evaluate();
};

class GreaterEqualNode : public BinaryOperatorNode {
public:
	GreaterEqualNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {
	};
	virtual int Evaluate();
};

class EqualNode : public BinaryOperatorNode {
public:
	EqualNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {
	};
	virtual int Evaluate();
};

class NotEqualNode : public BinaryOperatorNode {
public:
	NotEqualNode(ExpressionNode* left, ExpressionNode* right) : BinaryOperatorNode(left, right) {
	};
	virtual int Evaluate();
};
