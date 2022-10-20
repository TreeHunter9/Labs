#pragma once

#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

struct Edge
{
	int to;
	int weight;
};

class Node
{
public:
	Node()
		: node_id(-1), min_weight(0), prev_node_id(-1)
	{}

	Node(std::vector<Edge> edges, int node_id)
		: edges(edges), node_id(node_id), min_weight(0), prev_node_id(-1)
	{}

	bool SetMinWeight(int new_min_weight, int prev_node)
	{
		if (new_min_weight >= min_weight && min_weight > 0)
			return false;
		
		min_weight = new_min_weight;
		prev_node_id = prev_node;
		return true;
	}
public:
	std::vector<Edge> edges;
	int node_id;
	int min_weight;
	int prev_node_id;
};

template<size_t size>
class Graph
{
public:
	Graph(int map[size][size])
	{
		for (int i = 0; i < size; i++)
		{
			std::vector<Edge> edges;
			edges.reserve(size);
			for (int j = 0; j < size; j++)
			{
				if (map[i][j])
					edges.push_back({j, map[i][j]});
			}
			m_nodes[i] = Node(edges, i);
		}
	}

	std::vector<int> FindShortesPath(int start_id, int finish_id)
	{
		start_id--;
		finish_id--;
		if (start_id == finish_id)
			throw std::invalid_argument("Start and finish id are the same");

		std::queue<int> next_nodes;
		next_nodes.push(start_id);

		while (!next_nodes.empty())
		{
			Node& node = m_nodes.at(next_nodes.front());
			next_nodes.pop();
			if (node.node_id == finish_id)
				continue;

			for (const Edge& edge : node.edges)
			{
				if (m_nodes.at(edge.to).SetMinWeight(node.min_weight + edge.weight, node.node_id))
					next_nodes.push(edge.to);
			}
		}

		int current_id = finish_id;
		std::vector<int> path;
		while (m_nodes.count(current_id))
		{
			path.push_back(current_id + 1);
			
			current_id = m_nodes.at(current_id).prev_node_id;
		}
		if (path.empty())
			throw std::invalid_argument("Those two nodes are not \"connected\"");

		std::reverse(path.begin(), path.end());
		return path;
	}
private:
	std::unordered_map<int, Node> m_nodes;
};

namespace graph_util
{
	void PrintPath(std::vector<int> path)
	{
		for (int i = 0; i < path.size() - 1; i++)
		{
			std::cout << path[i] << " -> ";
		}
		std::cout << path.back() << '\n';
	};
}