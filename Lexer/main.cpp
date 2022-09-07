#include <iostream>
#include <fstream>
#include <string_view>
#include <sstream>

#include "lexer.h"

int main()
{
    std::fstream file("text.txt");
    std::stringstream buffer;

    if (file.is_open() == false)
        return 0;

    buffer << file.rdbuf();
    std::string str = buffer.str();
    Lexer lexer(str.c_str());
    for (Token token = lexer.Next(); token.GetType() != Token::End; token = lexer.Next())
    {
        std::cout << token.GetNameType() << " - " << token.GetSymbol() << '\n';
    }
}