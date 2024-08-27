#pragma once
#include "Graph.h"
#include <deque>

class GraphAdj
{
public:
	GraphAdj(const Graph& my_graph);

	std::deque<unsigned int> dijkstra(unsigned int src, unsigned int dest);
	void print();

	template <typename T>
	unsigned int GetDistance(T path)
	{
		auto distance = 0u;
		for (size_t id = 0; id + 1 < path.size(); ++id)
		{
			distance += graph[path[id]][path[id+1]];
		}
		return distance;
	}
private:
	unsigned int graph[MIN_NODES][MIN_NODES];
};


