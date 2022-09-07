#include "token.h"

Token::Token(Type type, char symbol)
	: m_type(type), m_symbol(symbol)
{}

Token::~Token()
{}

const char* Token::GetNameType() const
{
	switch (m_type)
	{
	case Token::Symbol:
		return "Symbol";
	case Token::Digit:
		return "Digit";
	case Token::Space:
		return "Space";
	case Token::NewLine:
		return "NewLine";
	case Token::End:
		return "End";
	case Token::Unknown:
		return "Unknown";
	default:
		return "";
	}	
}

Token::Type Token::GetType() const
{
	return m_type;
}

char Token::GetSymbol() const
{
	return m_symbol;
}
