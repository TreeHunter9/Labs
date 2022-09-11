#pragma once

class Token
{
public:
	enum Type
	{
		Symbol,
		Digit,
		Space,
		End,
		Unknown
	};

	Token();
	Token(Type type, char symbol);
	~Token();

	Type GetType() const;
	char GetSymbol() const;
private:
	Type m_type;
	char m_symbol;
};

