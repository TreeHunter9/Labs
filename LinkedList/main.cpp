#include <iostream>
#include "linked_list.h"

int main()
{
	LinkedList<int> linked_list;
	linked_list.AddBegin(5);
	linked_list.AddEnd(6);
	linked_list.AddEnd(23);
	linked_list.AddBegin(3);
	linked_list.Remove(3);
	for (const auto& node : linked_list)
	{
		std::cout << node.value << " ";
	}
}