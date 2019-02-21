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

