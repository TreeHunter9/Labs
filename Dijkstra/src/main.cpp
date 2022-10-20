#include <iostream>
#include <vector>
#include "graph.h"

int main(int, char**) 
{
	const int nodes_number = 7;
	int map[nodes_number][nodes_number] = {
		{0, 0, 2, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 3, 0, 4, 0, 0, 0},
		{0, 0, 0, 0, 1, 4, 6},
		{0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0}
	};
	Graph<nodes_number> graph(map);
	std::vector<int> path = graph.FindShortesPath(1, 7);
	graph_util::PrintPath(path);
}