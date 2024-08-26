#pragma once
#include <vector>
#include <array>

struct Node
{
	std::vector<size_t> edges;
};

typedef std::vector<Node> Nodes;

struct Edge
{
	size_t iFrom;
	size_t iTo;

	unsigned int weight;
};

typedef std::vector<Edge> Edges;


class Graph
{
public:
	Graph();
	Graph(const std::vector<std::vector<unsigned int>> adjacency_matrix); // Для создания графа из матрицы смежности в целях отладки

	size_t GetNodesSize() const
	{
		return nodes.size();
	}
	
	const Node& GetNode(size_t id) const
	{
		return nodes[id];
	}

	const Nodes& GetNodes() const
	{
		return nodes;
	}

	const Edge& GetEdge(size_t id) const
	{
		return edges[id];
	}

	const Edges& GetEdges() const
	{
		return edges;
	}

private:
	Nodes nodes;
	Edges edges;
};