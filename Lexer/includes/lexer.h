#pragma once
#include "token.h"

static class Lexer
{
public:
	static Token GetToken(char symbol);

private:
	static bool IsSymbol(char c);
	static bool IsDigit(char c);
	static bool IsSpace(char c);
	static bool IsEnd(char c);
};