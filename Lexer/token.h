#pragma once
#include <iostream>

class Token
{
public:
	enum Type
	{
		Symbol,
		Digit,
		Space,
		NewLine,
		End,
		Unknown
	};

	Token(Type type, char symbol);
	~Token();

	const char* GetNameType() const;
	Type GetType() const;
	char GetSymbol() const;
private:
	Type m_type;
	char m_symbol;
};

