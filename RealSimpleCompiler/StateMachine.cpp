#include "StateMachine.h"


StateMachineClass::StateMachineClass() {
	//MSG("Initializing StateMachine Object");
	for (int i = 0; i < LAST_STATE; i++) {
		for (int j = 0; j < LAST_CHAR; j++) {
			mLegalMoves[i][j] = CANTMOVE_STATE;
		}
	}

	for (int i = 0; i < LAST_STATE; i++) {
		mCorrespondingTokenTypes[i] = BAD_TOKEN;
	}

	mCurrentState = START_STATE;
	mLegalMoves[START_STATE][DIGIT_CHAR] = INTEGER_STATE;
	mLegalMoves[INTEGER_STATE][DIGIT_CHAR] = INTEGER_STATE;
	mLegalMoves[INTEGER_STATE][LESS_CHAR] = CANTMOVE_STATE;
	//MORE EDGES OF GRAPH GOES HERE from picture
	mLegalMoves[START_STATE][PLUS_CHAR] = PLUS_STATE;
	mLegalMoves[START_STATE][MINUS_CHAR] = MINUS_STATE;
	mLegalMoves[START_STATE][TIMES_CHAR] = TIMES_STATE;
	mLegalMoves[START_STATE][LEFTPAREN_CHAR] = LEFTPAREN_STATE;
	mLegalMoves[START_STATE][RIGHTPAREN_CHAR] = RIGHTPAREN_STATE;
	mLegalMoves[START_STATE][EOF_CHAR] = EOF_STATE;
	mLegalMoves[START_STATE][LEFTCURLY_CHAR] = LEFTCURLY_STATE;
	mLegalMoves[START_STATE][RIGHTCURLY_CHAR] = RIGHTCURLY_STATE;
	mLegalMoves[START_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[START_STATE][WHITESPACE_CHAR] = START_STATE;
	mLegalMoves[START_STATE][SEMICOLON_CHAR] = SEMICOLON_STATE;
	mLegalMoves[START_STATE][NEWLINE_CHAR] = START_STATE;

	//and state
	mLegalMoves[START_STATE][AMPERSAND_CHAR] = AMPERSAND_STATE;
	mLegalMoves[AMPERSAND_STATE][AMPERSAND_CHAR] = AND_STATE;

	//or state
	mLegalMoves[START_STATE][PIPE_CHAR] = PIPE_STATE;
	mLegalMoves[PIPE_STATE][PIPE_CHAR] = OR_STATE;
	

	//identifier state to anything else????
	//mLegalMoves[IDENTIFIER_STATE][RETURN_CHAR] = RETURN_STATE;
	mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[IDENTIFIER_STATE][DIGIT_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[IDENTIFIER_STATE][WHITESPACE_CHAR] = CANTMOVE_STATE;


	//HALFWAY STATES 
	mLegalMoves[START_STATE][DIVIDE_CHAR] = DIVIDE_STATE;

	//line comments
	mLegalMoves[DIVIDE_STATE][DIVIDE_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][EOF_CHAR] = EOF_STATE;
	mLegalMoves[LINECOMMENT_STATE][NEWLINE_CHAR] = START_STATE;

	//NOT RETURN CHAR OR NOT EOF STILL LINE COMMENT STATE 
	mLegalMoves[LINECOMMENT_STATE][LETTER_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][DIGIT_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][WHITESPACE_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][PLUS_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][BAD_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][LESS_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][GREATER_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][LEFTBR_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][RIGHTBR_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][ASSIGNMENT_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][NOT_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][SEMICOLON_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][TIMES_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][LEFTCURLY_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][RIGHTCURLY_CHAR] = LINECOMMENT_STATE;
	mLegalMoves[LINECOMMENT_STATE][DIVIDE_CHAR] = LINECOMMENT_STATE;

	//block comments 
	mLegalMoves[DIVIDE_STATE][TIMES_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][TIMES_CHAR] = HALFWAY_STATE;
	mLegalMoves[HALFWAY_STATE][DIVIDE_CHAR] = START_STATE;
	mLegalMoves[HALFWAY_STATE][TIMES_CHAR] = HALFWAY_STATE;

	//BLOCKCOMMENT STATE TO ANYTHING ELSE IN COMMENTS GOES BACK INTO BLOCKCOMMENT STATE
	mLegalMoves[BLOCKCOMMENT_STATE][LETTER_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][DIGIT_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][WHITESPACE_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][PLUS_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][BAD_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][LESS_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][GREATER_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][LEFTBR_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][RIGHTBR_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][ASSIGNMENT_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][NOT_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][SEMICOLON_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][EOF_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][LEFTCURLY_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][RIGHTCURLY_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][DIVIDE_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][NEWLINE_CHAR] = BLOCKCOMMENT_STATE;

	//HALFWAY STATE TO !* OR !/ GOES TO BLOCK COMMENT STATE 
	mLegalMoves[HALFWAY_STATE][LETTER_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[HALFWAY_STATE][DIGIT_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[HALFWAY_STATE][WHITESPACE_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[HALFWAY_STATE][PLUS_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[HALFWAY_STATE][BAD_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[HALFWAY_STATE][LESS_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[HALFWAY_STATE][GREATER_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[HALFWAY_STATE][LEFTBR_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[HALFWAY_STATE][RIGHTBR_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[HALFWAY_STATE][ASSIGNMENT_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[HALFWAY_STATE][NOT_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[HALFWAY_STATE][SEMICOLON_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[HALFWAY_STATE][EOF_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[HALFWAY_STATE][LEFTCURLY_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[HALFWAY_STATE][RIGHTCURLY_CHAR] = BLOCKCOMMENT_STATE;
	

	//LESS STATE
	mLegalMoves[START_STATE][LESS_CHAR] = LESS_STATE;
	mLegalMoves[LESS_STATE][LESS_CHAR] = INSERTION_STATE;
	mLegalMoves[LESS_STATE][ASSIGNMENT_CHAR] = LESSEQ_STATE;

	mLegalMoves[START_STATE][GREATER_CHAR] = GREATER_STATE;
	mLegalMoves[GREATER_STATE][ASSIGNMENT_CHAR] = GREATEREQ_STATE;

	mLegalMoves[START_STATE][ASSIGNMENT_CHAR] = ASSIGNMENT_STATE;
	mLegalMoves[ASSIGNMENT_STATE][ASSIGNMENT_CHAR] = ISEQUAL_STATE;

	//VOID_TOKEN, MAIN_TOKEN, INT_TOKEN, COUT_TOKEN
	mCorrespondingTokenTypes[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;
	mCorrespondingTokenTypes[LESS_STATE] = LESS_TOKEN;
	mCorrespondingTokenTypes[LESSEQ_STATE] = LESSEQUAL_TOKEN;
	mCorrespondingTokenTypes[GREATER_STATE] = GREATER_TOKEN;
	mCorrespondingTokenTypes[GREATEREQ_STATE] = GREATEREQUAL_TOKEN;
	mCorrespondingTokenTypes[ISEQUAL_STATE] = ISEQUAL_TOKEN;
	//NOT EQUAL TOKEN
	mCorrespondingTokenTypes[INSERTION_STATE] = INSERTION_TOKEN;
	mCorrespondingTokenTypes[ASSIGNMENT_STATE] = ASSIGNMENT_TOKEN;
	mCorrespondingTokenTypes[PLUS_STATE] = PLUS_TOKEN;
	mCorrespondingTokenTypes[MINUS_STATE] = MINUS_TOKEN;
	mCorrespondingTokenTypes[TIMES_STATE] = TIMES_TOKEN;
	mCorrespondingTokenTypes[DIVIDE_STATE] = DIVIDE_TOKEN;
	mCorrespondingTokenTypes[SEMICOLON_STATE] = SEMICOLON_TOKEN;
	mCorrespondingTokenTypes[LEFTPAREN_STATE] = LPAREN_TOKEN;
	mCorrespondingTokenTypes[RIGHTPAREN_STATE] = RPAREN_TOKEN;
	mCorrespondingTokenTypes[LEFTCURLY_STATE] = LCURLY_TOKEN;
	mCorrespondingTokenTypes[RIGHTCURLY_STATE] = RCURLY_TOKEN;
	mCorrespondingTokenTypes[INTEGER_STATE] = INTEGER_TOKEN;
	mCorrespondingTokenTypes[EOF_STATE] = ENDFILE_TOKEN;
	mCorrespondingTokenTypes[AND_STATE] = AND_TOKEN;
	mCorrespondingTokenTypes[OR_STATE] = OR_TOKEN;
	//RETURN TOKEN?!?!?!
}


MachineState StateMachineClass::UpdateState(char currentCharacter, TokenType & correspondingTokenType) {


	//convert the input character into an input character type
	CharacterType charType = BAD_CHAR;

	if (isdigit(currentCharacter)) {
		charType = DIGIT_CHAR;
	}

	else if (currentCharacter == '|') {
		charType = PIPE_CHAR;
	}
	else if (currentCharacter == '&') {
		charType = AMPERSAND_CHAR;
	}

	else if (currentCharacter == '\n') {
		charType = NEWLINE_CHAR;
	}

	else if (isalpha(currentCharacter)) {
		charType = LETTER_CHAR;
	}

	else if (isspace(currentCharacter)) {
		charType = WHITESPACE_CHAR;
	}

	else if (currentCharacter == '+') {
		charType = PLUS_CHAR;
	}

	else if (currentCharacter == '-') {
		charType = MINUS_CHAR;
	}

	else if (currentCharacter == '*') {
		charType = TIMES_CHAR;
	}

	else if (currentCharacter == '/') {
		charType = DIVIDE_CHAR;
	}

	else if (currentCharacter == ';') {
		charType = SEMICOLON_CHAR;
	}

	else if (currentCharacter == '(') {
		charType = LEFTPAREN_CHAR;
	}

	else if (currentCharacter == ')') {
		charType = RIGHTPAREN_CHAR;
	}

	else if (currentCharacter == '{') {
		charType = LEFTCURLY_CHAR;
	}

	else if (currentCharacter == '}') {
		charType = RIGHTCURLY_CHAR;
	}

	else if (currentCharacter == '<') {
		charType = LESS_CHAR;
	}

	else if (currentCharacter == '>') {
		charType = GREATER_CHAR;
	}

	else if (currentCharacter == '=') {
		charType = ASSIGNMENT_CHAR;
	}

	else if (currentCharacter == '!') {
		charType = NOT_CHAR;
	}

	else if (currentCharacter == EOF) {
		charType = EOF_CHAR;
	}

	else {
		charType = BAD_CHAR;
	}


	correspondingTokenType = mCorrespondingTokenTypes[mCurrentState];
	mCurrentState = mLegalMoves[mCurrentState][charType];
	return mCurrentState;
}
 
