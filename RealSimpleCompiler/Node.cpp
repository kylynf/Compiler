#include "Node.h"

Node::~Node() {

}

StartNode::StartNode(ProgramNode* programNode) {
	mProgramNode = programNode;
}

StartNode::~StartNode() {
	delete mProgramNode;
}

ProgramNode::ProgramNode(BlockNode* blockNode) {
	mBlockNode = blockNode;
}

ProgramNode::~ProgramNode(){
	delete mBlockNode;
}

BlockNode::BlockNode() {
}

StatementGroupNode::StatementGroupNode() {
}

void StatementGroupNode::AddStatement(StatementNode* statementNode){
	StatementNodeVector.push_back(statementNode);
}

StatementGroupNode::~StatementGroupNode() {
	for (int i = 0; i < StatementNodeVector.size(); i++) {
		delete StatementNodeVector[i];
	}
	//vector is automatically deleted
}

StatementNode::StatementNode() {
	//this allows only classes that derive from Statement node to be stored in StatementNodeVector
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
}

CoutStatementNode::CoutStatementNode(ExpressionNode* expressionNode) {
	mExpressionNode = expressionNode;
}

CoutStatementNode::~CoutStatementNode() {
	delete mExpressionNode;
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
