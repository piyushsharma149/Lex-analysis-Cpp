#include <iostream> 
#include <fstream> 
#include <string> 
#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"
#include<tr1/unordered_map>

using namespace std;

LexicalAnalyzer::LexicalAnalyzer(ifstream* scf) { 
	sourceCodeFile = scf;
	charPosition = 0;
	
	
	umaps["and"] = ANDSYM;
	umaps["begin"] = BEGINSYM;
	umaps["boolean"] = BOOLSYM;
	umaps["div"] = DIVSYM;
	umaps["do"] = DOSYM;
	umaps["downto"] = DOWNTOSYM;
	umaps["else"] = ELSESYM;
	umaps["end"] = ENDSYM;
	umaps["false"] = FALSESYM;
	umaps["for"] = FORSYM;
	umaps["if"] = IFSYM;
	umaps["integer"] = INTSYM;	
	umaps["mod"] = MODSYM;
	umaps["not"] = NOTSYM;
	umaps["or"] = ORSYM;
	umaps["program"] = PROGSYM;
	umaps["read"] = READSYM;
	umaps["readln"] = READLNSYM;
	umaps["real"] = REALSYM;
	umaps["repeat"] = REPEATSYM;
	umaps["then"] = THENSYM;
	umaps["to"] = TOSYM;
	umaps["true"] = TRUESYM;
	umaps["until"] = UNTILSYM;
	umaps["var"] = VARSYM;
	umaps["while"] = WHILESYM;
	umaps["write"] = WRITESYM;
	umaps["writeln"] = WRITELNSYM;
	
	
}
bool LexicalAnalyzer::isEOF() { 
	if (sourceCodeFile->eof()) { 
		return true;
	}
	return false;
}


void LexicalAnalyzer::getChar() {
	
	if (charPosition == 0){
		readNextLine();
		myChar = s[charPosition++];
		
	}
	
	else if(s.length() <= charPosition){
		myChar = '\n';
		charPosition = 0; 	
		readNextLine();
	}	
	else{
		myChar = s.at(charPosition++);
	}
}


void LexicalAnalyzer::readNextLine() 
{ 	
	
	if (!sourceCodeFile->eof()) { 
		getline(*sourceCodeFile, s);
			 
	}
	
}




Token* LexicalAnalyzer::getNextToken()
{	
	lexeme = "";
	getChar();
	
	if (isalpha(myChar))
	{
		lexeme += myChar;
		getChar();
		while(isalpha(myChar) || isdigit(myChar))
		{
			lexeme += myChar;
			getChar();

		}
		if(umaps.find(lexeme) != umaps.end()){
			auto it = umaps.find(lexeme);
			tk->setTokenCode(it->second);
		}
		else 
			tk->setTokenCode(IDENT);	
	}
	
	
	
	else if(isdigit(myChar))
	{		
		lexeme += myChar;
		getChar();
		while(isdigit(myChar) || myChar == '.')
		{	
			lexeme+= myChar;
			getChar();
		}
		tk->setTokenCode(NUMLIT);
	}

	else if (!sourceCodeFile->eof()) { 
		tk->setTokenCode(EOI);
		 
	}
	
	else
	switch(myChar) {
	
		case '+':
			lexeme += myChar;
			tk->setTokenCode(PLUS);
			break;
			
			
		case '-':
			lexeme += myChar;
			tk->setTokenCode(MINUS);
			break;

		case '*':
			lexeme += myChar;
			tk->setTokenCode(TIMES);
			break;
			
		case '/':
			lexeme += myChar;
			tk->setTokenCode(SLASH);
			break;
			
		case '=':
			lexeme += myChar;
			tk->setTokenCode(EQL);
			break;
			
		case '(':
			lexeme += myChar;
			tk->setTokenCode(LPAREN);
			break;
			
		case ')':
			lexeme += myChar;
			tk->setTokenCode(RPAREN);
			break;
			
		case '.':
			lexeme += myChar;
			tk->setTokenCode(PERIOD);
			break;

		case ',':
			lexeme += myChar;
			tk->setTokenCode(COMMA);
			break;
			
		case ';':
			lexeme += myChar;
			tk->setTokenCode(SEMICOLON);
			break;
			
	
		case ':':
			
			lexeme += myChar;
			getChar();
			char bec;
			if (myChar == '=')
			{
			  lexeme += myChar;
			  tk->setTokenCode(BECOMES);
			  getChar();
			}
			else
			    tk->setTokenCode(COLON);
			break;
			
		case '<':
			lexeme += myChar;
			getChar();
			char lec;
			if (myChar == '=')
			{
				lexeme += myChar;
				tk->setTokenCode(LEQ);
				getChar();
			}
			
			else if (myChar == '<'){
				lexeme += myChar;
				tk->setTokenCode(NEQ);
				getChar();
			}
			
			else
				tk->setTokenCode(LSS);
			break;
			
		case '>':
			lexeme += myChar;
			getChar();
			char gec;
			if (myChar == '=')
			{
				lexeme += myChar;
				tk->setTokenCode(GEQ);
				getChar();
			}
			else 
				tk->setTokenCode(GTR);
			break;
		
		default:
			lexeme += myChar;
			tk->setTokenCode(NAL);
			break;
	}
	
	tk->setLexemeString(lexeme);
	
	return tk;

}

