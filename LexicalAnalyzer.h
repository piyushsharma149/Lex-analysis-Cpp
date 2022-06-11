#ifndef LEXICALANALYZER_H 
#define LEXICALANALYZER_H

#include <fstream> 
#include <string>
#include "Token.h"
#include "TokenCodes.h"
#include<tr1/unordered_map>

using namespace std; 

class LexicalAnalyzer 
{ 
private: 
	ifstream *sourceCodeFile; 
	string s; 
	int charPosition = 0;
	char myChar;
	bool isEOF(); 
	void getChar(); 
	void readNextLine();
	
	Token* tk;
	string lexeme;
	std::tr1::unordered_map<string, TokenCodes> umaps;
	


public: 
	LexicalAnalyzer(ifstream*); 
	Token *getNextToken();
};

#endif




