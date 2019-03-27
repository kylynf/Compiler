#include "Node.h"

Node::~Node() {

}

StartNode::StartNode(ProgramNode* programNode) {
	mProgramNode = programNode;
}

void StartNode::Interpret() {
	mProgramNode->Interpret();
	MSG("Start node called interpret on program node");
}

StartNode::~StartNode() {
	delete mProgramNode;
	MSG("Start node destructor deleted program node");
}

ProgramNode::ProgramNode(BlockNode* blockNode) {
	mBlockNode = blockNode;
}

void ProgramNode::Interpret() {
	mBlockNode->Interpret();
	MSG("Program node called interpret on block node");
}

ProgramNode::~ProgramNode(){
	delete mBlockNode;
	MSG("Program node destructor deleted Block Node");
}

BlockNode::BlockNode(StatementGroupNode* statementGroupNode) {
	mStatementGroupNode = statementGroupNode;
}

void BlockNode::Interpret() {
	mStatementGroupNode->Interpret();
	MSG("Block node called interpret on statementgroup");
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

void StatementGroupNode::Interpret() {
	for (size_t i = 0; i < StatementNodeVector.size(); i++) {
		StatementNodeVector[i]->Interpret();
	}
	MSG("Statement Group called interpret on the statement node vector");
}

DeclarationStatementNode::DeclarationStatementNode(IdentifierNode* identifierNode) {
	mIdentifierNode = identifierNode;
}

void DeclarationStatementNode::Interpret() {
	mIdentifierNode->DeclareVariable();
	MSG("Declaration statement called declare variable on midentifiernode");
}

DeclarationStatementNode::~DeclarationStatementNode() {
	delete mIdentifierNode;
}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode* identifierNode, ExpressionNode* expressionNode) {
	mIdentifierNode = identifierNode;
	mExpressionNode = expressionNode;
}

void AssignmentStatementNode::Interpret() {
	int value = mExpressionNode->Evaluate();
	mIdentifierNode->SetValue(value);
	MSG("Assignment statement node set the value on the identifier node");
}

AssignmentStatementNode::~AssignmentStatementNode() {
	delete mIdentifierNode;
	delete mExpressionNode;
	MSG("Assignment statement node destructor deleted identifier node and expression node");
}

CoutStatementNode::CoutStatementNode(ExpressionNode* expressionNode) {
	mExpressionNode = expressionNode;
}

void CoutStatementNode::Interpret() {
	int answer = mExpressionNode->Evaluate();
	cout << "The answer is " << answer << std::endl;
	//cout << "Evaluate returned" << answer;
	//carriage return
	cout << '\r';
	MSG("Cout interpret ran");
}

CoutStatementNode::~CoutStatementNode() {
	delete mExpressionNode;
	MSG("Cout statement deleted expression node");
}

IfStatementNode::IfStatementNode(ExpressionNode* expressionNode, StatementNode* statementNode) {
	mStatementNode = statementNode;
	mExpressionNode = expressionNode;
}

void IfStatementNode::Interpret() {
	if (mExpressionNode->Evaluate()) {
		mStatementNode->Interpret();
	}
	MSG("IF statement node called interpret on mstatement node");
}

IfStatementNode::~IfStatementNode() {
	delete mExpressionNode;
	delete mStatementNode;
	MSG("If statement deleted expression node");
	MSG("If statement deleted statement node");
}

WhileStatementNode::WhileStatementNode(ExpressionNode* expressionNode, StatementNode* statementNode) {
	mStatementNode = statementNode;
	mExpressionNode = expressionNode;
}

void WhileStatementNode::Interpret() {
	while (mExpressionNode->Evaluate()) {
		mStatementNode->Interpret();
	}
	MSG("While statement node called interpret on statement node");
}

WhileStatementNode::~WhileStatementNode() {
	delete mExpressionNode;
	delete mStatementNode;
	MSG("If statement deleted expression node");
	MSG("If statement deleted statement node");
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

int OrNode::Evaluate() {
	if (mExpressionNodeOne->Evaluate() || mExpressionNodeTwo->Evaluate()) {
		return 1;
	}
	else {
		return 0;
	}
}

int AndNode::Evaluate() {
	if (mExpressionNodeOne->Evaluate() && mExpressionNodeTwo->Evaluate()) {
		return 1;
	}
	else {
		return 0;
	}
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
