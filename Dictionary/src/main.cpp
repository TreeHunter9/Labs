#include <iostream>
#include "dictionary.h"

int main(int, char**) 
{
	Dictionary<int, int> dict;
	dict[1] = 1;
	dict[25] = 2;
	dict[3] = 3;
	dict[46] = 4;
	dict[5] = 5;
	dict[64] = 6;
	dict[72] = 7;
	dict[8] = 8;
	dict[19] = 9;
	dict[10] = 10;
	int value;
	std::cout << dict.GetValue(72) << '\n';
	std::cout << dict.TryGetValue(3, value) << " - " << value << '\n';
	dict.Add(44, 34);
	std::cout << dict.TryAdd(44, 33) << '\n';
	std::cout << dict.RemoveKey(44) << '\n';
	std::cout << dict.ContainsKey(44) << '\n'; 
	return 0;
}
