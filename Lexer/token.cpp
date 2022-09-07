#include "token.h"

Token::Token()
	: m_type(Type::Unknown), m_symbol(0)
{}

Token::Token(Type type, char symbol)
	: m_type(type), m_symbol(symbol)
{}

Token::~Token()
{}

Token::Type Token::GetType() const
{
	return m_type;
}

char Token::GetSymbol() const
{
	return m_symbol;
}
