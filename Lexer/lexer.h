#pragma once
#include <string_view>
#include "token.h"

class Lexer
{
public:
	Lexer(const char* data);
	~Lexer();

	Token Next();

	bool IsSymbol(char c);
	bool IsDigit(char c);
	bool IsSpace(char c);
	bool IsNewLine(char c);
	bool IsEnd(char c);
private:
	const char* m_data;
};