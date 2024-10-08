﻿#include <iostream>
#include "Graph.h"
#include "AlternativeGraph.h"
#include "FindPath.h"
#include "Test.h"

template <typename T, typename G>
static void PrintPath(T path, G graph)
{
	std::cout << "Path length = " << path.size() << ", path distance = " << graph.GetDistance(path) << ":\n";
	for (auto id : path)
	{
		std::cout << id << " ";
	}
	std::cout << '\n';
}


/*
#define TEST
//*/

int main()
{
#ifdef TEST
	test();
#else

	Graph graph;
	auto path = FindPath(graph, 0, graph.GetNodesSize() - 1);
	PrintPath(path, graph);

	/*
	* Comment the random part of these lines in the Graph ctor for a correct comparison:
	*     size_t nNodes = MIN_NODES + nodes_qty_d100(random_generator);
	*	  size_t nEdges = MIN_EDGES + edges_qty_d230(random_generator);
	* - because the debug/test graph doesn't allow variable number of nodes and edges.
	* 
	* 
	GraphAdj alt_graph(graph);
	auto path2 = alt_graph.dijkstra(0, MIN_NODES - 1);
	PrintPath(path2, alt_graph);
	*/
#endif
	
	return 0;
}