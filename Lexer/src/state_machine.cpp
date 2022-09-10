#include <vector>
#include <iostream>

#include "state_machine.h"
#include "lexer.h"

StateMachine::StateMachine(const char* data)
	: m_data(data), m_currentState(States::Waiting)
{}

StateMachine::~StateMachine()
{}

void StateMachine::Start()
{
	Token token;
	std::vector<char> buffer;
	while (true)
	{
		token = Lexer::GetToken(*m_data++);
		switch (m_currentState)
		{
		case States::Waiting:
			ProcessWaitingState(token, buffer);
			break;
		case States::NextLitera:
			ProcessNextLiteraState(token, buffer);
			break;
		case States::Stop:
			ProcessStopState();
			return;
		case States::Error:
			ProcessErrorState();
			return;
		default:
			break;
		}
	}
}

void StateMachine::ProcessWaitingState(Token token, std::vector<char>& buffer)
{
	switch (token.GetType())
	{
	case Token::Symbol:
		buffer.push_back(token.GetSymbol());
		m_currentState = States::NextLitera;
		break;
	case Token::Space:
		break;
	case Token::End:
		m_currentState = States::Stop;
		break;
	default:
		m_currentState = States::Error;
		break;
	}
}

void StateMachine::ProcessNextLiteraState(Token token, std::vector<char>& buffer)
{
	switch (token.GetType())
	{
	case Token::Digit:
	case Token::Symbol:
		buffer.push_back(token.GetSymbol());
		m_currentState = States::NextLitera;
		break;
	case Token::Space:
		buffer.push_back('\0');
		std::cout << buffer.data() << '\n';
		buffer.clear();
		m_currentState = States::Waiting;
		break;
	case Token::End:
		buffer.push_back('\0');
		std::cout << buffer.data() << '\n';
		buffer.clear();
		m_currentState = States::Stop;
		break;
	default:
		m_currentState = States::Error;
		break;
	}
}

void StateMachine::ProcessStopState()
{
	std::cout << "Finish" << '\n';
}

void StateMachine::ProcessErrorState()
{
	std::cout << "Error" << '\n';
}
