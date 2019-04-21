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

void StartNode::Code(InstructionsClass &mycode) {
	mProgramNode->Code(mycode);
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

void ProgramNode::Code(InstructionsClass &mycode) {
	mBlockNode->Code(mycode);
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

void BlockNode::Code(InstructionsClass &mycode){
	mStatementGroupNode->Code(mycode);
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

void StatementGroupNode::Code(InstructionsClass & mycode) {
	for (size_t i = 0; i < StatementNodeVector.size(); i++) {
		StatementNodeVector[i]->Code(mycode);
	}
	MSG("Statement Group called code on the statement node vector");
}

DeclarationStatementNode::DeclarationStatementNode(IdentifierNode* identifierNode) {
	mIdentifierNode = identifierNode;
}

void DeclarationStatementNode::Interpret() {
	mIdentifierNode->DeclareVariable();
	MSG("Declaration statement called declare variable on midentifiernode");
}

void DeclarationStatementNode::Code(InstructionsClass &code) {
	mIdentifierNode->DeclareVariable();
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


void AssignmentStatementNode::Code(InstructionsClass & mycode) {
	mExpressionNode->CodeEvaluate(mycode);
	int index = mIdentifierNode->GetIndex();
	mycode.PopAndStore(index);
}

AssignmentStatementNode::~AssignmentStatementNode() {
	delete mIdentifierNode;
	delete mExpressionNode;
	MSG("Assignment statement node destructor deleted identifier node and expression node");
}

CoutStatementNode::CoutStatementNode()
{
	MSG("cout is initializing");
}

void CoutStatementNode::Interpret() {
	for (int i = 0; i < mExpressionNodeVector.size(); i++) {
		if (mExpressionNodeVector[i] == NULL) {
			std::cout << std::endl;
			continue;
		}
		int answer = mExpressionNodeVector[i]->Evaluate();
		cout << "The answer is " << answer << std::endl;
		//cout << "Evaluate returned" << answer;
		//carriage return
		//cout << '\r';
	}

	MSG("Cout interpret ran");
}

void CoutStatementNode::AddStatement(ExpressionNode * expressionNode) {
	mExpressionNodeVector.push_back(expressionNode);
}

void CoutStatementNode::Code(InstructionsClass & mycode) {
	for (int i = 0; i < mExpressionNodeVector.size(); i++) {
		if (mExpressionNodeVector[i] == NULL) {
			mycode.WriteEndl();
			continue;
		}
		mExpressionNodeVector[i]->CodeEvaluate(mycode);
		mycode.PopAndWrite();
	}
}

CoutStatementNode::~CoutStatementNode() {
	for (int i = 0; i < mExpressionNodeVector.size(); i++) {
		delete mExpressionNodeVector[i];
		MSG("deleting coutstatementnode");
	}
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

void IfStatementNode::Code(InstructionsClass & mycode) {
	mExpressionNode->CodeEvaluate(mycode);
	unsigned char * JumpAddress = mycode.SkipIfZeroStack();
	unsigned char * a1 = mycode.GetAddress();
	mStatementNode->Code(mycode);
	unsigned char * a2 = mycode.GetAddress();
	mycode.SetOffset(JumpAddress, int(a2 - a1));
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

//fixme
void WhileStatementNode::Code(InstructionsClass & mycode) {
	unsigned char * a0 = mycode.GetAddress();
	mExpressionNode->CodeEvaluate(mycode);
	unsigned char * JumpAddress1 = mycode.SkipIfZeroStack();
	unsigned char * a1 = mycode.GetAddress();
	mStatementNode->Code(mycode);
	unsigned char * JumpAddress2 = mycode.Jump();
	unsigned char * a2 = mycode.GetAddress();
	mycode.SetOffset(JumpAddress1, int(a2 - a1));
	mycode.SetOffset(JumpAddress2, int(a0 - a2));
}

WhileStatementNode::~WhileStatementNode() {
	delete mExpressionNode;
	delete mStatementNode;
	MSG("while statement deleted expression node");
	MSG("while statement deleted statement node");
}

IntegerNode::IntegerNode(int number) {
	mNumber = number;
}

int IntegerNode::Evaluate() {
	return mNumber;
}

void IntegerNode::CodeEvaluate(InstructionsClass & code) {
	code.PushValue(mNumber);
}

IdentifierNode::IdentifierNode(std::string label, SymbolTableClass* symbolTableClass) {
	mSymbolTable = symbolTableClass;
	mLabel = label;
}

void IdentifierNode::DeclareVariable() {
	mSymbolTable->AddEntry(mLabel);
}

void IdentifierNode::CodeEvaluate(InstructionsClass & mycode) {
	int index = GetIndex();
	mycode.PushVariable(index);
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

void OrNode::CodeEvaluate(InstructionsClass & mycode) {
	mExpressionNodeOne->CodeEvaluate(mycode);
	mExpressionNodeTwo->CodeEvaluate(mycode);
	mycode.PopPopOrPush();
}

int AndNode::Evaluate() {
	if (mExpressionNodeOne->Evaluate() && mExpressionNodeTwo->Evaluate()) {
		return 1;
	}
	else {
		return 0;
	}
}

void AndNode::CodeEvaluate(InstructionsClass & mycode) {
	mExpressionNodeOne->CodeEvaluate(mycode);
	mExpressionNodeTwo->CodeEvaluate(mycode);
	mycode.PopPopAndPush();
}

PlusEqualNode::PlusEqualNode(IdentifierNode* identifierNode, ExpressionNode * expressionNode) :AssignmentStatementNode(identifierNode, expressionNode)
{
	mExpressionNode = expressionNode;
	mIdentifierNode = identifierNode;
}

void PlusEqualNode::Interpret() {
	int value = mExpressionNode->Evaluate();
	mIdentifierNode->SetValue(mIdentifierNode->Evaluate() + value);
}

void PlusEqualNode::Code(InstructionsClass & mycode) {
	mIdentifierNode->CodeEvaluate(mycode);
	mExpressionNode->CodeEvaluate(mycode);
	mycode.PopPopAddPush();
	int index = mIdentifierNode->GetIndex();
	mycode.PopAndStore(index);
}


MinusEqualNode::MinusEqualNode(IdentifierNode* identifierNode, ExpressionNode * expressionNode) :AssignmentStatementNode(identifierNode, expressionNode) 
{
	mExpressionNode = expressionNode;
	mIdentifierNode = identifierNode;
}

void MinusEqualNode::Interpret() {
	int value = mExpressionNode->Evaluate();
	mIdentifierNode->SetValue(mIdentifierNode->Evaluate() - value);
}

void MinusEqualNode::Code(InstructionsClass & mycode) {
	mIdentifierNode->CodeEvaluate(mycode);
	mExpressionNode->CodeEvaluate(mycode);
	mycode.PopPopAddPush();
	int index = mIdentifierNode->GetIndex();
	mycode.PopAndStore(index);
}

//recursively call evaluate on left and right children
//return the sum of their return values
int PlusNode::Evaluate() {
	return mExpressionNodeOne->Evaluate() + mExpressionNodeTwo->Evaluate();
}

void PlusNode::CodeEvaluate(InstructionsClass & mycode) {
	mExpressionNodeOne->CodeEvaluate(mycode);
	mExpressionNodeTwo->CodeEvaluate(mycode);
	mycode.PopPopAddPush();
}

int MinusNode::Evaluate() {
	return mExpressionNodeOne->Evaluate() - mExpressionNodeTwo->Evaluate();
}

void MinusNode::CodeEvaluate(InstructionsClass & mycode) {
	mExpressionNodeOne->CodeEvaluate(mycode);
	mExpressionNodeTwo->CodeEvaluate(mycode);
	mycode.PopPopSubPush();
}

int TimesNode::Evaluate() {
	return mExpressionNodeOne->Evaluate() * mExpressionNodeTwo->Evaluate();

}

void TimesNode::CodeEvaluate(InstructionsClass & mycode) {
	mExpressionNodeOne->CodeEvaluate(mycode);
	mExpressionNodeTwo->CodeEvaluate(mycode);
	mycode.PopPopMulPush();
}

int DivideNode::Evaluate() {
	return mExpressionNodeOne->Evaluate() / mExpressionNodeTwo->Evaluate();
}

void DivideNode::CodeEvaluate(InstructionsClass & mycode) {
	mExpressionNodeOne->CodeEvaluate(mycode);
	mExpressionNodeTwo->CodeEvaluate(mycode);
	mycode.PopPopDivPush();
}


int LessNode::Evaluate() {
	if (mExpressionNodeOne->Evaluate() < mExpressionNodeTwo->Evaluate()) {
		return 1;
	}
	else {
		return 0;
	}
}

void LessNode::CodeEvaluate(InstructionsClass & mycode) {
	mExpressionNodeOne->CodeEvaluate(mycode);
	mExpressionNodeTwo->CodeEvaluate(mycode);
	mycode.PopPopLessPush();
}

int GreaterNode::Evaluate() {
	if (mExpressionNodeOne->Evaluate() > mExpressionNodeTwo->Evaluate()) {
		return 1;
	}
	else {
		return 0;
	}
}

void GreaterNode::CodeEvaluate(InstructionsClass & mycode) {
	mExpressionNodeOne->CodeEvaluate(mycode);
	mExpressionNodeTwo->CodeEvaluate(mycode);
	mycode.PopPopGreaterPush();
}

int LessEqualNode::Evaluate() {
	if (mExpressionNodeOne->Evaluate() <= mExpressionNodeTwo->Evaluate()) {
		return 1;
	}
	else {
		return 0;
	}
}

void LessEqualNode::CodeEvaluate(InstructionsClass & mycode) {
	mExpressionNodeOne->CodeEvaluate(mycode);
	mExpressionNodeTwo->CodeEvaluate(mycode);
	mycode.PopPopLessEqualPush();
}

int GreaterEqualNode::Evaluate() {
	if (mExpressionNodeOne->Evaluate() >= mExpressionNodeTwo->Evaluate()) {
		return 1;
	}
	else {
		return 0;
	}
}

void GreaterEqualNode::CodeEvaluate(InstructionsClass & mycode) {
	mExpressionNodeOne->CodeEvaluate(mycode);
	mExpressionNodeTwo->CodeEvaluate(mycode);
	mycode.PopPopGreaterEqualPush();
}

int EqualNode::Evaluate() {
	if (mExpressionNodeOne->Evaluate() == mExpressionNodeTwo->Evaluate()) {
		return 1;
	}
	else {
		return 0;
	}
}

void EqualNode::CodeEvaluate(InstructionsClass & mycode) {
	mExpressionNodeOne->CodeEvaluate(mycode);
	mExpressionNodeTwo->CodeEvaluate(mycode);
	mycode.PopPopEqualPush();
}

int NotEqualNode::Evaluate() {
	if (mExpressionNodeOne->Evaluate() != mExpressionNodeTwo->Evaluate()) {
		return 1;
	}
	else {
		return 0;
	}
}

void NotEqualNode::CodeEvaluate(InstructionsClass & mycode) {
	mExpressionNodeOne->CodeEvaluate(mycode);
	mExpressionNodeTwo->CodeEvaluate(mycode);
	mycode.PopPopNotEqualPush();
}
