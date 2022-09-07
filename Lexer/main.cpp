#include <iostream>
#include <fstream>
#include <string_view>
#include <sstream>

#include "lexer.h"
#include "state_machine.h"

int main()
{
    std::fstream file("text.txt");
    if (file.is_open() == false)
        return 0;

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string str = buffer.str();

    StateMachine stateMachine(str.c_str());
    stateMachine.Start();
}