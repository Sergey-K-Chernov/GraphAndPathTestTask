#pragma once
#include <vector>
#include <array>

const size_t MIN_NODES = 100;
const size_t MIN_EDGES = 230;
const size_t MAX_WEIGHT = 9;


struct Node
{
	std::vector<size_t> iEdges;
};

typedef std::vector<Node> Nodes;


struct Edge
{
	size_t iFrom;
	size_t iTo;

	unsigned int weight;
};

typedef std::vector<Edge> Edges;


class GraphAdj;


class Graph
{
public:
	Graph();
	Graph(const std::vector<std::vector<unsigned int>> adjacency_matrix); // Для создания графа из матрицы смежности в целях отладки

	size_t GetNodesSize() const;
	const Node& GetNode(size_t id) const;
	const Nodes& GetNodes() const;

	const Edge& GetEdge(size_t id) const;
	const Edges& GetEdges() const;

	template <typename T> 
	unsigned int GetDistance(T path)
	{
		auto distance = 0u;
		for (size_t id = 0; id + 1 < path.size(); ++id)
		{
			for (auto& edge : nodes[path[id]].iEdges)
			{
				if (edges[edge].iTo == path[id + 1])
				{
					distance += edges[edge].weight;
					break;
				}
			}
		}
		return distance;
	}

private:
	bool EdgeExists(size_t iNode1, size_t iNode2);

private:
	Nodes nodes;
	Edges edges;

	friend GraphAdj;
};


void PrintGraph(const Graph& g);