#pragma once
#include "token.h"

class Lexer
{
public:
	Token GetToken(char symbol);

private:
	bool IsSymbol(char c);
	bool IsDigit(char c);
	bool IsSpace(char c);
	bool IsEnd(char c);
};