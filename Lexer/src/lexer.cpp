#include "lexer.h"

Token Lexer::GetToken(char symbol)
{
	if (IsSymbol(symbol))
		return Token(Token::Symbol, symbol);

	if (IsDigit(symbol))
		return Token(Token::Digit, symbol);

	if (IsSpace(symbol))
		return Token(Token::Space, symbol);

	if (IsEnd(symbol))
		return Token(Token::End, symbol);

	return Token(Token::Unknown, symbol);
}

bool Lexer::IsSymbol(char c)
{
	if (c >= 'a' && c <= 'z')
		return true;

	if (c >= 'A' && c <= 'Z')
		return true;

	if (c >= 'à' && c <= 'ÿ')
		return true;

	if (c >= 'À' && c <= 'ß')
		return true;

	return false;
}

bool Lexer::IsDigit(char c)
{
	if (c >= '0' && c <= '9')
		return true;

	return false;
}

bool Lexer::IsSpace(char c)
{
	switch (c)
	{
	case ' ':
	case '\t':
	case '\r':
	case '\n':
		return true;
	default:
		return false;
	}
}

bool Lexer::IsEnd(char c)
{
	if (c == '\0')
		return true;

	return false;
}
