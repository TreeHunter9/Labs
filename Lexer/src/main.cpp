#include <fstream>
#include <sstream>
#include <chrono>
#include <iostream>

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

    auto start = std::chrono::high_resolution_clock::now();
    stateMachine.Start();
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = end - start;
    std::cout << "Execution time: " << duration.count() << " ns" << '\n';

    return 0;
}