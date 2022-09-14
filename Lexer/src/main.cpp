#include <fstream>
#include <sstream>

#include "state_machine.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    std::ifstream file(".\\examples\\ex1.txt");
    if (file.is_open() == false)
        return 0;

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string str = buffer.str();

    StateMachine stateMachine(str.c_str());
    stateMachine.Start();
}