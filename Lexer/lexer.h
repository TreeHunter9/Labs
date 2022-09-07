#pragma once
#include <string_view>
#include "token.h"

class Lexer
{
public:
	Lexer(const char* data);
	~Lexer();

	Token Next();
	static Token GetToken(char symbol);
private:
	static bool IsSymbol(char c);
	static bool IsDigit(char c);
	static bool IsSpace(char c);
	static bool IsEnd(char c);
private:
	const char* m_data;
};