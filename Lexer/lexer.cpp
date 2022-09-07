#include "lexer.h"

Lexer::Lexer(const char* data)
	: m_data(data)
{}

Lexer::~Lexer()
{}

Token Lexer::Next()
{
	char symbol = *m_data++;
	if (IsSymbol(symbol))
		return Token(Token::Symbol, symbol);

	if (IsDigit(symbol))
		return Token(Token::Digit, symbol);

	if (IsSpace(symbol))
		return Token(Token::Space, symbol);

	if (IsNewLine(symbol))
		return Token(Token::NewLine, symbol);

	if (IsEnd(symbol))
		return Token(Token::End, symbol);

	return Token(Token::Unknown, symbol);
}

bool Lexer::IsSymbol(char c)
{
	if (c > 'a' && c < 'z')
		return true;

	if (c > 'A' && c < 'Z')
		return true;

	if (c > 'a' && c < 'ÿ')
		return true;

	if (c > 'À' && c < 'ß')
		return true;

	return false;
}

bool Lexer::IsDigit(char c)
{
	if (c > '0' && c < '9')
		return true;

	return false;
}

bool Lexer::IsSpace(char c)
{
	if (c == ' ')
		return true;

	return false;
}

bool Lexer::IsNewLine(char c)
{
	if (c == '\n')
		return true;

	return false;
}

bool Lexer::IsEnd(char c)
{
	if (c == '\0')
		return true;

	return false;
}
