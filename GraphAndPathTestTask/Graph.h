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

	int weight;
};

typedef std::vector<Edge> Edges;


class Graph
{
public:
	Graph();
	Graph(const std::vector<std::vector<int>> adjacency_matrix); // Для создания графа из матрицы смежности в целях отладки

private:
	Nodes nodes;
	Edges edges;
};