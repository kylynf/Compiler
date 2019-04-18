//#include "Scanner.h"
//#include "Symbol.h"
#include "Parser.h"
#include "Instructions.h"

int main() {
	SymbolTableClass symbol;

	ScannerClass scanner("code.txt");

	ParserClass parser(&scanner, &symbol);

	StartNode * starting = parser.Start();

	//THIS
	//starting->Interpret();

	//OR THIS
	InstructionsClass newcode;
	starting->Code(newcode);
	newcode.Finish();
	newcode.Execute();

	delete starting;

	
	return 0;

}

//int T;
//int i;
//int j;
//i = 2;
//while (i <= 100) {
//	T = 0;
//	j = 2;
//	while (j < i) {
//		if (i / j * j == i) {
//			T = 1;
//		}
//		j = j + 1;
//	}
//	if (T == 0) {
//		cout << i;
//	}
//	i = i + 1;
//}