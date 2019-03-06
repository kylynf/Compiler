#include "Node.h"

Node::~Node() {

}

StartNode::StartNode(ProgramNode* programNode) {
	mProgramNode = programNode;
}

StartNode::~StartNode() {
	delete mProgramNode;
	MSG("Start node destructor deleted program node");
}

ProgramNode::ProgramNode(BlockNode* blockNode) {
	mBlockNode = blockNode;
}

ProgramNode::~ProgramNode(){
	delete mBlockNode;
	MSG("Program node destructor deleted Block Node");
}

BlockNode::BlockNode(StatementGroupNode* statementGroupNode) {
	mStatementGroupNode = statementGroupNode;
}

BlockNode::~BlockNode() {
	delete mStatementGroupNode;
	MSG("DELETE STATEMENT GROUP NODE");
}

StatementGroupNode::StatementGroupNode() {
}

void StatementGroupNode::AddStatement(StatementNode* statementNode){
	StatementNodeVector.push_back(statementNode);
}

StatementGroupNode::~StatementGroupNode() {
	for (size_t i = 0; i < StatementNodeVector.size(); i++) {
		delete StatementNodeVector[i];
	}
	MSG("Group node destructor cleared vector");
	//vector is automatically deleted
}

DeclarationStatementNode::DeclarationStatementNode(IdentifierNode* identifierNode) {
	mIdentifierNode = identifierNode;
}

DeclarationStatementNode::~DeclarationStatementNode() {
	delete mIdentifierNode;
}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode* identifierNode, ExpressionNode* expressionNode) {
	mIdentifierNode = identifierNode;
	mExpressionNode = expressionNode;
}

AssignmentStatementNode::~AssignmentStatementNode() {
	delete mIdentifierNode;
	delete mExpressionNode;
	MSG("Assignment statement node destructor deleted identifier node and expression node");
}

CoutStatementNode::CoutStatementNode(ExpressionNode* expressionNode) {
	mExpressionNode = expressionNode;
}

CoutStatementNode::~CoutStatementNode() {
	delete mExpressionNode;
	MSG("Cout statement deleted expression node");
}

IntegerNode::IntegerNode(int number) {
	mNumber = number;
}

int IntegerNode::Evaluate() {
	return mNumber;
}

IdentifierNode::IdentifierNode(std::string label, SymbolTableClass* symbolTableClass) {
	mSymbolTable = symbolTableClass;
	mLabel = label;
}

void IdentifierNode::DeclareVariable() {
	mSymbolTable->AddEntry(mLabel);
}

void IdentifierNode::SetValue(int v) {
	mSymbolTable->SetValue(mLabel, v);
}

int IdentifierNode::GetIndex() {
	return mSymbolTable->GetIndex(mLabel);
}

int IdentifierNode::Evaluate() {
	return mSymbolTable->GetValue(mLabel);
}

BinaryOperatorNode::BinaryOperatorNode(ExpressionNode* expressionNode1, ExpressionNode* expressionNode2) {
	mExpressionNodeOne = expressionNode1;
	mExpressionNodeTwo = expressionNode2;
}

BinaryOperatorNode::~BinaryOperatorNode() {
	delete mExpressionNodeOne;
	delete mExpressionNodeTwo;
	MSG("binary operator node deleted expression node one");
	MSG("binary operator node delete expression node two");
}


//recursively call evaluate on left and right children
//return the sum of their return values
int PlusNode::Evaluate() {
	return mExpressionNodeOne->Evaluate() + mExpressionNodeTwo->Evaluate();

}

int MinusNode::Evaluate() {
	return mExpressionNodeOne->Evaluate() - mExpressionNodeTwo->Evaluate();

}

int TimesNode::Evaluate() {
	return mExpressionNodeOne->Evaluate() * mExpressionNodeTwo->Evaluate();

}

int DivideNode::Evaluate() {
	return mExpressionNodeOne->Evaluate() / mExpressionNodeTwo->Evaluate();

}


int LessNode::Evaluate() {
	if (mExpressionNodeOne->Evaluate() < mExpressionNodeTwo->Evaluate()) {
		return 1;
	}
	else {
		return 0;
	}
}

int GreaterNode::Evaluate() {
	if (mExpressionNodeOne->Evaluate() > mExpressionNodeTwo->Evaluate()) {
		return 1;
	}
	else {
		return 0;
	}
}

int LessEqualNode::Evaluate() {
	if (mExpressionNodeOne->Evaluate() <= mExpressionNodeTwo->Evaluate()) {
		return 1;
	}
	else {
		return 0;
	}
}

int GreaterEqualNode::Evaluate() {
	if (mExpressionNodeOne->Evaluate() >= mExpressionNodeTwo->Evaluate()) {
		return 1;
	}
	else {
		return 0;
	}
}

int EqualNode::Evaluate() {
	if (mExpressionNodeOne->Evaluate() == mExpressionNodeTwo->Evaluate()) {
		return 1;
	}
	else {
		return 0;
	}
}

int NotEqualNode::Evaluate() {
	if (mExpressionNodeOne->Evaluate() != mExpressionNodeTwo->Evaluate()) {
		return 1;
	}
	else {
		return 0;
	}
}
