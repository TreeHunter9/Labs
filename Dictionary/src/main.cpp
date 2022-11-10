#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "dictionary.h"

int main(int, char**) 
{
	Dictionary<std::string, int> dict(20);

	std::fstream file("../examples/text.txt");
	if (file.is_open())
	{
		std::string line;
		std::string word;
		while(std::getline(file, line))
		{
			std::stringstream str_stream(line);
			while (str_stream >> word)
			{
				dict[word] = 0;
			}
		}
	}

	dict.PrintHistogram();
	return 0;
}
