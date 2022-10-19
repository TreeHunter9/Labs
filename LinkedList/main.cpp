#include <iostream>
#include "linked_list.h"

int main()
{
	LinkedList<int> linked_list;
	linked_list.RemoveBegin();
	for (const auto& node : linked_list)
	{
		std::cout << node.value << " ";
	}
}