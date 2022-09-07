#pragma once
#include <vector>
#include "token.h"

class StateMachine
{
public:
	enum class States
	{
		Waiting,
		NextLitera,
		Stop,
		Error
	};

	StateMachine(const char* data);
	~StateMachine();

	void Start();

private:
	void ProcessWaitingState(Token token, std::vector<char>& buffer);
	void ProcessNextLiteraState(Token token, std::vector<char>& buffer);
	void ProcessStopState();
	void ProcessErrorState();
private:
	const char* m_data;
	States m_currentState;
};

