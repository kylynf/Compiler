#pragma once

using namespace std;
#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

class Node {
public:
	virtual ~Node();
};

class StartNode : public Node {
public:
	StartNode(ProgramNode* programNode);
	~StartNode();

private:
	ProgramNode* mProgramNode;
};

//CHECK ME
class ProgramNode : public Node {
public:
	ProgramNode(BlockNode* blockNode);
	~ProgramNode();

private:
	BlockNode* mBlockNode;

};

class BlockNode : public StatementGroupNode {
	BlockNode();
};

class StatementGroupNode : public Node {
public:
	StatementGroupNode();
	void AddStatement(StatementNode* statementNode);
	~StatementGroupNode();

private:
	std::vector<StatementNode *> StatementNodeVector;
};

class StatementNode : public Node {
public:
	StatementNode();
};

class DeclarationStatementNode : public StatementNode {
public:
	DeclarationStatementNode(IdentiferNode* identifierNode);
	~DeclarationStatementNode();

private:
	IdentifierNode* mIdentifierNode;
};

class AssignmentStatementNode : public StatementNode {
public:
	AssignmentStatementNode(IdentifierNode* identifierNode, ExpressionNode* expressionNode);
	~AssignmentStatementNode();
private:
	IdentifierNode* mIdentifierNode;
	ExpressionNode* mExpressionNode;

};
